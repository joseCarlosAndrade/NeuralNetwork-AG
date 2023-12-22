MAIN = src/main.cpp
UTIL = src/TwoPlayerGame.cpp src/TicTacToe.cpp src/ConnectFour.cpp
PLAYER_UTIL = ../Player/src/DenseNetwork.cpp
BINARY = bin/teste
ZIP = teste.zip
INCLUDE_FOLDER = include
PLAYER_FOLDER = ../Player/include
EIGEN_FOLDER = ../lib/eigen
MINIDNN_FOLDER = ../lib/MiniDNN/include

all:
	@g++ -Wall -Werror -g -I$(INCLUDE_FOLDER) -I$(PLAYER_FOLDER) -I$(EIGEN_FOLDER) -I$(MINIDNN_FOLDER) $(UTIL) $(PLAYER_UTIL) $(MAIN) -o $(BINARY) -lm

run:
	@./$(BINARY)

valgrind:
	@valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)

clean:
	@rm $(BINARY) $(ZIP)

zip:
	@zip -r $(ZIP) *