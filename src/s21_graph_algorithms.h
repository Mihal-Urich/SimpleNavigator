#ifndef ZAMENIT1
#define ZAMENIT1

#include <algorithm>
#include <cmath>
#include <limits>
#include <queue>
#include <stack>

#include "s21_graph.h"

class GraphAlgorithms {
 public:
  struct TsmResult {
    std::vector<int> vertices;
    double distance;
  };

  std::vector<int> DepthFirstSearch(Graph &graph, int start_vertex);
  std::vector<int> BreadthFirstSearch(Graph &graph, int start_vertex);
  int GetShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
  std::vector<std::vector<int>> GetShortestPathsBetweenAllVertices(
      Graph &graph);
  std::vector<std::vector<int>> GetLeastSpanningTree(Graph &graph);
  TsmResult SolveTravelingSalesmanProblem(Graph &graph) {
    AntColony colony(graph);
    return colony.Solve();
  }

 private:
  class AntColony {
   public:
    AntColony(Graph &graph);

    TsmResult Solve();

   private:
    Graph &graph_;
    int numAnts_;
    double alpha_;
    double beta_;
    double rho_;
    double Q_;
    int maxIterations_;

    std::vector<std::vector<double>> pheromones_;
    double initialPheromone_;

    std::vector<TsmResult> antsResults_;

    void InitializePheromones();
    void UpdatePheromones(std::vector<std::vector<double>> &SumPheromone);
    double GetVisibility(int i, int j) const;
    int SelectNextCity(int currentCity, std::vector<bool> &visited) const;
  };
  int MinDistance(const std::vector<int> &dist, const std::vector<bool> &sptSet,
                  size_t size);
};

#endif  // ZAMENIT1