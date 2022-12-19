project(openMP)

set(CMAKE_CXX_FLAGS "-fopenmp -O0 -g -g3")

set(SOURCES src/day1.cpp)

add_executable(day1 ${SOURCES})
