add_executable(Day_X "Day X.cpp")

target_link_libraries(Day_X Utils Benchmark AhoCorasick)

configure_file(input.txt input.txt COPYONLY)