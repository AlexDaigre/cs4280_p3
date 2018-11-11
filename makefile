CC     = gcc
CFLAGS = -g
TARGET = scanner
OBJS   = main.o scanner.o fsaTable.o testScanner.o token.o parser.o testTree.o
DEPS   = scanner.h fsaTable.h testScanner.h token.h parser.h testTree.h

$(TARGET): $(OBJS) $(DEPS)
	$(CC) -o $(TARGET) $(OBJS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

scanner.o: scanner.c
	$(CC) $(CFLAGS) -c scanner.c

fsaTable.o: fsaTable.c
	$(CC) $(CFLAGS) -c fsaTable.c

testScanner.o: testScanner.c
	$(CC) $(CFLAGS) -c testScanner.c

token.o: token.c
	$(CC) $(CFLAGS) -c token.c

testTree.o: testTree.c
	$(CC) $(CFLAGS) -c testTree.c

parser.o: parser.c
	$(CC) $(CFLAGS) -c parser.c

clean:
	/bin/rm -f *.o $(TARGET)