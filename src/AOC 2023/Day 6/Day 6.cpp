//
// Created by Lobato on 07/12/2023.
//

#include <string>
#include <vector>
#include <sstream>
#include <cmath>

#include "utils.h"
#include "benchmark.h"

using Race = std::pair<size_t, size_t>;
using RaceList = std::vector<Race>;

template<typename T>
T readRaces(const InputLines &lines);

template<>
RaceList readRaces(const InputLines &lines) {
  std::stringstream times(lines[0].substr(lines[0].find(":") + 1));
  std::stringstream distances(lines[1].substr(lines[1].find(":") + 1));
  
  
  RaceList races;
  Race race;
  
  while (times >> race.first && distances >> race.second) {
    races.push_back(race);
  }
  
  return races;
}

template<>
Race readRaces(const InputLines &lines) {
  std::string times = replaceAll(lines[0].substr(lines[0].find(":") + 1), " ", "");
  std::string distances = replaceAll(lines[1].substr(lines[1].find(":") + 1), " ", "");
  
  return {std::stoull(times), std::stoull(distances)};
}

using PressTimeMinMax = std::pair<size_t, size_t>;

PressTimeMinMax calculateMinAndMaxPressTimes(double maxTime, double maxDistance) {
  double delta = std::sqrt(std::pow(maxTime, 2.0) - 4.0 * (maxDistance + 1));
  size_t min = ((maxTime - delta) / 2.0) + 1, max = (maxTime + delta) / 2.0;
  
  return {min, max};
}

int main(int argc, char **argv) {
  InputLines lines = readInput("input.txt");
  
  Benchmarker::initialize(argc, argv);

#ifdef PART1
  Benchmarker::registerBenchmark<size_t>("Day 6-1", [&]() -> size_t {
      RaceList races = readRaces<RaceList>(lines);
      size_t powersSum = 1;
      
      for (auto race: races) {
        PressTimeMinMax ptMinMax = calculateMinAndMaxPressTimes(race.first, race.second);
        powersSum *= ptMinMax.second - ptMinMax.first + 1;
      }
      
      return powersSum;
  });
#endif

#ifdef PART2
  Benchmarker::registerBenchmark<size_t>("Day 6-2", [&]() -> size_t {
      Race race = readRaces<Race>(lines);
      
      PressTimeMinMax ptMinMax = calculateMinAndMaxPressTimes(race.first, race.second);
      return ptMinMax.second - ptMinMax.first + 1;
  });
#endif
  
  return Benchmarker::run();
}