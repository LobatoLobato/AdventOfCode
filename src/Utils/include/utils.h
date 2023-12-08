//
// Created by Lobato on 07/12/2023.
//

#ifndef ADVENTOFCODE_INPUTREADER_H
#define ADVENTOFCODE_INPUTREADER_H

#include <vector>
#include <string>
#include <functional>

std::vector<std::string> readInput(const std::string& fileName);
void readInput(const std::string& fileName, const std::function<void(const std::string&)>& callback);


#endif //ADVENTOFCODE_INPUTREADER_H
