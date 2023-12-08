//
// Created by Lobato on 07/12/2023.
//
#include "Utils.h"
#include <fstream>

std::vector<std::string> readInput(const std::string &fileName) {
  std::ifstream file(fileName);
  std::vector<std::string> lines;
  
  
  std::string line;
  while (std::getline(file, line)) {
    lines.push_back(line);
  }
  
  return lines;
}

void readInput(const std::string &fileName, const std::function<void(const std::string &)> &callback) {
  std::ifstream file(fileName);
  
  std::string line;
  while (std::getline(file, line)) {
    callback(line);
  }
}