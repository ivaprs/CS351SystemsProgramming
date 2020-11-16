CC=gcc
CFLAGS=-Wall -O3

build: server netio
test-netio: server netio
	./server & #I run server here because if I run it right before socket, it will fail to connect, but only for the first one. Also I changed port to 8081 because 8080 kept failing to bind.
	./netio function add 1000000000
	./netio function subtract 1000000000
	./netio function multiply 1000000000
	./netio function divide 1000000000
	./netio socket add 1000000
	./server &
	./netio socket subtract 1000000
	./server &
	./netio socket multiply 1000000
	./server &
	./netio socket divide 1000000
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

