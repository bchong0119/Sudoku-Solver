CC=		g++
FLAGS=		-o
TARGETS=	Puzzle

all:	$(TARGETS)

Puzzle: main.o Puzzle.h
	$(CC) $(FLAGS) $@ $^ 

main.o: main.cpp
	$(CC) -c $^

clean:
	rm *.o $(TARGETS) 
	
