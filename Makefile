CC = gcc -Wall -pedantic

build_dir:
	mkdir -p build

element: build_dir
	$(CC) -c -o build/element.o element.c

bst: element
	$(CC) -c -o build/bst.o bst.c

main: bst
	$(CC) -o build/main main.c build/bst.o build/element.o