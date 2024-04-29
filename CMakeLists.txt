cmake_minimum_required(VERSION 3.5...3.16)
project(A2_SimpleNavigator_v1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall")

set(SOURCE_FILES_ENGINE
        src/s21_graph.h
        src/s21_graph.cc
        src/s21_graph_algorithms.h
        src/s21_graph_algorithms.cc)

set(SOURCE_FILES_VIEW
       src/Menu.h
       src/Menu.cc)

set(VIEW_ENTRY
       src/app.cc)

include_directories(src)

add_library(${PROJECT_NAME}_lib OBJECT ${SOURCE_FILES_ENGINE} ${SOURCE_FILES_VIEW})

add_library(s21_graph STATIC src/s21_graph.cc)
add_library(s21_graph_algorithms STATIC src/s21_graph_algorithms.cc)

add_executable(main ${VIEW_ENTRY})

add_executable(GA_Test src/test_graph_algorithms.cc)
add_executable(G_Test src/test_graph.cc)

target_link_libraries(main PRIVATE ${PROJECT_NAME}_lib)
target_link_libraries(GA_Test PRIVATE ${PROJECT_NAME}_lib)
target_link_libraries(G_Test PRIVATE ${PROJECT_NAME}_lib)
