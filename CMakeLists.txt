cmake_minimum_required(VERSION 3.10)
project(bezierCurve)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Gather source files
file(GLOB SRC_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} ${SRC_FILES})

# Include project headers
target_include_directories(${PROJECT_NAME} PRIVATE
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/libs"
)

#--------------------#
# External Libraries #
#--------------------#
find_package(raylib REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    raylib
)
