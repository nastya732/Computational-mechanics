cmake_minimum_required(VERSION 3.16)
project(Kepler LANGUAGES CXX)

option(KEPLER_PYTHON "Собрать Python-модуль (nanobind)" OFF)

# Ищем Eigen
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

# Подключаем папку с библиотекой
add_subdirectory(src)

if (KEPLER_TESTS)
    find_package(GTest REQUIRED)
    include(GoogleTest)
    enable_testing()
    add_subdirectory(tests)
endif()

if (KEPLER_PYTHON)
    add_subdirectory(bindings)
endif()