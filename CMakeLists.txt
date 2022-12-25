project(openMP)

set(CMAKE_CXX_FLAGS "-fopenmp -O0 -g3")

foreach(i RANGE 0 1)
    add_executable("day${i}" "src/day${i}.cpp")
endforeach()
