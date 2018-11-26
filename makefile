CC     = g++
CFLAGS = -g
TARGET = frontEnd
OBJS   = main.o scanner.o fsaTable.o token.o parser.o testTree.o
DEPS   = scanner.h fsaTable.h token.h parser.h testTree.h node.h

$(TARGET): $(OBJS) $(DEPS)
	$(CC) -o $(TARGET) $(OBJS)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

scanner.o: scanner.cpp
	$(CC) $(CFLAGS) -c scanner.cpp

fsaTable.o: fsaTable.cpp
	$(CC) $(CFLAGS) -c fsaTable.cpp

token.o: token.cpp
	$(CC) $(CFLAGS) -c token.cpp

testTree.o: testTree.cpp
	$(CC) $(CFLAGS) -c testTree.cpp

parser.o: parser.cpp
	$(CC) $(CFLAGS) -c parser.cpp

clean:
	/bin/rm -f *.o $(TARGET)