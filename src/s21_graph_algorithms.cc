#include "s21_graph_algorithms.h"

std::vector<int> GraphAlgorithms::DepthFirstSearch(Graph &graph,
                                                   int start_vertex) {
  int size = graph.GetSize();
  std::vector<std::vector<int>> mtx = graph.GetMatrix();
  std::stack<int> stk;
  std::vector<int> visited;

  stk.push(start_vertex - 1);
  while (!stk.empty()) {
    int buffer = stk.top();
    stk.pop();
    if (std::find(visited.begin(), visited.end(), buffer) == visited.end()) {
      visited.push_back(buffer);
    }

    for (int i = size - 1; i >= 0; --i) {
      if ((mtx[buffer][i] != 0) &&
          (std::find(visited.begin(), visited.end(), i) == visited.end())) {
        stk.push(i);
      }
    }
  }

  for (int i = 0; i < size; ++i) {
    visited[i] += 1;
  }

  return visited;
}

std::vector<int> GraphAlgorithms::BreadthFirstSearch(Graph &graph,
                                                     int start_vertex) {
  int size = graph.GetSize();
  std::vector<std::vector<int>> mtx = graph.GetMatrix();
  std::queue<int> cute;
  std::vector<int> visited;
  cute.push(start_vertex - 1);

  while (!cute.empty()) {
    int buffer = cute.front();
    cute.pop();
    if (std::find(visited.begin(), visited.end(), buffer) == visited.end()) {
      visited.push_back(buffer);
    }
    for (int i = 0; i < size; ++i) {
      if ((mtx[buffer][i] != 0) &&
          (std::find(visited.begin(), visited.end(), i) == visited.end())) {
        cute.push(i);
      }
    }
  }
  for (int i = 0; i < size; ++i) {
    visited[i] += 1;
  }

  return visited;
}

int GraphAlgorithms::GetShortestPathBetweenVertices(Graph &graph, int vertex1,
                                                    int vertex2) {
  int size = graph.GetSize();
  std::vector<std::vector<int>> mtx = graph.GetMatrix();
  const size_t V = size;
  std::vector<int> dist(
      V, std::numeric_limits<int>::max());  // Исходные расстояния
                                            // устанавливаются в бесконечность
  std::vector<bool> sptSet(V, false);  // Множество посещенных вершин

  int src = vertex1 - 1;
  int dest = vertex2 - 1;
  dist[src] = 0;  // Расстояние от самой себя до самого себя всегда равно 0

  for (size_t count = 0; count < V - 1; ++count) {
    int u = MinDistance(dist, sptSet, size);
    sptSet[u] = true;

    for (size_t v = 0; v < V; ++v) {
      if (!sptSet[v] && mtx[u][v] &&
          dist[u] != std::numeric_limits<int>::max() &&
          dist[u] + mtx[u][v] < dist[v]) {
        dist[v] = dist[u] + mtx[u][v];
      }
    }
  }

  return dist[dest];
}

// Вспомогательная функция для нахождения вершины с минимальным расстоянием
int GraphAlgorithms::MinDistance(const std::vector<int> &dist,
                                 const std::vector<bool> &sptSet, size_t size) {
  int min = std::numeric_limits<int>::max();
  int min_index = -1;
  for (size_t v = 0; v < size; ++v) {
    if (!sptSet[v] && dist[v] <= min) {
      min = dist[v];
      min_index = v;
    }
  }
  return min_index;
}
std::vector<std::vector<int>>
GraphAlgorithms::GetShortestPathsBetweenAllVertices(Graph &graph) {
  int size = graph.GetSize();
  std::vector<std::vector<int>> mtx = graph.GetMatrix();
  const size_t V = size;

  for (size_t i = 0; i < V; ++i) {
    for (size_t j = 0; j < V; ++j) {
      if (i != j && mtx[i][j] == 0) {
        mtx[i][j] = std::numeric_limits<int>::max();  // Заполняем недостижимые
                                                      // вершины бесконечностью
      }
    }
  }

  for (size_t k = 0; k < V; ++k) {
    for (size_t i = 0; i < V; ++i) {
      for (size_t j = 0; j < V; ++j) {
        if (mtx[i][k] != std::numeric_limits<int>::max() &&
            mtx[k][j] != std::numeric_limits<int>::max() &&
            mtx[i][k] + mtx[k][j] < mtx[i][j]) {
          mtx[i][j] = mtx[i][k] + mtx[k][j];
        }
      }
    }
  }

  return mtx;
}

std::vector<std::vector<int>> GraphAlgorithms::GetLeastSpanningTree(
    Graph &graph) {
  size_t size = graph.GetSize();
  std::vector<std::vector<int>> mtx = graph.GetMatrix();
  std::vector<std::vector<int>> answer(size, std::vector<int>(size, 0));
  std::vector<int> visited;
  int new_vert = 0;
  do {
    visited.push_back(new_vert);
    int min_face = 1000000000;
    int save_i = 0, save_j = 0;
    for (size_t i = 0; i < size; ++i) {
      if (std::find(visited.begin(), visited.end(), i) != visited.end()) {
        for (size_t j = 0; j < size; ++j) {
          if ((mtx[i][j] != 0) && (mtx[i][j] < min_face) &&
              (std::find(visited.begin(), visited.end(), j) == visited.end())) {
            min_face = mtx[i][j];
            save_i = i;
            save_j = j;
          }
        }
      }
    }
    new_vert = save_j;
    answer[save_i][save_j] = mtx[save_i][save_j];
    answer[save_j][save_i] = mtx[save_i][save_j];
  } while (visited.size() != size);
  return answer;
}

