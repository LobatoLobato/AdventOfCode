//
// Created by Lobato on 07/12/2023.
//
#include "utils.h"
#include <fstream>
#include <cstring>

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

std::string replaceAll(std::string str, const std::string &from, const std::string &to) {
  size_t start_pos = 0;
  while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
    str.replace(start_pos, from.length(), to);
    start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
  }
  return str;
}

template<typename T>
std::optional<T> extractCLIArgValue(const char *arg, int argc, char *argv[])
{
  std::optional<const char *> argValue = extractCLIArgValue<const char *>(arg, argc, argv);
  if (!argValue.has_value()) return std::nullopt;
  
  if (typeid(T) == typeid(size_t)) return std::stoull(argValue.value());
  else if (typeid(T) == typeid(long long int)) return std::stoll(argValue.value());
  else if (typeid(T) == typeid(float)) return std::stof(argValue.value());
  else if (typeid(T) == typeid(double)) return std::stod(argValue.value());
  else if (typeid(T) == typeid(long double)) return std::stold(argValue.value());
  
  return std::nullopt;
}

template<>
std::optional<const char *> extractCLIArgValue(const char *arg, int argc, char *argv[]) {
  for (size_t argIdx = 0; argIdx < argc; argIdx++) {
    if (strcmp(arg, argv[argIdx]) == 0 && (argIdx + 1) < argc) {
      return argv[argIdx + 1];
    }
  }
  return std::nullopt;
}

template std::optional<size_t> extractCLIArgValue(const char *arg, int argc, char *argv[]);
template std::optional<long long int> extractCLIArgValue(const char *arg, int argc, char *argv[]);
template std::optional<float> extractCLIArgValue(const char *arg, int argc, char *argv[]);
template std::optional<double> extractCLIArgValue(const char *arg, int argc, char *argv[]);
template std::optional<long double> extractCLIArgValue(const char *arg, int argc, char *argv[]);