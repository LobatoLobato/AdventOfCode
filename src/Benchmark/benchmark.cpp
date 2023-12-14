//
// Created by Lobato on 08/12/2023.
//
#include "benchmark.h"
#include <benchmark/benchmark.h>
#include "colorprintf.h"

std::map<std::string, std::string> Benchmarker::benchmarkedFunctionResultMap{};
Benchmarker::CustomBenchmarkReporter Benchmarker::customReporter{};

void Benchmarker::initialize(int argc, char **argv) {
  static char arg0Default[] = "benchmark";
  static char *argvDefault = arg0Default;
  if (!argv) {
    argv = &argvDefault;
    argc = 1;
  }
  if (benchmark::ReportUnrecognizedArguments(argc, argv)) exit(1);
  benchmark::Initialize(&argc, argv);
  
}

int Benchmarker::run(benchmark::TimeUnit timeUnit) {
  if (benchmarkedFunctionResultMap.empty()) return 1;
  benchmark::SetDefaultTimeUnit(timeUnit);

#ifdef BENCHMARK_ONLY
  benchmark::RunSpecifiedBenchmarks(&customReporter);
  benchmark::Shutdown();
#else
  benchmark::RunSpecifiedBenchmarks(&customReporter);
  
  printFunctionsResults();
  
  benchmark::Shutdown();
#endif
  return 0;
}

void Benchmarker::printFunctionsResults() {
  printf("----------------------------------------------------\n");
  for (const auto &[id, result]: benchmarkedFunctionResultMap) {
    colorprintf(1, "%s ()", id.c_str());
    colorprintf(3, " => ");
    colorprintf(2, "%s\n", result.c_str());
  }
  printf("----------------------------------------------------\n");
}

template<class T>
void Benchmarker::registerBenchmark(const std::string &id, std::function<T()> target) {
#ifdef BENCHMARK_ONLY
  benchmark::RegisterBenchmark(id, [&](benchmark::State &state) -> void {
      for (auto _: state) benchmark::DoNotOptimize(target());
  })->Repetitions(10);
#else
  benchmark::RegisterBenchmark(id, [&](benchmark::State &state) -> void {
      for (auto _: state) benchmark::DoNotOptimize(target());
    
  })->Complexity();
#endif
  benchmarkedFunctionResultMap.insert_or_assign(id, std::to_string(target()));
}

template<>
void Benchmarker::registerBenchmark(const std::string &id, std::function<std::string()> target) {
#ifdef BENCHMARK_ONLY
  benchmark::RegisterBenchmark(id, [&](benchmark::State &state) -> void {
      for (auto _: state) benchmark::DoNotOptimize(target());
  })->Repetitions(10);
#else
  benchmark::RegisterBenchmark(id, [&](benchmark::State &state) -> void {
      for (auto _: state) benchmark::DoNotOptimize(target());
    
  })->Complexity();
#endif
  benchmarkedFunctionResultMap.insert_or_assign(id, target());
}

template void Benchmarker::registerBenchmark<size_t>(const std::string &, std::function<size_t()>);

template void Benchmarker::registerBenchmark<long long int>(const std::string &, std::function<long long int()>);

template void Benchmarker::registerBenchmark<float>(const std::string &, std::function<float()>);

template void Benchmarker::registerBenchmark<double>(const std::string &, std::function<double()>);

template void Benchmarker::registerBenchmark<long double>(const std::string &, std::function<long double()>);
