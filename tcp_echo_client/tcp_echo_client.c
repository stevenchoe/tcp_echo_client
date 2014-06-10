#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFSIZE 1024
void error_exit(char *message);

int main(int argc, char **argv) {
	int client_fd;
	char message[BUFSIZE];
	int str_len, ret;
	struct sockaddr_in server_addr;

	if (argc != 3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	client_fd = socket(PF_INET, SOCK_STREAM, 0);
	if (client_fd == -1)
		error_exit("client_fdet() error");

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	server_addr.sin_port = htons(atoi(argv[2]));

	ret = connect(client_fd, (struct sockaddr*) &server_addr,
			sizeof(server_addr));
	if (ret == -1)
		error_exit("connect() error!");

	while (1) {
		fputs("write message (q to quit) : ", stdout);
		fgets(message, BUFSIZE, stdin);

		if (!strcmp(message, "q\n")) break;
		write(client_fd, message, strlen(message));

		str_len = read(client_fd, message, BUFSIZE-1);
		message[str_len] = 0;
		printf("read message : %s \n", message);
	}

	close(client_fd);
	return 0;
}

void error_exit(char *message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
