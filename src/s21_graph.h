#ifndef ZAMENIT
#define ZAMENIT

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Graph {
 public:
  void LoadGraphFromFile(std::string filename);
  void ExportGraphToDot(std::string filename);

  void Output() {
    for (size_t i = 0; i < size_; ++i) {
      for (size_t j = 0; j < size_; ++j) {
        std::cout << matrix_[i][j] << " ";
      }
      std::cout << std::endl;
    }
    std::cout << size_ << std::endl;
  }

  size_t GetSize() { return size_; }
  std::vector<std::vector<int>> GetMatrix() { return matrix_; }

 private:
  std::vector<std::vector<int>> matrix_;
  size_t size_;
};

#endif  // ZAMENIT