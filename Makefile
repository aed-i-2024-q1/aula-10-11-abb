CC = gcc -Wall -pedantic

build:
	mkdir -p build

main:
	$(CC) -o build/main main.c

run:
	./$(EXE)
