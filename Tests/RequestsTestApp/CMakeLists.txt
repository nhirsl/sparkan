cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

project(RequestsTestApp)

add_compile_options(-std=c++14)

include_directories(${Requests_API_DIR})

set(CPP_FILES 
    Source/RequestsTestApp.cpp)

add_executable(${PROJECT_NAME} ${CPP_FILES})

target_link_libraries(${PROJECT_NAME} Requests)
