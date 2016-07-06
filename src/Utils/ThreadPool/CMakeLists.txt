cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

project(ThreadPool)

add_compile_options(-std=c++14)

SET(${PROJECT_NAME}_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/Include 
    CACHE INTERNAL "${PROJECT_NAME}: Include Directory" FORCE)

include_directories(${BlockingQueue_INCLUDE_DIR})
include_directories(Include)

set(CPP_FILES 
    Source/FixedThreadPool.cpp 
    Source/ThreadPoolFactory.cpp)

add_library(${PROJECT_NAME} SHARED ${CPP_FILES})

target_link_libraries(${PROJECT_NAME} BlockingQueue)
