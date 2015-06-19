all: 64server 64client

64server:64server.c
	gcc -o $@ $^ -Wall -O2 -s 

64client:64client.c
	gcc -o $@ $^ -Wall -O2 -s 

clean:
	rm -f 64client 64server
