CC = g++
CFLAGS = -std=c++17 -O3 -g -Wall -Wextra -pedantic 
SRCDIR = ./src
BINDIR = ./bin

test: $(SRCDIR)/main.cpp
	$(CC) $(CFLAGS) $? -o $@ 

main.o: src/main.cpp src/matrix.h src/MatrixRow.h src/MatrixElement.h

matrix.o: src/matrix.cpp src/MatrixRow.cpp src/MatrixElement.cpp
	$(CC) -o bin/$@ -c $?