GraphAlgorithms::AntColony::AntColony(Graph &graph)
    : graph_(graph),
      numAnts_(graph_.GetSize() * 2),
      alpha_(1.0),
      beta_(2.0),
      rho_(0.2),
      Q_(5.0),
      maxIterations_(2500),
      pheromones_(graph.GetSize(), std::vector<double>(graph.GetSize(), 1.0)),
      initialPheromone_(1.0) {}

GraphAlgorithms::TsmResult GraphAlgorithms::AntColony::Solve() {
  InitializePheromones();
  for (int iteration = 0; iteration < maxIterations_; ++iteration) {
    std::vector<std::vector<double>> summary_pheromone(
        graph_.GetSize(), std::vector<double>(graph_.GetSize(), 0));
    antsResults_.clear();

    for (int antIndex = 0; antIndex < numAnts_; ++antIndex) {
      TsmResult antResult;
      antResult.distance = 0.0;

      std::vector<bool> visited(graph_.GetSize(), false);
      antResult.vertices.push_back(0);

      for (size_t step = 0; step < graph_.GetSize() - 1; ++step) {
        int currentCity = antResult.vertices.back();
        int nextCity = SelectNextCity(currentCity, visited);
        antResult.vertices.push_back(nextCity);
        visited[nextCity] = true;
        antResult.distance += graph_.GetMatrix()[currentCity][nextCity];
      }

      antResult.distance += graph_.GetMatrix()[antResult.vertices.back()][0];
      antsResults_.push_back(antResult);
      for (std::size_t v = 0; v != antResult.vertices.size() - 1; ++v)
        summary_pheromone[antResult.vertices[v]][antResult.vertices[v + 1]] +=
            Q_ / antResult.distance;
    }

    UpdatePheromones(summary_pheromone);
  }

  auto bestResult =
      std::min_element(antsResults_.begin(), antsResults_.end(),
                       [](const TsmResult &a, const TsmResult &b) {
                         return a.distance < b.distance;
                       });

  return *bestResult;
}

void GraphAlgorithms::AntColony::InitializePheromones() {
  for (size_t i = 0; i < graph_.GetSize(); ++i) {
    for (size_t j = 0; j < graph_.GetSize(); ++j) {
      pheromones_[i][j] = initialPheromone_;
    }
  }
}

void GraphAlgorithms::AntColony::UpdatePheromones(
    std::vector<std::vector<double>> &SumPheromone) {
  for (size_t i = 0; i < graph_.GetSize(); ++i) {
    for (size_t j = 0; j < graph_.GetSize(); ++j) {
      pheromones_[i][j] *= (1.0 - rho_);
      if (pheromones_[i][j] < 0.01 && i != j) pheromones_[i][j] = 0.01;
    }
  }

  for (size_t i = 0; i < graph_.GetSize(); ++i) {
    for (size_t j = 0; j < graph_.GetSize(); ++j) {
      pheromones_[i][j] += SumPheromone[i][j];
    }
  }
  for (auto &antResult : antsResults_) {
    if (antResult.vertices.back() != 0) {
      antResult.vertices.push_back(0);
    }
  }
}

double GraphAlgorithms::AntColony::GetVisibility(int i, int j) const {
  return 1.0 / graph_.GetMatrix()[i][j];
}

int GraphAlgorithms::AntColony::SelectNextCity(
    int currentCity, std::vector<bool> &visited) const {
  double sum = 0.0;
  double probability;

  for (size_t i = 0; i < graph_.GetSize(); ++i) {
    if (!visited[i] && graph_.GetMatrix()[currentCity][i] > 0) {
      double pheromone = std::pow(pheromones_[currentCity][i], alpha_);
      double visibility = std::pow(GetVisibility(currentCity, i), beta_);
      sum += pheromone * visibility;
    }
  }

  if (sum == 0.0) {
    for (size_t i = 0; i < graph_.GetSize(); ++i) {
      if (!visited[i]) {
        visited[i] = true;
        return i;
      }
    }
  }

  probability = (rand() / (RAND_MAX + 1.0));

  for (size_t i = 0; i < graph_.GetSize(); ++i) {
    if (!visited[i] && graph_.GetMatrix()[currentCity][i] > 0) {
      double pheromone = std::pow(pheromones_[currentCity][i], alpha_);
      double visibility = std::pow(GetVisibility(currentCity, i), beta_);
      double p = (pheromone * visibility) / sum;

      if (probability <= p && i != 0) {
        visited[i] = true;
        return i;
      }
    }
  }

  for (size_t i = 0; i < graph_.GetSize(); ++i) {
    if (!visited[i] && i != 0) {
      visited[i] = true;
      return i;
    }
  }

  return -1;
}
