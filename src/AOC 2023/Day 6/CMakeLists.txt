add_executable(Day_6 "Day 6.cpp")

target_link_libraries(Day_6 Utils Benchmark AhoCorasick)

configure_file(input.txt input.txt COPYONLY)