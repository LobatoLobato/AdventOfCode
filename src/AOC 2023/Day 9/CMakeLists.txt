add_executable(Day_9 "Day 9.cpp")

target_link_libraries(Day_9 Utils Benchmark AhoCorasick)

configure_file(input.txt input.txt COPYONLY)