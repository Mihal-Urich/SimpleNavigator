#include <iostream>
#include <string>

#include "s21_graph.h"
#include "s21_graph_algorithms.h"

const std::string COLOR_DEFAULT = "\033[0m";  // Сброс цвета
const std::string COLOR_HIGHLIGHT = "\033[1;32m";  // Ярко-зеленый текст
const std::string COLOR_WARNING = "\033[1;31m";  // Ярко-красный текст
const std::string COLOR_INFO = "\033[1;36m";  // Ярко-голубой текст

class Menu {
 public:
  // Menu(Graph& graph, GraphAlgorithms& algorithms)
  //     : graph_(graph), algorithms_(algorithms), loaded_file_(false) {}

  Menu(Graph& graph, GraphAlgorithms& algorithms)
      : graph_(graph), algorithms_(algorithms), loaded_file_(false) {}

  void Run();

 private:
  Graph& graph_;
  GraphAlgorithms& algorithms_;
  bool loaded_file_;

  void ClearScreen() { std::cout << "\033[2J\033[1;1H"; }
  std::string ApplyColor(const std::string& text, std::string color) {
    return color + text + COLOR_DEFAULT;
  }

  void ShowMainMenu();
  void ProcessMainMenuChoice(char choice);
  void LoadGraphFromFile();
  void BreadthFirstSearch();
  void DepthFirstSearch();
  void GetShortestPathBetweenVertices();
  void GetShortestPathsBetweenAllVertices();
  void GetLeastSpanningTree();
  void GetSolveTravelingSalesmanProblem();

  void PrintResult(const std::vector<int>& result);
  void PrintResult(const int& result);
  void PrintResult(const std::vector<std::vector<int>>& result);
  void PrintResult(const GraphAlgorithms::TsmResult& result);
  void PrintGraph();
};