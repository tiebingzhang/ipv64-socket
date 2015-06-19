#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(char *msg) {
	perror(msg);
	exit(0);
}

int doConnect(char* server, char *port){
	struct addrinfo hints;
	struct addrinfo *result, *rp;
	int sfd, s;

	/* Obtain address(es) matching host/port */
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_STREAM; /* STREAM socket */

	s = getaddrinfo(server,port, &hints, &result);
	if (s != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}

	/* getaddrinfo() returns a list of address structures.
	   Try each address until we successfully connect(2).
	   If socket(2) (or connect(2)) fails, we (close the socket
	   and) try the next address. */

	for (rp = result; rp != NULL; rp = rp->ai_next) {
		sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (sfd == -1)
			continue;

		if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
			break;                  /* Success */

		close(sfd);
	}

	if (rp == NULL) {               /* No address succeeded */
		fprintf(stderr, "Could not find the right address to connect\n");
		exit(EXIT_FAILURE);
	}

	freeaddrinfo(result);           /* No longer needed */
	return sfd;
}


int main(int argc, char *argv[]) {
	int sockfd,  n;
	char buffer[256];
	char *portno;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s <server> \n", argv[0]);
		exit(0);
	}
	memset(buffer,'A',sizeof(buffer));
	buffer[255]='\0';

	portno = "3005";

	printf("\nIPv4 TCP Client Started...\n");

	//Sockets Layer Call: socket() and connect()
	sockfd = doConnect(argv[1],portno);

	//Sockets Layer Call: send()
	n = send(sockfd,buffer, strlen(buffer)+1, 0);
	if (n < 0)
		error("ERROR writing to socket");

	memset(buffer, 0, 256);

	//Sockets Layer Call: recv()
	n = recv(sockfd, buffer, 255, 0);
	if (n < 0)
		error("ERROR reading from socket");
	printf("Message from server: %d bytes %s\n", n,buffer);

	//Sockets Layer Call: close()
	close(sockfd);

	return 0;
}
