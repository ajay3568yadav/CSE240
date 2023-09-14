CC=g++
CFLAGS=-c -Wall
LFLAGS=-Wall $(DEBUG)

DEBUG = -g

OBJS=hw.o Conga.o Zombie.o linkedlist.o

all: hw

hw: $(OBJS)
	$(CC) $(LFLAGS) $^ -o $@

hw.o: hw.cpp Conga.h
	$(CC) $(CFLAGS) $< -o $@

Conga.o: Conga.cpp Conga.h Zombie.h linkedlist.hpp
	$(CC) $(CFLAGS) $< -o $@

Zombie.o: Zombie.cpp Zombie.h
	$(CC) $(CFLAGS) $< -o $@

linkedlist.o: linkedlist.hpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o hw
