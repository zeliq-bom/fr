cmake_minimum_required(VERSION 3.13)
project(fr)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_COMPILER gcc)

# Add source files
file(GLOB SOURCES *.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

# Link against required libraries
target_link_libraries(${PROJECT_NAME}
stdc++
pthread
)
