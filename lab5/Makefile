CC=gcc
CFLAGS=-Wall

build: cpubench

test-cpubench: cpubench
	./runbench.sh

cpubench: cpubench.c
	$(CC) $(CFLAGS) -lpthread -Ofast -o cpubench $<

clean:
	rm -rf cpubench

