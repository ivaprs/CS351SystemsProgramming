CC=gcc
CFLAGS=-Wall -O3

build: server netio
test-netio: server netio
	./server &
	sleep 1 #I have a sleep because it takes a second for the server to setup
	./netio socket add 1000000
	./server &
	sleep 1
	./netio socket subtract 1000000
	./server &
	sleep 1
	./netio socket multiply 1000000
	./server &
	sleep 1
	./netio socket divide 1000000
	./netio function add 1000000000
	./netio function subtract 1000000000
	./netio function multiply 1000000000
	./netio function divide 1000000000
	./netio pipe add 1000000
	./netio pipe subtract 1000000
	./netio pipe multiply 1000000
	./netio pipe divide 1000000
netio: netio.c
	$(CC) $(CFLAGS) -o netio $<
server: server.c
	$(CC) $(CFLAGS) -o server $<
clean:
	rm -rf netio
	rm -rf server

