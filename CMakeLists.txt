cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)

# Specify the source file for your code
set(SOURCE_FILES app/train.cpp)

# Specify the paths to Eigen and MiniDNN
set(EIGEN_INCLUDE_DIR lib//eigen)
set(MINIDNN_INCLUDE_DIR lib//MiniDNN//include)
set(INCLUDE_DIR include)
set(AG_DIR AG)
set(AG_INCLUDE_DIR AG//include)
set(GAME_DIR game//include)

#add libraries
add_library(AG_lib AG/src/geneticAlgorithm.c AG/src/type.c AG/src/typeEvolvable.c AG/src/util.c)
add_library(player Player/src/Player.cpp)
add_library(denseNetwork Player/src/DenseNetwork.cpp)
add_library(two_game Game/src/TwoPlayerGame.cpp)
add_library(tictactoe Game/src/TicTacToe.cpp)

# Add the include directories
include_directories(${EIGEN_INCLUDE_DIR} ${MINIDNN_INCLUDE_DIR} ${AG_DIR} ${AG_INCLUDE_DIR})

# Specify include directories for the library target

target_include_directories(AG_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/AG/include)
target_include_directories(denseNetwork PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Player/include ${CMAKE_CURRENT_SOURCE_DIR}/Game/include ${CMAKE_CURRENT_SOURCE_DIR}/AG/include ${MINIDNN_INCLUDE_DIR} ${EIGEN_INCLUDE_DIR})
target_include_directories(player PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Player/include ${CMAKE_CURRENT_SOURCE_DIR}/Game/include  ${CMAKE_CURRENT_SOURCE_DIR}/AG/include ${MINIDNN_INCLUDE_DIR} ${EIGEN_INCLUDE_DIR})
target_include_directories(two_game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Game/include ${CMAKE_CURRENT_SOURCE_DIR}/Player/include ${CMAKE_CURRENT_SOURCE_DIR}/AG/include ${MINIDNN_INCLUDE_DIR} ${EIGEN_INCLUDE_DIR})
target_include_directories(tictactoe PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Game/include ${CMAKE_CURRENT_SOURCE_DIR}/Player/include ${CMAKE_CURRENT_SOURCE_DIR}/AG/include ${MINIDNN_INCLUDE_DIR} ${EIGEN_INCLUDE_DIR})

# Add executable target
add_executable(train_AG ${SOURCE_FILES})
add_executable(test app/test.cpp)

# Set optimization level
# target_compile_options(my_executable PRIVATE)

# Link your library to the main executable
target_link_libraries(train_AG AG_lib player denseNetwork two_game tictactoe)
target_link_libraries(test AG_lib player denseNetwork two_game tictactoe)