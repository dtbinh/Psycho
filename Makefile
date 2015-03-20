CC = g++
CFLAGS = -I. -L -02
LIBS = -lm -lpthread -ldl

all : main

main : main.o board.o path.o node.o player.o marble.o util.o myvectoroftree.o tree.o
	$(CC) -o psycho main.o board.o path.o node.o player.o marble.o util.o myvectoroftree.o tree.o $(LIBS)

main.o : main.cpp board.h player.h path.h tree.h minimax.h myvectoroftree.h minimax.h
	$(CC) -c -o $@ $< $(CFLAGS) 

board.o : board.cpp board.h path.h node.h marble.h util.h
	$(CC) -c -o $@ $< $(CFLAGS)

node.o : node.cpp node.h marble.h path.h
	$(CC) -c -o $@ $< $(CFLAGS)

path.o : path.cpp path.h
	$(CC) -c -o $@ $< $(CFLAGS)

player.o : player.cpp player.h marble.h board.h util.h path.h tree.h node.h
	$(CC) -c -o $@ $< $(CFLAGS)
	
marble.o : marble.cpp marble.h path.h board.h player.h
	$(CC) -c -o $@ $< $(CFLAGS)

util.o : util.cpp util.h board.h marble.h player.h
	$(CC) -c -o $@ $< $(CFLAGS)

myvectoroftree.o : myvectoroftree.cpp myvectoroftree.h tree.h
	$(CC) -c -o $@ $< $(CFLAGS)

tree.o : tree.cpp tree.h myvectoroftree.h minimax.h marble.h util.h
	$(CC) -c -o $@ $< $(CFLAGS)


clean :
	rm -rf *.o
