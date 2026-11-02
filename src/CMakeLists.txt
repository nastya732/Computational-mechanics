# Создаем библиотеку с уникальным именем
add_library(KeplerConversions STATIC
    library/KeplerovToRV.cpp
    library/RVToKeplerov.cpp
)

# Задаем стандарт для библиотеки (PUBLIC — передастся всем, кто её использует)
target_compile_features(KeplerConversions PUBLIC cxx_std_20)

# Указываем пути к заголовкам
target_include_directories(KeplerConversions PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/library
)

# Линкуем с Eigen
target_link_libraries(KeplerConversions PUBLIC Eigen3::Eigen)