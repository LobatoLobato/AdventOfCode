//
// Created by Lobato on 07/12/2023.
//

#include <iostream>
#include <string>
#include <vector>

#include "utils.h"
#include "benchmark.h"

int main(int argc, char **argv) {
  InputLines lines = readInput("input.txt");
  
  Benchmarker::initialize(argc, argv);

#ifdef PART1
  Benchmarker::registerBenchmark<size_t>("Day X-1", [&]() -> size_t {
  });
#endif

#ifdef PART2
  Benchmarker::registerBenchmark<size_t>("Day X-2", [&]() -> size_t {
  });
#endif
  
  return Benchmarker::run();
}