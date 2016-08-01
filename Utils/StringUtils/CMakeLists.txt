cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

project(StringUtils)

add_compile_options(-std=c++14)

include_directories(Include)

SET(${PROJECT_NAME}_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/Include 
    CACHE INTERNAL "${PROJECT_NAME}: Include Directory" FORCE)

set(CPP_FILES Source/StringUtils.cpp)

add_library(${PROJECT_NAME} SHARED ${CPP_FILES})
