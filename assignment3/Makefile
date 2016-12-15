CC = gcc
CFLAGS = -Wall -lm -g -pthread

all: libnetfiles netfileserver

libnetfiles:
	$(CC) -o libnet.o libnetfiles.c $(CFLAGS)

libnetfilestest:
	$(CC) -o libnettest.o libnetfilestest.c $(CFLAGS)

server:
	$(CC) -o server.o server.c $(CFLAGS)

netfileserver:
	$(CC) -o netfileserver.o netfileserver.c $(CFLAGS)

simpleserver:
	$(CC) -o simpleserver.o simpleserver.c $(CFLAGS)

testserver:
	$(CC) -o testserver.o testserver.c $(CFLAGS)

clean:
	rm *.o
