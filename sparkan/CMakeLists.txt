project (sparkan_cli)

include_directories(include)
include_directories(../coreservice/include/api)
#link_directories(../coreservice/)

file(GLOB sparkan_HEADER "include/*.h" "*.h" "../coreservice/include/api/*.h")
file(GLOB sparkan_SRCS "*cpp" "*.c" "src/*.cpp" "src/*.c")
file(GLOB sparkan_RES "res/*qrc")


cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
cmake_policy(SET CMP0063 NEW)
set(QT_MIN_VERSION "5.3.0")

include_directories ("${PROJECT_SOURCE_DIR}/include")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_VERBOSE_MAKEFILE ON)



find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS 
    Core    # QCommandLineParser, QStringLiteral
    Widgets # QApplication
    Quick
    Qml
)


qt5_add_resources(RESOURCES ${sparkan_RES})



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++1y -pedantic -ffunction-sections")
add_executable(sparkan ${sparkan_SRCS} ${sparkan_HEADER} ${RESOURCES})

#


target_link_libraries(sparkan coreservice)

qt5_use_modules (sparkan Core Network Quick Qml Widgets)
