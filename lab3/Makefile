CC=gcc
CFLAGS=-Wall

build: fileio

benchmark: fileio benchmark.sh
	./benchmark.sh

fileio: fileio.c
	$(CC) $(CFLAGS) -o fileio $<

clean:
	rm -rf fileio

