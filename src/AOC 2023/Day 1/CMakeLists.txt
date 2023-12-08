add_executable(Day_1 "Day 1.cpp")

target_link_libraries(Day_1 Utils)

configure_file(input.txt input.txt COPYONLY)