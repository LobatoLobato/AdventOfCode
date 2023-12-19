//
// Created by Lobato on 07/12/2023.
//

#include <string>
#include <vector>
#include <forward_list>
#include <numeric>

#include "utils.h"
#include "benchmark.h"

class NavigationMap {
public:
    using Node = std::pair<std::string, std::string>;
    
    NavigationMap(bool ghostMode = false) : ghostMode(ghostMode) {}
    
    static NavigationMap from(const InputLines &inputLines, bool ghostMode = false) {
      using NodeTuple = std::tuple<std::string, std::string, std::string>;
      auto readNode = [](const std::string &line) -> NodeTuple {
          std::string nodeName, leftNodeName, rightNodeName;
          for (char character: line) {
            if (!std::isalpha(character) && !std::isdigit(character)) continue;
            if (nodeName.size() < 3) nodeName.push_back(character);
            else if (leftNodeName.size() < 3) leftNodeName.push_back(character);
            else if (rightNodeName.size() < 3) rightNodeName.push_back(character);
            else break;
          }
          
          return {nodeName, leftNodeName, rightNodeName};
      };
      NavigationMap navigationMap(ghostMode);
      
      for (size_t i = 1; i < inputLines.size(); i++) {
        if (inputLines[i].empty()) continue;
        
        auto node = readNode(inputLines[i]);
        navigationMap.insert(std::get<0>(node), std::get<1>(node), std::get<2>(node));
      }
      
      return navigationMap;
    }
    
    void insert(const std::string &source, const std::string &left, const std::string &right) {
      nodeMap.insert_or_assign(source, Node{left, right});
      
      if (ghostMode && source.ends_with('A')) { nodeStarts.push_back(source); }
      if (!ghostMode && source == "AAA") { nodeStarts.push_back(source); }
    }
    
    size_t navigate(const std::string &instructions) {
      using RunningNode = std::tuple<std::string, size_t>;
      std::vector<std::tuple<std::string, size_t>> runningNodes = map<std::string, RunningNode>(
          nodeStarts,
          [](std::string startNode, size_t) -> RunningNode { return {startNode, 0}; }
      );
      
      size_t finishedNodes = 0;
      size_t instructionIndex = 0;
      while (finishedNodes != runningNodes.size()) {
        char instruction = instructions[instructionIndex++ % instructions.size()];
        
        for (auto &[nextNode, numberOfInstructions]: runningNodes) {
          if (numberOfInstructions != 0) continue;
          
          nextNode = instruction == 'L' ? nodeMap.at(nextNode).first : nodeMap.at(nextNode).second;
          
          if ((ghostMode && nextNode.ends_with("Z")) || (!ghostMode && nextNode == "ZZZ")) {
            numberOfInstructions = instructionIndex;
            finishedNodes++;
          }
        }
      }
      auto reduceFunctor = [](size_t acc, auto node, size_t) -> size_t {
          return std::lcm((acc == 0) ? 1 : acc, std::get<1>(node));
      };
      return reduce<RunningNode, size_t>(runningNodes, reduceFunctor);
    }

private:
    std::unordered_map<std::string, Node> nodeMap;
    std::vector<std::string> nodeStarts;
    bool ghostMode;
};

int main(int argc, char **argv) {
  InputLines lines = readInput("input.txt");
  
  Benchmarker::initialize(argc, argv);

#ifdef PART1
  Benchmarker::registerBenchmark<size_t>("Day 8-1", [&]() -> size_t {
      std::string instructions = lines[0];
      return NavigationMap::from(lines).navigate(instructions);
  });
#endif

#ifdef PART2
  Benchmarker::registerBenchmark<size_t>("Day 8-2", [&]() -> size_t {
      std::string instructions = lines[0];
      return NavigationMap::from(lines, true).navigate(instructions);
  });
#endif
  
  return Benchmarker::run();
}