cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

project(BlockingQueue)

add_compile_options(-std=c++14)

<<<<<<< HEAD
include_directories(Include)

set(${PROJECT_NAME}_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/Include 
    CACHE INTERNAL "${PROJECT_NAME}: Include Directory" FORCE)

=======
set(${PROJECT_NAME}_API_DIR ${PROJECT_SOURCE_DIR}/API 
    CACHE INTERNAL "${PROJECT_NAME}: API Directory" FORCE)

include_directories(API)
include_directories(Include)
    
>>>>>>> nebojsakaran
set(CPP_FILES 
    Source/BlockingQueueFactory.cpp
    Source/NonblockingRecursiveLock.cpp)

add_library(${PROJECT_NAME} SHARED ${CPP_FILES})
