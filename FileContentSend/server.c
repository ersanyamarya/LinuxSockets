// Linux Socket Programming in C
// Server sends a file to every client connected
/*....................................................
* Author: Sanyam Arya
* ersanyamarya@gmail.com
* https://www.facebook.com/er.sanyam.arya
* https://www.linkedin.com/in/sanyam-arya/
......................................................*/

#include <stdio.h>  // general purpose
#include <stdlib.h> // general purpose
#include <string.h> // general purpose
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // for the structures
#include <errno.h>		// for perror
#include <fcntl.h>		// for open
#include <unistd.h>		// for close
#include <arpa/inet.h>
#include <ctype.h>
#define DATASIZE 1024
// Main Function
int main(int argc, char *argv[])
{
	// accepting port no as an argument
	// checking if port no is passed or not
	if (argc < 2)
	{
		printf("Usage: %s <port_no>\n", argv[0]);
		exit(1);
		return 0;
	}

	int fileToSend; // file discriptor
	ssize_t readFile; // No of bytes sent

	// server and client file discriptor and port no
	int sfd, cfd, port_no;
	// length of sockaddr_in
	unsigned int len = sizeof(struct sockaddr_in);
	//data to be sent to the clients
	char data[DATASIZE] = {0};

	// Converting string to unsigned long integer
	port_no = strtoul(argv[1], NULL, 10);

	// opening the socket
	if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket");
		exit(2);
	}

	// structures for server address and client address
	struct sockaddr_in saddr = {0}, caddr = {0};

	saddr.sin_family = AF_INET; //IPv4
	// The htons() function converts the unsigned short integer hostshort from host byte order to network byte order.
	saddr.sin_port = htons(port_no);
	saddr.sin_addr.s_addr = INADDR_ANY; // Accept any ip address

	// Bind is used for binding an address with the socket
	if (bind(sfd, (struct sockaddr *)&saddr, len) < 0)
	{
		perror("bind");
		close(sfd);
		exit(3);
	}

	// listening for connection requests
	if (listen(sfd, 5) < 0)
	{
		perror("listen");
		close(sfd);
		exit(4);
	}

	//Opening a File
	fileToSend = open("sample.txt", O_RDONLY);
	// Seeking to the begaining of the file
	lseek(fileToSend, 0, 0);
	// Reading the file to data
	readFile = read(fileToSend, data, DATASIZE);
	
	printf("File Content: \n%s",data);
	
	while (1)
	{
		printf("\n\nWiting for Clients\n\n");	
		// accepting connections
		if ((cfd = accept(sfd, (struct sockaddr *)&caddr, &len)) < 0)
		{
			perror("accept");
			exit(5);
		}

		// Sending file content to client	
		if (send(cfd, data, strlen(data), 0) < 0)
		{
			perror("send");
			close(cfd);
			exit(4);
		}
		//printing the port no and ip of the client
		printf("File send to:\tclient : %s\tConnected at %d\n", inet_ntoa(caddr.sin_addr), ntohs(caddr.sin_port));
		
		// closing descriptors
		close(fileToSend);
		close(cfd);
	}

	return 0;
}
