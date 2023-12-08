add_executable(Day_2 "Day 2.cpp")

target_link_libraries(Day_2 Utils Benchmark AhoCorasick)

configure_file(input.txt input.txt COPYONLY)