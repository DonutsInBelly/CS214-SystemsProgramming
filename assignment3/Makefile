CC = gcc
CFLAGS = -Wall -lm -g -lpthread

libnetfiles:
	$(CC) -o libnet.o libnetfiles.c $(CFLAGS)

simpleserver:
	$(CC) -o simpleserver.o simpleserver.c $(CFLAGS)

clean:
	rm *.o
