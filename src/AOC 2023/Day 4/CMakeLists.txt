add_executable(Day_4 "Day 4.cpp")

target_link_libraries(Day_4 Utils Benchmark AhoCorasick)

configure_file(input.txt input.txt COPYONLY)