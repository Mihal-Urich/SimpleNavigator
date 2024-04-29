#include "Menu.h"

void Menu::Run() {
  char choice;
  while (true) {
    ShowMainMenu();
    std::cout << ApplyColor("Выберите действие: ", COLOR_INFO);
    std::cin >> choice;
    ProcessMainMenuChoice(choice);
  }
}

void Menu::ShowMainMenu() {
  if (!loaded_file_) {
    std::cout << ApplyColor("~~~~~~~~~", COLOR_HIGHLIGHT) << std::endl;
    std::cout << ApplyColor(" M E N U ", COLOR_INFO) << std::endl;
    std::cout << ApplyColor("~~~~~~~~~", COLOR_HIGHLIGHT) << std::endl;
    std::cout << "1. " << ApplyColor("Загрузить граф из файла", COLOR_HIGHLIGHT)
              << "\n";
    std::cout << "0. " << ApplyColor("Выход", COLOR_WARNING) << "\n";
  } else {
    std::cout << ApplyColor("~~~~~~~~~", COLOR_HIGHLIGHT) << std::endl;
    std::cout << ApplyColor(" M E N U ", COLOR_INFO) << std::endl;
    std::cout << ApplyColor("~~~~~~~~~", COLOR_HIGHLIGHT) << std::endl;
    std::cout << "1. " << ApplyColor("Загрузить граф из файла", COLOR_HIGHLIGHT)
              << "\n";
    std::cout << "2. " << ApplyColor("Обход в ширину", COLOR_HIGHLIGHT) << "\n";
    std::cout << "3. " << ApplyColor("Обход в глубину", COLOR_HIGHLIGHT)
              << "\n";
    std::cout << "4. "
              << ApplyColor("Поиск кратчайшего пути между вершинами",
                            COLOR_HIGHLIGHT)
              << "\n";
    std::cout << "5. "
              << ApplyColor("Поиск кратчайших путей между всеми парами вершин",
                            COLOR_HIGHLIGHT)
              << "\n";
    std::cout << "6. "
              << ApplyColor("Поиск минимального остовного дерева",
                            COLOR_HIGHLIGHT)
              << "\n";
    std::cout << "7. "
              << ApplyColor("Решение задачи комивояжера", COLOR_HIGHLIGHT)
              << "\n";
    std::cout << "8. "
              << ApplyColor("Матрица смежности текущего графа", COLOR_HIGHLIGHT)
              << "\n";
    std::cout << "0. " << ApplyColor("Выход", COLOR_WARNING) << "\n";
  }
}

void Menu::ProcessMainMenuChoice(char choice) {
  switch (choice) {
    case '1':
      ClearScreen();
      LoadGraphFromFile();
      break;
    case '2':
      ClearScreen();
      BreadthFirstSearch();
      break;
    case '3':
      ClearScreen();
      DepthFirstSearch();
      break;
    case '4':
      ClearScreen();
      GetShortestPathBetweenVertices();
      break;
    case '5':
      ClearScreen();
      GetShortestPathsBetweenAllVertices();
      break;
    case '6':
      ClearScreen();
      GetLeastSpanningTree();
      break;
    case '7':
      ClearScreen();
      GetSolveTravelingSalesmanProblem();
      break;
    case '8':
      ClearScreen();
      PrintGraph();
      break;
    case '0':
      std::cout << ApplyColor("Выход из программы.", COLOR_WARNING) << "\n";
      exit(0);
    default:
      ClearScreen();
      std::cout << ApplyColor("Некорректный ввод!", COLOR_WARNING) << "\n";
  }
}

void Menu::LoadGraphFromFile() {
  loaded_file_ = false;
  std::string filename;
  std::cout << ApplyColor("Введите имя файла: ", COLOR_INFO);
  std::cin >> filename;
  try {
    graph_.LoadGraphFromFile(filename);
    loaded_file_ = true;
    PrintGraph();
  } catch (...) {
    std::cout << ApplyColor("Неверное имя файла!", COLOR_WARNING) << "\n";
  }
}

void Menu::BreadthFirstSearch() {
  if (loaded_file_) {
    char c_start_vertex;
    std::cout << ApplyColor("Обход в ширину: ", COLOR_INFO);
    std::cin >> c_start_vertex;
    size_t start_vertex = c_start_vertex - '0';
    if (start_vertex <= graph_.GetSize() && start_vertex != 0) {
      auto answer = algorithms_.BreadthFirstSearch(graph_, start_vertex);
      PrintResult(answer);
    } else {
      std::cout << ApplyColor("Нет такой вершины!", COLOR_WARNING) << "\n";
    }
  } else {
    std::cout << ApplyColor("Загрузите файл!", COLOR_WARNING) << "\n";
  }
}

