CC     = gcc
CFLAGS = -g
TARGET = scanner
OBJS   = main.o scanner.o fsaTable.o testScanner.o token.o
DEPS   = scanner.h fsaTable.h testScanner.h token.h

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

clean:
	/bin/rm -f *.o $(TARGET)