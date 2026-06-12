CC = gcc
CFLAGS = -g -w -Wall
CXXFLAGS = -Ilib -Isrc -Itest
VPATH = lib:src:test
LIB = -lm
OBJ := exe

main: main.o tools.o
	$(CC) $(CFLAGS) -o main main.o tools.o $(LIB)

test_unit: test_unit.o tools.o
	$(CC) $(CFLAGS) -o test_unit test_unit.o tools.o $(CXXFLAGS) $(LIB)

test_unit.o: ./test/test_unit.c
	$(CC) $(CFLAGS) -c ./test/test_unit.c $(CXXFLAGS)

tools.o: ./src/tools.h ./src/tools.c
	$(CC) $(CFLAGS) -c ./src/tools.c -o tools.o $(CXXFLAGS)

main.o: ./src/tools.h  ./src/main.c
	$(CC) $(CFLAGS) -c ./src/main.c -o main.o $(CXXFLAGS)

clean:
	rm -f *.o main test_unit
