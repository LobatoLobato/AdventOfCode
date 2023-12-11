//
// Created by Lobato on 08/12/2023.
//

#ifndef ADVENTOFCODE_BENCHMARK_H
#define ADVENTOFCODE_BENCHMARK_H

#include <chrono>
#include <string>
#include <functional>

#define DEFAULT_BENCHMARK_RUN_COUNT 100

template<typename T>
void benchmark(const std::string &id, std::function<T()> target, size_t count = DEFAULT_BENCHMARK_RUN_COUNT);

#endif //ADVENTOFCODE_BENCHMARK_H
