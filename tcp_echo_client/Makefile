CC = gcc
CFLAGS = -W -Wall -O2
LDFLAGS = -lm

all : tcp_echo_client

tcp_echo_client : tcp_echo_client.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean :
	rm -rf *.o
