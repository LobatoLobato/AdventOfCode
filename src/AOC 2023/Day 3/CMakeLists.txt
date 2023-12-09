add_executable(Day_3 "Day 3.cpp")

target_link_libraries(Day_3 Utils Benchmark AhoCorasick)

configure_file(input.txt input.txt COPYONLY)