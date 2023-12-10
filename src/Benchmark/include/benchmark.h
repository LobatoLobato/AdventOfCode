//
// Created by Lobato on 08/12/2023.
//

#ifndef ADVENTOFCODE_BENCHMARK_H
#define ADVENTOFCODE_BENCHMARK_H

#ifdef NO_OUTPUT
#define startBenchmark(id)
#define endBenchmark(result)
#else

#include <chrono>
#include <string>

void startBenchmark(const std::string &id);

template<typename T>
void endBenchmark(const T& result);

#endif

#endif //ADVENTOFCODE_BENCHMARK_H
