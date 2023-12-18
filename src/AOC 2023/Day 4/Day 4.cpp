//
// Created by Lobato on 07/12/2023.
//

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>

#include "utils.h"
#include "benchmark.h"
#include "aho_corasick.hpp"

std::stringstream extractWinningNumbers(const std::string &line) {
  size_t winningNumberListStart = line.find(':') + 1;
  size_t winningNumberListEnd = line.find('|') - winningNumberListStart;
  
  return std::stringstream{line.substr(winningNumberListStart, winningNumberListEnd)};
}

std::string extractPlayerNumbers(const std::string &line) {
  size_t playerNumberListStart = line.find('|') + 1;
  
  return replaceAll(line.substr(playerNumberListStart), " ", ".") + ".";
}

aho_corasick::trie buildTrie(const std::string &line) {
  aho_corasick::trie trie;
  trie.case_insensitive();
  trie.only_whole_words();
  
  std::stringstream winningNumberStream = extractWinningNumbers(line);
  std::string winningNumber;
  while (winningNumberStream >> winningNumber) trie.insert("." + winningNumber + ".");
  
  return trie;
}

size_t getWinningCardsAmount(const std::string &line) {
  aho_corasick::trie trie = buildTrie(line);
  
  auto result = trie.parse_text(extractPlayerNumbers(line));
  
  return result.size();
}

size_t getCardPoints(const std::string &line) {
  size_t winningCardsAmount = getWinningCardsAmount(line);
  
  if (winningCardsAmount == 0) return 0;
  
  return std::pow(2, winningCardsAmount - 1);
}

size_t getAmountOfCardCopies(const InputLines &lines, std::vector<size_t> &copies, size_t originalIdx) {
  size_t winningCardsAmount = getWinningCardsAmount(lines[originalIdx]);
  size_t copyIdxStart = originalIdx + 1, copyIdxEnd = copyIdxStart + winningCardsAmount;
  
  for (size_t copyIdx = copyIdxStart; copyIdx < copyIdxEnd && copyIdx < copies.size(); copyIdx++) {
    copies[copyIdx] += copies[originalIdx];
  }
  
  return copies[originalIdx];
}

int main(int argc, char *argv[]) {
  InputLines lines = readInput("input.txt");
  Benchmarker::initialize(argc, argv);

#ifdef PART1
  Benchmarker::registerBenchmark<size_t>("Day 4-1", [&]() -> size_t {
      size_t totalGamePoints = 0;
      for (const auto &line: lines) {
        totalGamePoints += getCardPoints(line);
      }
      return totalGamePoints;
  });
#endif

#ifdef PART2
  Benchmarker::registerBenchmark<size_t>("Day 4-2", [&]() -> size_t {
      std::vector<size_t> copies(lines.size(), 1);
      size_t totalCards = 0;
      for (size_t copyIdx = 0; copyIdx < copies.size(); copyIdx++) {
        totalCards += getAmountOfCardCopies(lines, copies, copyIdx);
      }
      return totalCards;
  });
#endif
  
  return Benchmarker::run();
}