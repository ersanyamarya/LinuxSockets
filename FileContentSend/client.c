// Linux Socket Programming in C
// Client Recieves the file and diconnects
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
#include <errno.h>      // for perror
#include <fcntl.h>      // for open
#include <unistd.h>     // for close
#include <netinet/in.h>
#include <arpa/inet.h>
#define BUFSIZE 1024 // size of the buffer
int main(int argc, char *argv[])
{
    if (argc < 3)
    { // using command line argument
        printf("Usage: %s <serv_ip> <serv_port>\n", argv[0]);
        exit(1);
    }
    int fileRecieved; // file discriptor
	ssize_t writeFile; // no of bytes recieved
    
    // declearing aand defining variables
    unsigned int len = sizeof(struct sockaddr_in);
    int cfd, serv_port; 
    char buf[BUFSIZE] = {0};
    
    //string to unsigned long atoi can also be used
    serv_port = strtoul(argv[2], NULL, 10); 

    //creating the socket
    if ((cfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
        exit(2);
    }

    // filling the address structure
    struct sockaddr_in saddr = {0};
    saddr.sin_family = AF_INET;                 // set to AF_INET
    saddr.sin_port = htons(serv_port);          // Port number
    saddr.sin_addr.s_addr = inet_addr(argv[1]); // IP address eg "192.168.1.1"
    
    //connecting to a server
    if (connect(cfd, (struct sockaddr *) &saddr, len) < 0) {
		perror("connect");
		close(cfd);
		exit(3);
    }
    
    //Receiving data from the socket
    if (recv(cfd, buf, sizeof(buf), 0) < 0) {
        perror("recv");
        exit(5);
    }
    // opening a file
    fileRecieved = open("recieved.txt", O_WRONLY|O_CREAT,0666);
    // going to the begaining of the file
    lseek(fileRecieved, 0, 0);
    // writing to the file
 	writeFile = write(fileRecieved, buf, BUFSIZE);
    
    printf("File Recieved\n");
    
    // Closing all descriptors
    close(fileRecieved);
    close(cfd);
    
    return 0;
}