add_executable(Day_7 "Day 7.cpp")

target_link_libraries(Day_7 Utils Benchmark AhoCorasick)

configure_file(input.txt input.txt COPYONLY)