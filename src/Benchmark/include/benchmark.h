//
// Created by Lobato on 08/12/2023.
//

#ifndef ADVENTOFCODE_BENCHMARK_H
#define ADVENTOFCODE_BENCHMARK_H

#include <chrono>
#include <string>

struct BenchmarkInfo {
    using system_clock = std::chrono::system_clock;
    using duration = std::chrono::nanoseconds;
    using time_point = std::chrono::time_point<system_clock, duration>;
    
    std::string id;
    time_point startTime;
};

BenchmarkInfo startBenchmark(const std::string &id);

template<typename T>
void endBenchmark(const BenchmarkInfo& benchmarkInfo, const T& result);

#endif //ADVENTOFCODE_BENCHMARK_H
