CC     = g++
CFLAGS = -g
TARGET = scanner
OBJS   = main.o scanner.o fsaTable.o token.o parser.o testTree.o tree.o
DEPS   = scanner.h fsaTable.h token.h parser.h testTree.h tree.h node.h

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

parser.o: parser.c
	$(CC) $(CFLAGS) -c parser.c

tree.o: tree.cpp
	$(CC) $(CFLAGS) -c tree.cpp

clean:
	/bin/rm -f *.o $(TARGET)