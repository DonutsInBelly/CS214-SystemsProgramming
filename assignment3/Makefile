CC = gcc
CFLAGS = -Wall -lm -g -pthread

libnetfiles:
	$(CC) -o libnet.o libnetfiles.c $(CFLAGS)

netfileserver:
	$(CC) -o netfileserver.o netfileserver.c $(CFLAGS)

simpleserver:
	$(CC) -o simpleserver.o simpleserver.c $(CFLAGS)

testserver:
	$(CC) -o testserver.o testserver.c $(CFLAGS)

clean:
	rm *.o
