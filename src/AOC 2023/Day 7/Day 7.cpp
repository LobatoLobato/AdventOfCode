//
// Created by Lobato on 07/12/2023.
//

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <sstream>

#include "utils.h"
#include "benchmark.h"

class Hand {
public:
    enum class Type {
        HighCard = 0,
        OnePair = 1,
        TwoPair = 2,
        ThreeOfAKind = 3,
        FullHouse = 4,
        FourOfAKind = 5,
        FiveOfAKind = 6,
    };
    std::string cards;
    std::string compCards;
    size_t bid;
    Type type = Type::HighCard;
    
    
    Hand(const std::string &cards, size_t bid, bool includeJokers = false) : cards(cards), bid(bid), compCards(cards) {
      this->compCards = cardsToCompCards(cards, includeJokers);
      this->type = cardsToHandType(cards, includeJokers);
    }
    
    static Hand from(const std::string &line, bool includeJokers = false) {
      size_t delimIndex = line.find(" ");
      std::string cards = line.substr(0, delimIndex);
      size_t bid = std::stoull(line.substr(delimIndex));
      
      return {cards, bid, includeJokers};
    }
    
    bool operator<(const Hand &hand) const {
      if (this->type == hand.type) { return compCards.compare(hand.compCards) < 0; }
      return this->type < hand.type;
    }

private:
    static std::string cardsToCompCards(std::string cards, bool includeJokers = false) {
      static const std::unordered_map<char, char> cardToCompCardMap = {
          {'T', 10},
          {'J', 11},
          {'Q', 12},
          {'K', 13},
          {'A', 14},
      };
      
      for (char &card: cards) {
        if (includeJokers && card == 'J') { card = '0'; }
        else if (!std::isdigit(card)) { card = cardToCompCardMap.at(card) + '0'; }
      }
      
      return cards;
    }
    
    static Hand::Type cardsToHandType(std::string cards, bool includeJokers = false) {
      static const std::unordered_map<size_t, Hand::Type> cardsToTypeMap = {
          {0,             Hand::Type::HighCard},
          {(1 * (2 + 0)), Hand::Type::OnePair},
          {(1 * (3 + 0)), Hand::Type::ThreeOfAKind},
          {(1 * (4 + 0)), Hand::Type::FourOfAKind},
          {(1 * (5 + 0)), Hand::Type::FiveOfAKind},
          {(2 * (2 + 2)), Hand::Type::TwoPair},
          {(2 * (3 + 2)), Hand::Type::FullHouse},
      };
      
      std::sort(cards.begin(), cards.end());
      
      std::array<size_t, 2> sequenceSizes = {0, 0};
      auto sequenceSize = sequenceSizes.begin();
      size_t numberOfSequences = 0;
      size_t numberOfJokers = (includeJokers && cards[0] == 'J') ? 1 : 0;
      
      for (size_t i = 1; i < cards.size(); i++) {
        bool isJokerCard = includeJokers && cards[i] == 'J';
        bool isCardSequence = cards[i] == cards[i - 1];
        if (isJokerCard) {
          numberOfJokers++;
        }
        else if (isCardSequence) {
          if (*sequenceSize == 0) numberOfSequences++;
          (*sequenceSize) += (*sequenceSize == 0) ? 2 : 1;
        } else if (*sequenceSize > 0) {
          sequenceSize++;
        }
      }
      
      if (includeJokers && (numberOfSequences == 0 && numberOfJokers > 0)) {
        if (numberOfJokers != 5) numberOfJokers++;
        numberOfSequences = 1;
      }
      
      return cardsToTypeMap.at(numberOfSequences * (sequenceSizes[0] + sequenceSizes[1] + numberOfJokers));
    }
};

int main(int argc, char **argv) {
  InputLines lines = readInput("input.txt");
  
  Benchmarker::initialize(argc, argv);

#ifdef PART1
  Benchmarker::registerBenchmark<size_t>("Day 7-1", [&]() -> size_t {
      std::vector<Hand> hands = map<std::string, Hand>(lines, [](const std::string &line, size_t) -> Hand {
          return Hand::from(line);
      }, true);
      
      return reduce<Hand, size_t>(hands, [](size_t acc, const Hand &curr, size_t rank) -> size_t {
          return acc + curr.bid * (rank + 1);
      });
  });
#endif

#ifdef PART2
  Benchmarker::registerBenchmark<size_t>("Day 7-2", [&]() -> size_t {
      std::vector<Hand> hands = map<std::string, Hand>(lines, [](const std::string &line, size_t) -> Hand {
          return Hand::from(line, true);
      }, true);
      
      return reduce<Hand, size_t>(hands, [](size_t acc, const Hand &curr, size_t rank) -> size_t {
          return acc + curr.bid * (rank + 1);
      });
  });
#endif
  
  return Benchmarker::run();
}