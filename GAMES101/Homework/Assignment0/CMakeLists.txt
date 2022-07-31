cmake_minimum_required (VERSION 2.8.12)
project (Transformation)

find_package(Eigen3 REQUIRED)
include_directories("/opt/homebrew/include")

add_executable (Transformation main.cpp)
