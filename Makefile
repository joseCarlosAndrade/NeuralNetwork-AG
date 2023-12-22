TRAIN = app/train.cpp
TEST = app/test.cpp
AG_UTIL = AG/src/util.c AG/src/type.c AG/src/typeEvolvable.c AG/src/geneticAlgorithm.c
GAME_UTIL = Game/src/TwoPlayerGame.cpp Game/src/TicTacToe.cpp Game/src/ConnectFour.cpp
PLAYER_UTIL = Player/src/DenseNetwork.cpp Player/src/Player.cpp
BINARY_TRAIN = bin/train
BINARY_TEST = bin/test
ZIP = backup.zip
AG_FOLDER = AG/include
GAME_FOLDER = Game/include
PLAYER_FOLDER = Player/include
EIGEN_FOLDER = lib/eigen
MINIDNN_FOLDER = lib/MiniDNN/include
PYTHON_PLOT = python_plot_history/python_plot_history.py

all:
	@g++ -std=c++20 -Wall -Werror -g -I$(AG_FOLDER) -I$(GAME_FOLDER) -I$(PLAYER_FOLDER) -I$(EIGEN_FOLDER) -I$(MINIDNN_FOLDER) $(AG_UTIL) $(GAME_UTIL) $(PLAYER_UTIL) $(TRAIN) -o $(BINARY_TRAIN) -lm
	@g++ -std=c++20 -Wall -Werror -g -I$(AG_FOLDER) -I$(GAME_FOLDER) -I$(PLAYER_FOLDER) -I$(EIGEN_FOLDER) -I$(MINIDNN_FOLDER) $(AG_UTIL) $(GAME_UTIL) $(PLAYER_UTIL) $(TEST) -o $(BINARY_TEST) -lm

comp_train:
	@g++ -std=c++20 -Wall -Werror -g -I$(AG_FOLDER) -I$(GAME_FOLDER) -I$(PLAYER_FOLDER) -I$(EIGEN_FOLDER) -I$(MINIDNN_FOLDER) $(AG_UTIL) $(GAME_UTIL) $(PLAYER_UTIL) $(TRAIN) -o $(BINARY_TRAIN) -lm

comp_test:
	@g++ -std=c++20 -Wall -Werror -g -I$(AG_FOLDER) -I$(GAME_FOLDER) -I$(PLAYER_FOLDER) -I$(EIGEN_FOLDER) -I$(MINIDNN_FOLDER) $(AG_UTIL) $(GAME_UTIL) $(PLAYER_UTIL) $(TEST) -o $(BINARY_TEST) -lm

train:
	@./$(BINARY_TRAIN)

test:
	@./$(BINARY_TEST)

plot:
	@python3 $(PYTHON_PLOT)

valgrind:
	@valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)

clean:
	@rm $(BINARY_TRAIN) $(BINARY_TEST) $(ZIP)

zip:
	@zip -r $(ZIP) *