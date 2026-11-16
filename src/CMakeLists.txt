add_library(KeplerConversions STATIC
    library/KeplerToRV.cpp
    library/RVToKepler.cpp
    library/Anomalies.cpp
    library/OrbitalPrediction.cpp
)

target_compile_features(KeplerConversions PUBLIC cxx_std_20)

target_include_directories(KeplerConversions PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/library)

target_link_libraries(KeplerConversions PUBLIC Eigen3::Eigen)

set_target_properties(KeplerConversions PROPERTIES POSITION_INDEPENDENT_CODE ON)