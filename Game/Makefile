MAIN = src/main.cpp
UTIL = src/TwoPlayerGame.cpp src/TicTacToe.cpp 
BINARY = bin/teste
ZIP = teste.zip
INCLUDE_FOLDER = include

all:
	@g++ -Wall -Werror -g -I$(INCLUDE_FOLDER) $(UTIL) $(MAIN) -o $(BINARY) -lm

run:
	@./$(BINARY)

valgrind:
	@valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)

clean:
	@rm $(BINARY) $(ZIP)

zip:
	@zip -r $(ZIP) *