#include "s21_graph.h"

void FileReadTest() {
  Graph test;
  try {
    for (const auto &path :
         {"../src/tests/matrix1.txt", "../src/tests/matrix2.txt",
          "../src/tests/matrix3.txt", "../src/tests/matrix4.txt",
          "../src/tests/matrix5.txt", "../src/tests/matrix6.txt",
          "../src/tests/matrix7.txt", "../src/tests/matrix8.txt",
          "../src/tests/matrix9.txt"})
      test.LoadGraphFromFile(path);
  } catch (...) {
    std::cout << "Неверное имя файла!"
              << "\n";
  }
  std::cout << "File read test correct!"
            << "\n";
}

// void DotTest() {
//   Graph test;
//   test.ExportGraphToDot("../src/tests/matrix1.txt");
//   test.Output();
// }

int main() {
  FileReadTest();
  //   DotTest();
}
