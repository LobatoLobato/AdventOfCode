add_library(Benchmark benchmark.cpp include/benchmark.h)

find_package(benchmark REQUIRED)

target_link_libraries(Benchmark benchmark::benchmark Utils)
target_include_directories(Benchmark PUBLIC include)