MAIN= src/main.c
UTIL = src/util.c src/type.c src/typeEvolvable.c src/geneticAlgorithm.c src/funcaoEscrota.c
BINARY = bin/teste
ZIP = teste.zip
INCLUDE_FOLDER = include

all:
	@gcc -Wall -Werror -g -I$(INCLUDE_FOLDER) $(UTIL) $(MAIN) -o $(BINARY) -lm

run:
	@./$(BINARY)
	
debug:
	@gcc -DDEBUG -Wall $(MAIN) $(UTIL) -o $(BINARY)

valgrind:
	@valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)

clean:
	@rm $(BINARY) $(ZIP)

zip:
	@zip -r $(ZIP) *
