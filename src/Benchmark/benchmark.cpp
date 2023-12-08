//
// Created by Lobato on 08/12/2023.
//
#include "benchmark.h"
#include <iostream>

BenchmarkInfo startBenchmark(const std::string &id) {
  return {.id = id, .startTime = std::chrono::high_resolution_clock::now()};
}

void endBenchmark(const BenchmarkInfo& benchmarkInfo) {
  BenchmarkInfo::time_point endTime = std::chrono::high_resolution_clock::now();
  
  std::chrono::duration<double, std::milli> ms_double = endTime - benchmarkInfo.startTime;
  
  std::cout << "\nBenchmark Result [" << benchmarkInfo.id << "]: \n";
  std::cout << "  Time elapsed: " << ms_double.count() << "ms\n\n";
}