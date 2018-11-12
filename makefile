CC     = g++
CFLAGS = -g
TARGET = frontEnd
OBJS   = main.o scanner.o fsaTable.o token.o parser.o testTree.o
DEPS   = scanner.h fsaTable.h token.h parser.h testTree.h node.h

$(TARGET): $(OBJS) $(DEPS)
	$(CC) -o $(TARGET) $(OBJS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

scanner.o: scanner.cpp
	$(CC) $(CFLAGS) -c scanner.cpp

fsaTable.o: fsaTable.c
	$(CC) $(CFLAGS) -c fsaTable.c

token.o: token.c
	$(CC) $(CFLAGS) -c token.c

testTree.o: testTree.c
	$(CC) $(CFLAGS) -c testTree.c

parser.o: parser.cpp
	$(CC) $(CFLAGS) -c parser.cpp

clean:
	/bin/rm -f *.o $(TARGET)