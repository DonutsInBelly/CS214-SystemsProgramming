CC = gcc
CFLAGS = -Wall -lm -g -lpthread

libnetfiles:
	$(CC) -o libnet.o libnetfiles.c $(CFLAGS)

simpleserver:
	$(CC) -o simpleserver.o simpleserver.c $(CFLAGS)

testserver:
	$(CC) -o testserver.o testserver.c $(CFLAGS)

clean:
	rm *.o
