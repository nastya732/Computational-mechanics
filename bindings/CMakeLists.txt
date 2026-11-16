if (CMAKE_VERSION VERSION_LESS 3.18)
  set(DEV_MODULE Development)
else()
  set(DEV_MODULE Development.Module)
endif()
find_package(Python 3.10 COMPONENTS Interpreter ${DEV_MODULE} REQUIRED)

# Находим установленный пакет nanobind и подключаем его к CMake
execute_process(
  COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
  OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE nanobind_ROOT)
find_package(nanobind CONFIG REQUIRED)

nanobind_add_module(Kepler bindings.cpp)
target_link_libraries(Kepler PRIVATE KeplerConversions)

# scikit-build-core кладёт результат в корень wheel -> `import Kepler`
install(TARGETS Kepler LIBRARY DESTINATION .)