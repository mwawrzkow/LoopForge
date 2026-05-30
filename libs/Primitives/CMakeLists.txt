cmake_minimum_required(VERSION 3.14)


project(Primitives)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(CGAL REQUIRED)

set(SRC src/Polygon.cpp)

add_library(${PROJECT_NAME} ${SRC})


target_include_directories(${PROJECT_NAME}
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    CGAL::CGAL
)
