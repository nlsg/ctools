
CC=gcc

all: trd

trd: trd.c
	$(CC) -lncurses trd.c -o trd 

bat: bat.cpp
	c++ bat.cpp -o bat

clean: 
	rm tui

