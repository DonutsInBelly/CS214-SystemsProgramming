CC=gcc
CFLAGS=-std=c99 -lm -Wall -g -lpthread

compressRLE:
	$(CC) -o asst2 compressRLE.c $(CFLAGS)

compressT_LOLS:
	$(CC) -o asst2 compressT_LOLS.c lols.c $(CFLAGS)

compressR_LOLS:
	$(CC) -o asst2 compressR_LOLS.c lols.c utils.c $(CFLAGS)

compressLOLS:
	$(CC) -o asst2 compressLOLS.c $(CFLAGS)

clean:
	rm -rf asst2
