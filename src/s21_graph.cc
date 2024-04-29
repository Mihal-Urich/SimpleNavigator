#include "s21_graph.h"

void Graph::LoadGraphFromFile(std::string filename) {
  matrix_.clear();

  std::string str;
  std::ifstream file;
  file.open(filename);
  if (!file.is_open()) {
    throw std::invalid_argument("No correct file");
  }
  std::getline(file, str);
  std::istringstream size(str);
  size >> size_;

  for (size_t i = 0; i < size_; ++i) {
    std::getline(file, str);
    std::istringstream line(str);
    std::vector<int> buffer_line;
    int number = 0;
    for (size_t j = 0; j < size_; ++j) {
      line >> number;
      buffer_line.push_back(number);
    }
    matrix_.push_back(buffer_line);
  }
  file.close();
}

void Graph::ExportGraphToDot(std::string filename) {
  std::ofstream file(filename + ".dot");
  file << "graph " << filename << " {" << std::endl;
  for (size_t i = 0; i < size_; ++i) {
    file << "\t" << i + 1 << ";" << std::endl;
  }
  for (size_t i = 0; i < size_; ++i) {
    for (size_t j = i; j < size_; ++j) {
      if (matrix_[i][j] != 0) {
        file << "\t" << i + 1 << " -- " << j + 1 << ";" << std::endl;
      }
    }
  }
  file << "}" << std::endl;
  file.close();
}
