project (coreservice)
set(CMAKE_VERBOSE_MAKEFILE ON)
include_directories(include)
include_directories(include/api)
add_definitions(-DCORESERVICE)

file(GLOB coreservice_HEADER "include/*.h" "*.h" "include/api/*.h")
file(GLOB coreservice_SRCS "*cpp" "*.c" "src/*.cpp" "src/*.c")


cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
cmake_policy(SET CMP0063 NEW)
set(QT_MIN_VERSION "5.3.0")
set(CMAKE_AUTOMOC ON)

include_directories ("${PROJECT_SOURCE_DIR}/include")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
    Core
    Network
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++1y -pedantic")

add_library(coreservice SHARED ${coreservice_SRCS} ${coreservice_HEADER})
qt5_use_modules (coreservice Core Network)

#install(TARGETS sparkan  ${INSTALL_TARGETS_DEFAULT_ARGS}) 