void Menu::DepthFirstSearch() {
  if (loaded_file_) {
    char c_start_vertex;
    std::cout << ApplyColor("Обход в глубину: ", COLOR_INFO);
    std::cin >> c_start_vertex;
    size_t start_vertex = c_start_vertex - '0';
    if (start_vertex <= graph_.GetSize() && start_vertex != 0) {
      auto answer = algorithms_.DepthFirstSearch(graph_, start_vertex);
      PrintResult(answer);
    } else {
      std::cout << ApplyColor("Нет такой вершины!", COLOR_WARNING) << "\n";
    }
  } else {
    std::cout << ApplyColor("Загрузите файл!", COLOR_WARNING) << "\n";
  }
}

void Menu::GetShortestPathBetweenVertices() {
  if (loaded_file_) {
    char c_start, c_end;
    std::cout << ApplyColor("Введите начальную и конечную вершины: ",
                            COLOR_INFO);
    std::cin >> c_start >> c_end;
    size_t i_start = c_start - '0', i_end = c_end - '0';
    if (i_start <= graph_.GetSize() && i_start != 0 &&
        i_end <= graph_.GetSize() && i_end != 0) {
      int answer =
          algorithms_.GetShortestPathBetweenVertices(graph_, i_start, i_end);
      PrintResult(answer);
    } else {
      std::cout << ApplyColor("Нет таких вершин!", COLOR_WARNING) << "\n";
    }
  } else {
    std::cout << ApplyColor("Загрузите файл!", COLOR_WARNING) << "\n";
  }
}

void Menu::GetShortestPathsBetweenAllVertices() {
  if (loaded_file_) {
    std::cout << ApplyColor("Кратчайшие пути между всеми парами вершин: ",
                            COLOR_INFO)
              << "\n";
    auto answer = algorithms_.GetShortestPathsBetweenAllVertices(graph_);
    PrintResult(answer);
  } else {
    std::cout << ApplyColor("Загрузите файл!", COLOR_WARNING) << "\n";
  }
}

void Menu::GetLeastSpanningTree() {
  if (loaded_file_) {
    std::cout << ApplyColor("Минимальное остовное дерево: ", COLOR_INFO)
              << "\n";
    auto answer = algorithms_.GetLeastSpanningTree(graph_);
    PrintResult(answer);
  } else {
    std::cout << ApplyColor("Загрузите файл!", COLOR_WARNING) << "\n";
  }
}

void Menu::GetSolveTravelingSalesmanProblem() {
  if (loaded_file_) {
    std::cout << ApplyColor("Задача коммивояжера: ", COLOR_INFO) << "\n";
    auto answer = algorithms_.SolveTravelingSalesmanProblem(graph_);
    PrintResult(answer);
  } else {
    std::cout << ApplyColor("Загрузите файл!", COLOR_WARNING) << "\n";
  }
}

void Menu::PrintResult(const std::vector<int>& result) {
  for (const auto& value : result) {
    std::cout << value << " ";
  }
  std::cout << "\n";
}

void Menu::PrintResult(const int& result) {
  std::cout << result;
  std::cout << "\n";
}

void Menu::PrintResult(const std::vector<std::vector<int>>& result) {
  for (const auto& row : result) {
    for (auto value : row) {
      std::cout << value << "\t";
    }
    std::cout << "\n";
  }
}

void Menu::PrintResult(const GraphAlgorithms::TsmResult& result) {
  for (const auto& value : result.vertices) {
    std::cout << value << " -> ";
  }
  std::cout << "\nTotal distance: " << result.distance << std::endl;
}

void Menu::PrintGraph() {
  auto mtx = graph_.GetMatrix();
  std::cout << ApplyColor("Размер матрицы: ", COLOR_INFO) << graph_.GetSize()
            << "\n"
            << std::endl;
  for (size_t i = 0; i < graph_.GetSize(); ++i) {
    for (size_t j = 0; j < graph_.GetSize(); ++j) {
      std::cout << mtx[i][j] << "\t";
    }
    std::cout << std::endl;
  }
}
