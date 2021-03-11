cmake_minimum_required(VERSION 3.5)

project(SetGeometry LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(SetGeometry main.cpp polygon.cpp point2d.cpp line2d.cpp AuxFunctions.cpp lattice.cpp domainpoints.cpp)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(SetGeometry PUBLIC OpenMP::OpenMP_CXX)
endif()
