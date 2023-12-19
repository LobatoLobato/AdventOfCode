//
// Created by Lobato on 07/12/2023.
//

#ifndef ADVENTOFCODE_UTILS_H
#define ADVENTOFCODE_UTILS_H

#include <vector>
#include <string>
#include <functional>
#include <optional>
#include <iostream>
#include <sstream>
#include <iterator>

using InputLines = std::vector<std::string>;

InputLines readInput(const std::string &fileName);

void readInput(const std::string &fileName, const std::function<void(const std::string &)> &callback);

std::string replaceAll(std::string str, const std::string &from, const std::string &to);

template<typename T>
size_t numlen(T number) {
  return std::to_string(number).size();
}

template<typename TIn, typename TOut>
std::vector<TOut> map(
    const std::vector<TIn> &inputArray,
    std::function<TOut(TIn, size_t)> mapFunctor,
    bool sort = false
) {
  std::vector<TOut> outputArray;
  
  for (size_t i = 0; i < inputArray.size(); i++) {
    outputArray.push_back(mapFunctor(inputArray[i], i));
  }
  
  if (sort) {
    std::sort(outputArray.begin(), outputArray.end());
  }
  
  return outputArray;
}

template<typename TIn, typename TOut>
TOut reduce(
    const std::vector<TIn> &inputArray,
    std::function<TOut(TOut acc, TIn curr, size_t index)> reduceFunctor,
    TOut initialValue = TOut{}
) {
  TOut output = initialValue;
  
  for (size_t i = 0; i < inputArray.size(); i++) {
    output = reduceFunctor(output, inputArray[i], i);
  }
  
  return output;
}

template<typename T>
std::vector<T> istreamToVector(std::istringstream &sstream) {
  return std::vector<T>{std::istream_iterator<T>{sstream}, std::istream_iterator<T>()};
}

#endif //ADVENTOFCODE_UTILS_H
