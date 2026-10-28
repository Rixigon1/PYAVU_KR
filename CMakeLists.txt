cmake_minimum_required(VERSION 3.19)

project(PAYVU_KR LANGUAGES CXX)

add_executable(PAYVU_KR
    src/main.cpp
    src/dataStructures.h
    src/dataStructures.cpp
    src/menuFunctions.h
    src/menuFunctions.cpp
    src/utils.h
    src/utils.cpp
)

target_compile_features(PAYVU_KR PRIVATE cxx_std_20)


