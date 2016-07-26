project (coreservice)

include_directories(include)
include_directories(include/api)

file(GLOB sparkan_HEADER "include/*.h" "*.h" "include/api/*.h")
file(GLOB sparkan_SRCS "*cpp" "*.c" "src/*.cpp" "src/*.c")



cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
cmake_policy(SET CMP0063 NEW)
set(QT_MIN_VERSION "5.3.0")

include_directories ("${PROJECT_SOURCE_DIR}/include")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)

find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(Qt5Core REQUIRED)
#include_directories(${Qt5Core_INCLUDES})


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++1y -pedantic")
add_library(coreservice SHARED ${sparkan_SRCS} ${sparkan_HEADER})
 add_definitions(${Qt5Core_DEFINITIONS})

#install(TARGETS sparkan  ${INSTALL_TARGETS_DEFAULT_ARGS}) 
