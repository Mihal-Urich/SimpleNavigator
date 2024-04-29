#include "Menu.h"

int main() {
  Graph graph;
  GraphAlgorithms algorithms;
  Menu menu(graph, algorithms);
  menu.Run();
}