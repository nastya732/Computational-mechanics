cmake_minimum_required(VERSION 3.16)
project(Kepler LANGUAGES CXX)

# Отключаем GNU-расширения (оставляем это глобально, так как нет target-аналога)
set(CMAKE_CXX_EXTENSIONS OFF)
# Полезно для работы автодополнения в VS Code
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 

# Ищем Eigen
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

# Подключаем папку с библиотекой
add_subdirectory(src)

# Создаем исполняемый файл (тестовую программу)
add_executable(kepler_test tests/main.cpp)

# Явно указываем стандарт для теста (PRIVATE)
target_compile_features(kepler_test PRIVATE cxx_std_20)

# Линкуем с нашей библиотекой
target_link_libraries(kepler_test PRIVATE KeplerConversions)

# Указываем, где искать заголовки (чтобы #include "library/..." сработал)
target_include_directories(kepler_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)