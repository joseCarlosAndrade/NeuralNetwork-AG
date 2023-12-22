MAIN = src/main.cpp
UTIL = src/DenseNetwork.cpp src/Player.cpp
AG_UTIL = ../AG/src/util.c ../AG/src/type.c ../AG/src/typeEvolvable.c
GAME_UTIL = ../Game/src/TwoPlayerGame.cpp ../Game/src/TicTacToe.cpp ../Game/src/ConnectFour.cpp
BINARY = bin/teste
ZIP = teste.zip
INCLUDE_FOLDER = include
AG_FOLDER = ../AG/include
GAME_FOLDER = ../Game/include
EIGEN_FOLDER = ../lib/eigen
MINIDNN_FOLDER = ../lib/MiniDNN/include

all:
	@g++ -std=c++20 -Wall -Werror -g -I$(INCLUDE_FOLDER) -I$(AG_FOLDER) -I$(GAME_FOLDER) -I$(EIGEN_FOLDER) -I$(MINIDNN_FOLDER) $(UTIL) $(AG_UTIL) $(GAME_UTIL) $(MAIN) -o $(BINARY) -lm

run:
	@./$(BINARY)

valgrind:
	@valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)

clean:
	@rm $(BINARY) $(ZIP)

zip:
	@zip -r $(ZIP) *