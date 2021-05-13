Project(P5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -O2 --std=c++17")

add_executable(rpn rpn.cpp)
add_executable(cache cache.cpp)
add_executable(dlist dlistTester.cpp)
#add_executable(g1 g1.cpp)
#add_executable(g2 g2.cpp)
#add_executable(g3 g3.cpp)
