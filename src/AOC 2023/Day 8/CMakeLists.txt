add_executable(Day_8 "Day 8.cpp")

target_link_libraries(Day_8 Utils Benchmark AhoCorasick)

configure_file(input.txt input.txt COPYONLY)