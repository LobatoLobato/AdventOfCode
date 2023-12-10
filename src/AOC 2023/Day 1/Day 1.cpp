//
// Created by Lobato on 07/12/2023.
//

#include <string>
#include <iostream>
#include <numeric>
#include <vector>
#include <unordered_map>
#include <chrono>

#include "utils.h"
#include "benchmark.h"
#include "aho_corasick.hpp"


size_t getCalibrationValue(std::string input, bool includeSpelledDigits = false) {
  static const std::unordered_map<std::string, std::string> spelledDigitToDigit = {
      {"zero",  "0"},
      {"one",   "1"},
      {"two",   "2"},
      {"three", "3"},
      {"four",  "4"},
      {"five",  "5"},
      {"six",   "6"},
      {"seven", "7"},
      {"eight", "8"},
      {"nine",  "9"},
  };
  static aho_corasick::trie digitsTrie;
  static aho_corasick::trie digitsAndSpelledDigitsTrie;
  static bool initialize = true;
  
  if (initialize) {
    digitsTrie.case_insensitive();
    digitsAndSpelledDigitsTrie.case_insensitive();
    
    for (auto [spelledDigit, digit]: spelledDigitToDigit) {
      digitsTrie.insert(digit);
      digitsAndSpelledDigitsTrie.insert(digit);
      digitsAndSpelledDigitsTrie.insert(spelledDigit);
    }
    initialize = false;
  }
  
  static auto getDigit = [](std::vector<aho_corasick::emit<char>>::iterator it) {
      return spelledDigitToDigit.contains(it->get_keyword())
             ? spelledDigitToDigit.at(it->get_keyword())
             : it->get_keyword();
  };
  
  auto parseResult = includeSpelledDigits
                     ? digitsAndSpelledDigitsTrie.parse_text(input)
                     : digitsTrie.parse_text(input);
  
  return !parseResult.empty()
         ? stoi(getDigit(parseResult.begin()) + getDigit(--parseResult.end()))
         : 0;
}

int main() {
  std::vector<std::string> lines = readInput("input.txt");
  
  BenchmarkInfo benchmarkInfo = startBenchmark("Sum without spelled Digits");
  
  size_t sumWithoutSpelledDigits = 0;
  for (const auto &line: lines) {
    sumWithoutSpelledDigits += getCalibrationValue(line);
  }
  endBenchmark(benchmarkInfo, sumWithoutSpelledDigits);
  
  benchmarkInfo = startBenchmark("Sum with spelled digits");
  
  size_t sumWithSpelledDigits = 0;
  for (const auto &line: lines) {
    sumWithSpelledDigits += getCalibrationValue(line, true);
  }
  endBenchmark(benchmarkInfo, sumWithSpelledDigits);
  
  return 0;
}