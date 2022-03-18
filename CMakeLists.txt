cmake_minimum_required(VERSION 3.10)
project(franka_control)

# minimum C++ version
set(CMAKE_CXX_STANDARD 11)

# include header files
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

# define source files
file(GLOB_RECURSE FRANKA_CONTROL_SRC ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)
add_executable(franka_control ${FRANKA_CONTROL_SRC})

# link libraries 
target_link_libraries(franka_control PUBLIC Franka:Franka Eigen3:Eigen3 cppzmq)