# Тестовые программы
add_executable(kepler_test tests/main.cpp)
add_executable(simple_test tests/prediction_simple.cpp)

# Одни и те же настройки для обоих тестов
foreach(test_target kepler_test simple_test)
    target_compile_features(${test_target} PRIVATE cxx_std_20)
    target_link_libraries(${test_target} PRIVATE KeplerConversions)
endforeach()