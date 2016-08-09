cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

project(Requests)

add_compile_options(-std=c++14)

<<<<<<< HEAD
SET(${PROJECT_NAME}_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/Include 
    CACHE INTERNAL "${PROJECT_NAME}: Include Directory" FORCE)

set(INCLUDE_DIRS)
set(INCLUDE_DIRS ${INCLUDE_DIRS} Include)
set(INCLUDE_DIRS ${INCLUDE_DIRS} ${StringUtils_INCLUDE_DIR})
set(INCLUDE_DIRS ${INCLUDE_DIRS} ${ThreadPool_INCLUDE_DIR})
=======
SET(${PROJECT_NAME}_API_DIR ${PROJECT_SOURCE_DIR}/API 
    CACHE INTERNAL "${PROJECT_NAME}: API Directory" FORCE)

set(INCLUDE_DIRS)
set(INCLUDE_DIRS ${INCLUDE_DIRS} API)
set(INCLUDE_DIRS ${INCLUDE_DIRS} Include)
set(INCLUDE_DIRS ${INCLUDE_DIRS} ${StringUtils_INCLUDE_DIR})
set(INCLUDE_DIRS ${INCLUDE_DIRS} ${ThreadPool_API_DIR})
>>>>>>> nebojsakaran

set(REQUIRED_LIBS)
set(REQUIRED_LIBS ${REQUIRED_LIBS} StringUtils)
set(REQUIRED_LIBS ${REQUIRED_LIBS} ThreadPool)

find_package(CURL)
if(CURL_FOUND)
    set(INCLUDE_DIRS ${INCLUDE_DIRS} ${CURL_INCLUDE_DIR})
    set(REQUIRED_LIBS ${REQUIRED_LIBS} ${CURL_LIBRARIES})
else(CURL_FOUND)
    message(FATAL_ERROR "Could not find the CURL library and development files.")
endif(CURL_FOUND)

include_directories(${INCLUDE_DIRS})

set(CPP_FILES 
    Source/CurlDeliveredDataHandler.cpp
<<<<<<< HEAD
    Source/DeleteRequest.cpp
    Source/GetRequest.cpp
    Source/PostRequest.cpp
    Source/PutRequest.cpp
    Source/RequestImpl.cpp
    Source/RequestsImpl.cpp
    Source/RequestWithContent.cpp
=======
    Source/RequestImpl.cpp
    Source/RequestBuilder.cpp
    Source/RequestBuilderImpl.cpp
    Source/RequestsImpl.cpp
>>>>>>> nebojsakaran
    Source/ResponseBuilder.cpp
    Source/ResponseImpl.cpp
    Source/IncommingTask.cpp
    Source/Requests.cpp)

add_library(${PROJECT_NAME} SHARED ${CPP_FILES})

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS})
