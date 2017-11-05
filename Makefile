EXE = search.out
OBJS = porter2_stemmer.o
CC = clang++ -std=c++11 -Wall -pedantic -I.
CCOPTS = -O3
LINKER = clang++ -std=c++11 -Wall -pedantic -I.

all: $(EXE)

search.out: $(OBJS) main.cpp
	$(LINKER) *.cpp -o $@

porter2_stemmer.o: porter2_stemmer.h porter2_stemmer.cpp
	$(CC) $(CCOPTS) -c porter2_stemmer.cpp -o $@

clean:
	rm -f *.o $(EXE)
