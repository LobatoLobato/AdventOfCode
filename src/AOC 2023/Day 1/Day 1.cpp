//
// Created by Lobato on 07/12/2023.
//

#include <string>
#include <iostream>
#include <numeric>
#include <vector>

#include "Utils.h"

size_t getCalibrationValue(std::string input, bool includeSpelledDigits = false) {
  const std::string spelledDigits[10] = {
      "zero",
      "one",
      "two",
      "three",
      "four",
      "five",
      "six",
      "seven",
      "eight",
      "nine"
  };
  struct DigitInfo {
      std::string digit;
      size_t pos;
  };
  DigitInfo firstDigitInfo = {.pos = SIZE_MAX};
  DigitInfo lastDigitInfo = {.pos =  0};
  
  auto setDigits = [&](const std::string &searchElement, int digit) {
      size_t pos = input.find(searchElement);
      while (pos != std::string::npos) {
        if (pos <= firstDigitInfo.pos) firstDigitInfo = {std::to_string(digit), pos};
        if (pos >= lastDigitInfo.pos) lastDigitInfo = {std::to_string(digit), pos};
        
        pos = input.find(searchElement, pos + searchElement.length());
      }
  };
  
  for (int digit = 0; digit < 10; digit++) {
    const std::string &spelledDigit = spelledDigits[digit];
    
    if (includeSpelledDigits) setDigits(spelledDigit, digit);
    setDigits(std::to_string(digit), digit);
  }
  
  return stoi(firstDigitInfo.digit + lastDigitInfo.digit);
}

int main() {
  std::vector<std::string> lines = readInput("input.txt");
  size_t sumWithoutSpelledDigits = std::transform_reduce(
      lines.begin(), lines.end(),
      0L, std::plus{},
      [](const std::string &line) -> size_t { return getCalibrationValue(line); }
  );
  std::cout << "Sum (Spelled out digits not included): " << sumWithoutSpelledDigits << std::endl;
  
  size_t sumWithSpelledDigits = std::transform_reduce(
      lines.begin(), lines.end(),
      0L, std::plus{},
      [](const std::string &line) -> size_t { return getCalibrationValue(line, true); }
  );
  std::cout << "Sum (Spelled out digits included): " << sumWithSpelledDigits << std::endl;
  
  return 0;
}