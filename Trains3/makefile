# Simple makefile for the first mandatory assignment in DM510 - 14

# The compiler we will use
CC=gcc

# Compiler flags
CFLAGS= -Wall

# Dependencies
DEPS = dijkstra.h edge.h graph_builder.h heap.h linked_list.h vertex.h

# The objects we will compile
OBJ = travelplanning.o dijkstra.o graph_builder.o heap.o linked_list.o vertex.o 

# Compile to objects
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Link everything togeather
travelplanning: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

.PHONY: test
test:
	make clean && make && ./check.pl


# Test run with some file - if you debug with a single test, update target below
.PHONY: testrun
testrun: travelplanning
	./travelplanning tests/gitter.in a1 a3

# Make a target that is not a file, but used to clean
.PHONY: clean
clean:
	rm -f ./*.o ./*~ ./travelplanning
	
all: travelplanning
