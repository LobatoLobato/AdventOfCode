//
// Created by Lobato on 08/12/2023.
//
#include "benchmark.h"
#include <iostream>

template<typename T>
void benchmark(const std::string &id, std::function<T()> target, size_t count) {
  using system_clock = std::chrono::system_clock;
  using duration = std::chrono::nanoseconds;
  using time_point = std::chrono::time_point<system_clock, duration>;
  
  double totalTime = 0, averageTime = 0;
  time_point startTime, endTime;
  std::chrono::duration<double, std::milli> execTime;
  
  for (size_t i = 0; i < count; i++) {
    startTime = std::chrono::high_resolution_clock::now();
    target();
    endTime = std::chrono::high_resolution_clock::now();
    
    execTime = endTime - startTime;
    totalTime += execTime.count();
  }
  averageTime = totalTime / count;

#ifdef OUTPUT_EXECUTION_TIME_ONLY
  printf("%f\n", averageTime);
#else
  T result = target();
  std::cout << "\nBenchmark Result [" << id << "]: \n";
  std::cout << "  Elapsed Time: " << averageTime << "ms\n";
  std::cout << "  Result: " << result << "\n\n";
#endif

}

template void benchmark<size_t>(const std::string &id, std::function<size_t()> target, size_t count);
template void benchmark<long long int>(const std::string &id, std::function<long long int()> target, size_t count);
template void benchmark<float>(const std::string &id, std::function<float()> target, size_t count);
template void benchmark<double>(const std::string &id, std::function<double()> target, size_t count);
template void benchmark<long double>(const std::string &id, std::function<long double()> target, size_t count);
template void benchmark<std::string>(const std::string &id, std::function<std::string()> target, size_t count);