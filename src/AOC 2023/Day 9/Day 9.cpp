//
// Created by Lobato on 07/12/2023.
//

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>

#include "utils.h"
#include "benchmark.h"

intmax_t predict(const std::vector<intmax_t> intervals, bool predictLeft) {
  std::vector<intmax_t> newIntervals;
  
  bool allZeroes = true;
  intmax_t prevNumber = intervals[0];
  for (size_t i = 1; i < intervals.size(); i++) {
    const intmax_t &currNumber = intervals[i];
    const intmax_t interval = currNumber - prevNumber;
    
    newIntervals.push_back(interval);
    
    if (interval != 0) { allZeroes = false; }
    prevNumber = currNumber;
  }
  
  intmax_t edgeInterval = predictLeft ? intervals.front() : intervals.back();
  if (allZeroes) { return edgeInterval; }
  
  intmax_t prediction = predict(newIntervals, predictLeft);
  return predictLeft ? edgeInterval - prediction : edgeInterval + prediction;
}

intmax_t predict(const std::string &line, bool predictLeft = false) {
  std::istringstream numberHistory(line);
  return predict(istreamToVector<intmax_t>(numberHistory), predictLeft);
}

int main(int argc, char **argv) {
  InputLines lines = readInput("input.txt");
  
//  size_t sum = reduce<std::string, size_t>(lines, [](size_t acc, std::string line, size_t) -> size_t {
//      return acc + predict(line);
//  });
//
//  std::cout << sum << std::endl;
//
//  sum = reduce<std::string, size_t>(lines, [](size_t acc, std::string line, size_t) -> size_t {
//      return acc + predict(line, true);
//  });
//  std::cout << sum << std::endl;
//  return 0;
  Benchmarker::initialize(argc, argv);

#ifdef PART1
  Benchmarker::registerBenchmark<size_t>("Day 9-1", [&]() -> size_t {
      return reduce<std::string, size_t>(lines, [](size_t acc, std::string line, size_t) -> size_t {
          return acc + predict(line);
      });
  });
#endif

#ifdef PART2
  Benchmarker::registerBenchmark<size_t>("Day 9-2", [&]() -> size_t {
    return reduce<std::string, size_t>(lines, [](size_t acc, std::string line, size_t) -> size_t {
        return acc + predict(line, true);
    });
  });
#endif
  
  return Benchmarker::run();
}