//
// Created by Lobato on 07/12/2023.
//
#include "utils.h"
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

std::string replaceAll(std::string str, const std::string& from, const std::string& to) {
  size_t start_pos = 0;
  while((start_pos = str.find(from, start_pos)) != std::string::npos) {
    str.replace(start_pos, from.length(), to);
    start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
  }
  return str;
}