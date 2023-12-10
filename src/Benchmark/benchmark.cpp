//
// Created by Lobato on 08/12/2023.
//
#include "benchmark.h"
#include <iostream>

BenchmarkInfo startBenchmark(const std::string &id) {
  return {.id = id, .startTime = std::chrono::high_resolution_clock::now()};
}

template<typename T>
void endBenchmark(const BenchmarkInfo &benchmarkInfo, const T &result) {
  BenchmarkInfo::time_point endTime = std::chrono::high_resolution_clock::now();
  
  std::chrono::duration<double, std::milli> ms_double = endTime - benchmarkInfo.startTime;
  
  std::cout << "\nBenchmark Result [" << benchmarkInfo.id << "]: \n";
  std::cout << "  Time elapsed: " << ms_double.count() << "ms\n";
  std::cout << "  Result: " << result << "\n\n";
}

template void endBenchmark<size_t>(const BenchmarkInfo &benchmarkInfo, const size_t &result);
template void endBenchmark<long long int>(const BenchmarkInfo &benchmarkInfo, const long long int &result);
template void endBenchmark<std::string>(const BenchmarkInfo &benchmarkInfo, const std::string &result);