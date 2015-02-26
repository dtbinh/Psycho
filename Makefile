CC = g++
CFLAGS = -I. -L -02
LIBS = -lm -lpthread -ldl

all : main

main : main.o board.o path.o node.o player.o marble.o util.o
	$(CC) -o psycho main.o board.o path.o node.o player.o marble.o util.o $(LIBS)

main.o : main.cpp board.h
	$(CC) -c -o $@ $< $(CFLAGS) 

board.o : board.cpp board.h path.h node.h marble.h
	$(CC) -c -o $@ $< $(CFLAGS)

node.o : node.cpp node.h marble.h
	$(CC) -c -o $@ $< $(CFLAGS)

path.o : path.cpp path.h
	$(CC) -c -o $@ $< $(CFLAGS)

player.o : player.cpp player.h marble.h board.h
	$(CC) -c -o $@ $< $(CFLAGS)
	
marble.o : marble.cpp marble.h path.h board.h player.h
	$(CC) -c -o $@ $< $(CFLAGS)

util.o : util.cpp util.h
	$(CC) -c -o $@ $< $(CFLAGS)


clean :
	rm -rf *.o
