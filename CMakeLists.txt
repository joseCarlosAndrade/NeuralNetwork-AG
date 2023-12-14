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
set(AG_DIR AG)
set(AG_INCLUDE_DIR AG//include)

#add libraries
add_library(neural_n src/neural_network.cpp)
add_library(velha src/velha.c)
#AG library
add_library(AG_lib AG/src/geneticAlgorithm.c AG/src/input.c AG/src/type.c AG/src/typeEvolvable.c AG/src/util.c)

# Add the include directories
include_directories(${EIGEN_INCLUDE_DIR} ${MINIDNN_INCLUDE_DIR} ${AG_DIR} ${AG_INCLUDE_DIR})

# Specify include directories for the library target
target_include_directories(neural_n PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${MINIDNN_INCLUDE_DIR} ${EIGEN_INCLUDE_DIR})
target_include_directories(velha PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(AG_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/AG/include)

# Add executable target
add_executable(my_executable ${SOURCE_FILES})

# Set optimization level
# target_compile_options(my_executable PRIVATE)

# Link your library to the main executable
target_link_libraries(my_executable neural_n velha AG_lib)