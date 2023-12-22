TRAIN = app/train.cpp
TEST = app/test.cpp
AG_UTIL = AG/src/util.c AG/src/type.c AG/src/typeEvolvable.c AG/src/geneticAlgorithm.c
GAME_UTIL = Game/src/TwoPlayerGame.cpp Game/src/TicTacToe.cpp
PLAYER_UTIL = Player/src/DenseNetwork.cpp Player/src/Player.cpp
BINARY = bin/teste
ZIP = teste.zip
AG_FOLDER = AG/include
GAME_FOLDER = Game/include
PLAYER_FOLDER = Player/include
EIGEN_FOLDER = lib/eigen
MINIDNN_FOLDER = lib/MiniDNN/include

all:
	@g++ -std=c++20 -Wall -Werror -g -I$(AG_FOLDER) -I$(GAME_FOLDER) -I$(PLAYER_FOLDER) -I$(EIGEN_FOLDER) -I$(MINIDNN_FOLDER) $(AG_UTIL) $(GAME_UTIL) $(PLAYER_UTIL) $(MAIN) -o $(TRAIN) -lm
	@g++ -std=c++20 -Wall -Werror -g -I$(AG_FOLDER) -I$(GAME_FOLDER) -I$(PLAYER_FOLDER) -I$(EIGEN_FOLDER) -I$(MINIDNN_FOLDER) $(AG_UTIL) $(GAME_UTIL) $(PLAYER_UTIL) $(MAIN) -o $(TEST) -lm

comp_train:
	@g++ -std=c++20 -Wall -Werror -g -I$(AG_FOLDER) -I$(GAME_FOLDER) -I$(PLAYER_FOLDER) -I$(EIGEN_FOLDER) -I$(MINIDNN_FOLDER) $(AG_UTIL) $(GAME_UTIL) $(PLAYER_UTIL) $(MAIN) -o $(TRAIN) -lm

comp_test:
	@g++ -std=c++20 -Wall -Werror -g -I$(AG_FOLDER) -I$(GAME_FOLDER) -I$(PLAYER_FOLDER) -I$(EIGEN_FOLDER) -I$(MINIDNN_FOLDER) $(AG_UTIL) $(GAME_UTIL) $(PLAYER_UTIL) $(MAIN) -o $(TEST) -lm

train:
	@./$(TRAIN)

test:
	@./$(TEST)

valgrind:
	@valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)

clean:
	@rm $(TRAIN) $(TEST) $(ZIP)

zip:
	@zip -r $(ZIP) *