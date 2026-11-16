add_executable(kepler_test cpp/main.cpp)
add_executable(simple_test cpp/prediction_simple.cpp)

foreach(test_target kepler_test simple_test)
    target_compile_features(${test_target} PRIVATE cxx_std_20)
    target_link_libraries(${test_target} PRIVATE KeplerConversions)
    add_test(NAME ${test_target} COMMAND ${test_target})
endforeach()