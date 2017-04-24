CC = g++
CFLAGS = -Wall -O0 -g
all: server client
server: server.c
	$(CC) -o server server.c
client: client.c
	$(CC) $(CFLAGS) -o client client.c
clean:
	rm -f client server
