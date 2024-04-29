#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

#include "s21_graph.h"
#include "s21_graph_algorithms.h"

int main() {
  Graph A;
  A.LoadGraphFromFile("../matrixes/test2.txt");
  A.Output();

  GraphAlgorithms alg;
  auto anwser7 = alg.SolveTravelingSalesmanProblem(A);
  std::cout << "Optimal TSP route: ";
  for (size_t i = 0; i < anwser7.vertices.size(); ++i) {
    std::cout << anwser7.vertices[i] + 1 << " ";
    if (i < anwser7.vertices.size() - 1) {
      std::cout << " -> ";
    }
  }
  std::cout << "\nTotal distance: " << anwser7.distance;

  // part1
  // auto answer1 = alg.BreadthFirstSearch(A, 9);

  // for (auto i : answer1) {
  //   std::cout << i << " ";
  // }
  // std::cout << std::endl;

  // auto answer2 = alg.DepthFirstSearch(A, 9);

  // for (auto i : answer2) {
  //   std::cout << i << " ";
  // }
  // std::cout << std::endl;

  // part2
  // auto answer3 = alg.GetShortestPathBetweenVertices(A, 7, 10);

  // std::cout << answer3 << std::endl;

  //  auto answer4 = alg.GetShortestPathsBetweenAllVertices(A);
  //
  //  for (auto& i : answer4) {
  //    for (auto j : i) {
  //      std::cout << j << "\t";
  //    }
  //    std::cout << std::endl;
  //  }

  return 0;
}