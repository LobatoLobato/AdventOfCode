//
// Created by Lobato on 07/12/2023.
//

#ifndef ADVENTOFCODE_INPUTREADER_H
#define ADVENTOFCODE_INPUTREADER_H

#include <vector>
#include <string>
#include <functional>
#include <optional>
#include <iostream>

using InputLines = std::vector<std::string>;

InputLines readInput(const std::string &fileName);

void readInput(const std::string &fileName, const std::function<void(const std::string &)> &callback);

std::string replaceAll(std::string str, const std::string &from, const std::string &to);

template<typename T>
size_t numlen(T number) {
  return std::to_string(number).size();
}
#endif //ADVENTOFCODE_INPUTREADER_H
