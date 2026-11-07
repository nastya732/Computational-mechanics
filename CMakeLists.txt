cmake_minimum_required(VERSION 3.16)
project(Kepler LANGUAGES CXX)

# Ищем Eigen
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

# Подключаем папку с библиотекой
add_subdirectory(src)

