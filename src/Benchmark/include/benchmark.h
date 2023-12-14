//
// Created by Lobato on 08/12/2023.
//

#ifndef ADVENTOFCODE_BENCHMARK_H
#define ADVENTOFCODE_BENCHMARK_H

#include <functional>
#include <map>
#include <benchmark/benchmark.h>

class Benchmarker {
public:
    Benchmarker() = delete;
    
    static void initialize(int argc, char **argv);
    
    template<class T>
    static void registerBenchmark(const std::string &id, std::function<T()> target);
    
    static int run(benchmark::TimeUnit timeUnit = benchmark::kMillisecond);


private:
    static class CustomBenchmarkReporter : public ::benchmark::ConsoleReporter {
        bool ReportContext(const Context &context) override { return true; };

#ifdef BENCHMARK_ONLY
        void ReportRuns(const std::vector<Run> &report) override {
          for (auto &run: report) {
            if (run.aggregate_name == "mean") printf("%f\n", run.GetAdjustedRealTime());
          }
        }
#endif
    } customReporter;
    
    static std::map<std::string, std::string> benchmarkedFunctionResultMap;
    
    static void printFunctionsResults();
};

#endif //ADVENTOFCODE_BENCHMARK_H
