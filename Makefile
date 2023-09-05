C_ARGS=-Wall -std=c99 -march=native

# main commands
# compile my libraries
install: bin/initialization.o bin/operations.o bin/velha.o
	
	ar rcs bin/matrixop.a bin/initialization.o bin/operations.o
	ar rcs bin/velha.a bin/velha.o

# compile the main code
all: bin/network.o
	gcc bin/network.o -o bin/network -L/bin bin/*.a -lm

# run the main code
run:
	./bin/network

bin/network.o: src/main.c
	gcc -c src/main.c -o bin/network.o $(C_ARGS)

# run a single instance of jogo da veia
single: bin/main.o
	gcc -o bin/main bin/main.o -L/bin bin/matrixop.a bin/velha.a

bin/main.o: single/main.c
	gcc -c single/main.c -o bin/main.o $(C_ARGS)

run_single: 
	./bin/main

# ignore these
bin/initialization.o: src/initialization.c include/matrix_operations.h
	mkdir -p bin/
	gcc src/initialization.c -c $(C_ARGS) -o bin/initialization.o

bin/operations.o: src/operations.c include/matrix_operations.h
	gcc src/operations.c -c $(C_ARGS) -o bin/operations.o

bin/velha.o: src/velha.c include/velha.h
	gcc src/velha.c -c $(C_ARGS) -o bin/velha.o

clean:
	rm bin/*