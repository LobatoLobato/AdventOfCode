//
// Created by Lobato on 08/12/2023.
//
#include "benchmark.h"
#include <iostream>

#ifndef NO_OUTPUT

struct BenchmarkInfo {
    using system_clock = std::chrono::system_clock;
    using duration = std::chrono::nanoseconds;
    using time_point = std::chrono::time_point<system_clock, duration>;
    
    std::string id;
    time_point startTime;
} benchmarkInfo;

void startBenchmark(const std::string &id) {
  benchmarkInfo = {.id = id, .startTime = std::chrono::high_resolution_clock::now()};
}

template<typename T>
void endBenchmark(const T &result) {
  BenchmarkInfo::time_point endTime = std::chrono::high_resolution_clock::now();
  
  std::chrono::duration<double, std::milli> ms_double = endTime - benchmarkInfo.startTime;
  
  std::cout << "\nBenchmark Result [" << benchmarkInfo.id << "]: \n";
  std::cout << "  Time elapsed: " << ms_double.count() << "ms\n";
  std::cout << "  Result: " << result << "\n\n";
}

template void endBenchmark<size_t>(const size_t &result);
template void endBenchmark<long long int>(const long long int &result);
template void endBenchmark<std::string>(const std::string &result);

#endif