//
// Created by Lobato on 07/12/2023.
//

#include <string>
#include <iostream>
#include <vector>
#include <optional>

#include "utils.h"
#include "benchmark.h"

class LineIterator {
public:
    LineIterator(const std::vector<std::string> &lines, size_t lineIdx) {
      this->line = "." + lines[lineIdx] + ".";
      this->prevLine = (lineIdx > 0) ? ("." + lines[lineIdx - 1] + ".") : "";
      this->nextLine = (lineIdx < lines.size() - 1) ? ("." + lines[lineIdx + 1] + ".") : "";
      this->characterIdx = 0;
    }
    
    inline size_t next() { return this->characterIdx < line.length() ? ++this->characterIdx : this->characterIdx; }
    
    inline size_t prev() { return this->characterIdx > 0 ? --this->characterIdx : this->characterIdx; }
    
    [[nodiscard]] inline size_t reachedEndOfLine() const { return this->characterIdx >= (this->getLineLength()); }
    
    [[nodiscard]] inline bool isDigit() const {
      return std::isdigit(this->line[characterIdx]);
    }
    
    [[nodiscard]] inline bool isAsterisk() const {
      return this->line[characterIdx] == '*';
    }
    
    [[nodiscard]] inline bool hasAdjacentSymbols() const {
      const char prevLineCharacter = !prevLine.empty() ? prevLine[characterIdx] : '.';
      const char nextLineCharacter = !nextLine.empty() ? nextLine[characterIdx] : '.';
      return isSymbol(prevLineCharacter) || isSymbol(nextLineCharacter);
    }
    
    [[nodiscard]] inline std::optional<size_t> isNumberWithAdjacentSymbols() {
      const size_t baseIdx = this->characterIdx;
      static auto goToEndOfNumber = [&] { while (isDigit()) this->next(); };
      
      if (isSymbol(line[this->prev()]) || hasAdjacentSymbols()) {
        this->next();
        goToEndOfNumber();
        
        return stoi(line.substr(baseIdx));
      }
      
      while (std::isdigit(line[this->next()])) {
        if (hasAdjacentSymbols()) {
          goToEndOfNumber();
          return stoi(line.substr(baseIdx));
        }
      }
      
      if (isSymbol(line[characterIdx]) || hasAdjacentSymbols()) {
        return stoi(line.substr(baseIdx));
      }
      
      return std::nullopt;
    }
    
    [[nodiscard]] inline std::vector<size_t> hasAdjacentNumbers() const {
      std::vector<size_t> adjacentNumbers;
      
      for (int i = 0; i < 3; i++) {
        const size_t idx = characterIdx - 1 + i;
        static auto prevIsDigit = [&](const std::string &l) -> bool {
            return i > 0 && std::isdigit(l[idx - 1]);
        };
        
        if (std::isdigit(line[idx]) && !prevIsDigit(line)) {
          adjacentNumbers.push_back(extractNumber(line, idx));
        }
        
        if (!prevLine.empty() && std::isdigit(prevLine[idx]) && !prevIsDigit(prevLine)) {
          adjacentNumbers.push_back(extractNumber(prevLine, idx));
        }
        
        if (!nextLine.empty() && std::isdigit(nextLine[idx]) && !prevIsDigit(nextLine)) {
          adjacentNumbers.push_back(extractNumber(nextLine, idx));
        }
      }
      
      return adjacentNumbers;
    };
    
    [[nodiscard]] inline size_t getLineLength() const {
      return this->line.length();
    }
    
    operator char() {
      return line[characterIdx];
    }

private:
    std::string line, prevLine, nextLine;
    size_t characterIdx;

private:
    [[nodiscard]] static inline bool isSymbol(char character) {
      return character != '.' && !std::isdigit(character);
    }
    
    [[nodiscard]] static inline size_t extractNumber(const std::string &line, size_t idx) {
      while (std::isdigit(line[--idx]));
      return stoi(line.substr(idx + 1));
    }
};

size_t getLinePartNumbersSum(const std::vector<std::string> &lines, size_t lineIdx) {
  LineIterator lineIterator(lines, lineIdx);
  size_t partNumbersSum = 0;
  
  while (!lineIterator.reachedEndOfLine()) {
    if (!lineIterator.isDigit()) {
      lineIterator.next();
      continue;
    }
    
    partNumbersSum += lineIterator.isNumberWithAdjacentSymbols().value_or(0);
    
    lineIterator.next();
  }
  
  return partNumbersSum;
}

size_t getLineGearRatiosSum(const std::vector<std::string> &lines, size_t lineIdx) {
  LineIterator lineIterator(lines, lineIdx);
  size_t gearRatioSum = 0;
  
  while (!lineIterator.reachedEndOfLine()) {
    if (!lineIterator.isAsterisk()) {
      lineIterator.next();
      continue;
    }
    
    std::vector<size_t> adjacentNumbers = lineIterator.hasAdjacentNumbers();
    if (adjacentNumbers.size() == 2) {
      gearRatioSum += adjacentNumbers[0] * adjacentNumbers[1];
    }
    
    lineIterator.next();
  }
  
  return gearRatioSum;
}

int main(int argc, char **argv) {
  std::vector<std::string> lines = readInput("input.txt");
  Benchmarker::initialize(argc, argv);

#ifdef PART1
  Benchmarker::registerBenchmark<size_t>("Day 3-1", [&]() -> size_t {
      size_t partNumbersSum = 0;
      for (size_t i = 0; i < lines.size(); i++) {
        partNumbersSum += getLinePartNumbersSum(lines, i);
      }
      
      return partNumbersSum;
  });
#endif

#ifdef PART2
  Benchmarker::registerBenchmark<size_t>("Day 3-2", [&]() -> size_t {
      size_t gearRatiosSum = 0;
      for (size_t i = 0; i < lines.size(); i++) {
        gearRatiosSum += getLineGearRatiosSum(lines, i);
      }
      
      return gearRatiosSum;
  });
#endif
  
  return Benchmarker::run();
}