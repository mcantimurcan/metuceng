CC=g++
CFLAGS=-ansi -Wall -pedantic-errors -O0

all: linkedlist directory

directory: Block.h Node.h LinkedList.h File.h Directory.h File.cpp Directory.cpp main_directory.cpp
	$(CC) $(CFLAGS) main_directory.cpp Directory.cpp File.cpp -o directory

linkedlist: Node.h LinkedList.h
	$(CC) $(CFLAGS) main_linkedlist.cpp -o linkedlist

clean:
	rm linkedlist
	rm directory
