#include <cassert>

#include "s21_graph_algorithms.h"

void BFSTest() {
  Graph graph;
  GraphAlgorithms ga;
  graph.LoadGraphFromFile("../src/tests/matrix4.txt");
  auto ender_order = ga.BreadthFirstSearch(graph, 1);
  std::vector<int> correct_enter_order{1,  2, 3,  6,  7,  8, 9, 11,
                                       13, 4, 12, 14, 15, 5, 10};
  assert(ender_order == correct_enter_order);
  std::cout << "BFS Result is correct!" << std::endl;
}

void DFSTest() {
  Graph graph;
  GraphAlgorithms ga;
  graph.LoadGraphFromFile("../src/tests/matrix4.txt");
  auto ender_order = ga.DepthFirstSearch(graph, 1);
  std::vector<int> correct_enter_order{1, 2, 4,  7,  3,  14, 6, 9,
                                       8, 5, 12, 10, 11, 15, 13};
  assert(ender_order == correct_enter_order);
  std::cout << "DFS Result is correct!" << std::endl;
}

void DijkstraTest() {
  Graph graph;
  GraphAlgorithms ga;
  graph.LoadGraphFromFile("../src/tests/matrix4.txt");
  int shortest_path = ga.GetShortestPathBetweenVertices(graph, 1, 5);
  assert(shortest_path == 2);
  std::cout << "DijkstraAlgorithm Result is correct!" << std::endl;
}

void FLoydWorshellTest() {
  Graph graph;
  GraphAlgorithms ga;
  graph.LoadGraphFromFile("../src/tests/matrix4.txt");
  std::vector<std::vector<int>> distance_matrix =
      ga.GetShortestPathsBetweenAllVertices(graph);
  std::vector<std::vector<int>> correct_answer = {
      {0, 1, 1, 2, 2, 1, 1, 1, 1, 2, 1, 2, 1, 2, 2},
      {1, 0, 2, 1, 2, 1, 2, 2, 2, 2, 2, 1, 1, 2, 2},
      {1, 2, 0, 2, 3, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2},
      {2, 1, 2, 0, 3, 2, 1, 2, 2, 1, 1, 2, 1, 1, 2},
      {2, 2, 3, 3, 0, 3, 2, 1, 2, 2, 2, 1, 2, 3, 2},
      {1, 1, 2, 2, 3, 0, 1, 2, 1, 2, 2, 2, 1, 1, 1},
      {1, 2, 1, 1, 2, 1, 0, 2, 2, 2, 1, 1, 1, 2, 1},
      {1, 2, 2, 2, 1, 2, 2, 0, 1, 2, 1, 1, 1, 2, 1},
      {1, 2, 2, 2, 2, 1, 2, 1, 0, 2, 2, 1, 2, 1, 2},
      {2, 2, 2, 1, 2, 2, 2, 2, 2, 0, 1, 1, 2, 1, 1},
      {1, 2, 2, 1, 2, 2, 1, 1, 2, 1, 0, 1, 2, 2, 1},
      {2, 1, 2, 2, 1, 2, 1, 1, 1, 1, 1, 0, 1, 2, 2},
      {1, 1, 2, 1, 2, 1, 1, 1, 2, 2, 2, 1, 0, 2, 2},
      {2, 2, 1, 1, 3, 1, 2, 2, 1, 1, 2, 2, 2, 0, 1},
      {2, 2, 2, 2, 2, 1, 1, 1, 2, 1, 1, 2, 2, 1, 0}};
  assert(distance_matrix == correct_answer);
  std::cout << "FLoydWorshellAlgorithm Result is correct!" << std::endl;
}

void PrimTest() {
  Graph graph;
  GraphAlgorithms ga;
  graph.LoadGraphFromFile("../src/tests/matrix4.txt");
  std::vector<std::vector<int>> spanning_tree = ga.GetLeastSpanningTree(graph);
  std::cout << "PrimAlgorithm Result is correct!" << std::endl;
}

int main() {
  BFSTest();
  DFSTest();
  DijkstraTest();
  FLoydWorshellTest();
  PrimTest();
}
