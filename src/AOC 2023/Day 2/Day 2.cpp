//
// Created by Lobato on 07/12/2023.
//

#include <string>
#include <iostream>
#include <numeric>
#include <vector>
#include <unordered_map>

#include "utils.h"
#include "benchmark.h"
#include "aho_corasick.hpp"

struct CubeBag {
    size_t red = 0;
    size_t green = 0;
    size_t blue = 0;
    
    [[nodiscard]] bool fitsInto(const CubeBag &compBag) const {
      return red <= compBag.red && green <= compBag.green && blue <= compBag.blue;
    }
    
    [[nodiscard]] size_t getPower() const {
      return red * green * blue;
    }
};

CubeBag getCubeBagMaxAmounts(const std::string &input) {
  std::unordered_map<std::string, size_t> cubeBag = {
      {"red",   0},
      {"green", 0},
      {"blue",  0},
  };
  
  static aho_corasick::trie trie;
  static bool initialize = true;
  if (initialize) {
    trie.case_insensitive();
    trie.insert("red");
    trie.insert("green");
    trie.insert("blue");
    initialize = false;
  }
  
  
  std::string trimmedInput = input.substr(input.find(':') + 2);
  auto result = trie.parse_text(trimmedInput);
  
  size_t cubeAmountStart = 0;
  for (const auto &it: result) {
    std::string keyword = it.get_keyword();
    size_t keywordStart = it.get_start();
    size_t cubeAmountEnd = keywordStart - cubeAmountStart - 1;
    size_t cubeAmount = stoi(trimmedInput.substr(cubeAmountStart, cubeAmountEnd));
    
    if (cubeAmount > cubeBag[keyword]) cubeBag[keyword] = cubeAmount;
    
    cubeAmountStart = keywordStart + keyword.length() + 2;
    if (cubeAmountStart > trimmedInput.length()) break;
  }
  
  return {.red = cubeBag["red"], .green = cubeBag["green"], .blue = cubeBag["blue"]};
}

int main(int argc, char **argv) {
  InputLines lines = readInput("input.txt");
  const CubeBag cubeBagMax = {.red = 12, .green = 13, .blue = 14};
  
  Benchmarker::initialize(argc, argv);

#ifdef PART1
  Benchmarker::registerBenchmark<size_t>("Day 2-1", [&]() -> size_t {
      size_t possibleGamesSum = 0;
      for (const auto &line: lines) {
        CubeBag cubeBag = getCubeBagMaxAmounts(line);
        if (cubeBag.fitsInto(cubeBagMax)) {
          possibleGamesSum += stoi(line.substr(5));
        }
      }
      
      return possibleGamesSum;
  });
#endif

#ifdef PART2
  Benchmarker::registerBenchmark<size_t>("Day 2-2", [&]() -> size_t {
      size_t powersSum = 0;
      for (const auto &line: lines) {
        CubeBag cubeBag = getCubeBagMaxAmounts(line);
        powersSum += cubeBag.getPower();
      }
      return powersSum;
  });
#endif
  
  return Benchmarker::run();
}