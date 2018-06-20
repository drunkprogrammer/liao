all: server client
server: server.o

	gcc server.o  -o  server

server.o:server.s

	gcc -c server.s -o server.o

server.s:server.i
	
        gcc -S server.i -o server.s

server.i:server.c
	
        gcc -E server.c -o server.i
client: client.o

	gcc client.o  -o  client

client.o:client.s

	gcc -c client.s -o client.o

client.s:client.i
	
        gcc -S client.i -o client.s

client.i:client.c
	
        gcc -E client.c -o client.i

.PHONY:clean
clean:
    -rm -f server.o server server.s server.i
    -rm -f client.o client client.s client.i


