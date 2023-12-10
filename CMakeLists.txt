cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)

# Specify the source file for your code
set(SOURCE_FILES game/main_v2.cpp)

# Specify the paths to Eigen and MiniDNN
set(EIGEN_INCLUDE_DIR lib//eigen)
set(MINIDNN_INCLUDE_DIR lib//MiniDNN//include)
set(INCLUDE_DIR include)

#add libraries
add_library(neural_n src/neural_network.cpp)
add_library(velha src/velha.c)

# Add the include directories
include_directories(${EIGEN_INCLUDE_DIR} ${MINIDNN_INCLUDE_DIR})

# Specify include directories for the library target
target_include_directories(neural_n PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${MINIDNN_INCLUDE_DIR} ${EIGEN_INCLUDE_DIR})
target_include_directories(velha PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add executable target
add_executable(my_executable ${SOURCE_FILES})

# Set optimization level
# target_compile_options(my_executable PRIVATE)

# Link your library to the main executable
target_link_libraries(my_executable neural_n velha)