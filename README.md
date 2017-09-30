[![logosmallestd](https://user-images.githubusercontent.com/28115284/28752842-881291c0-7546-11e7-9277-bd89186ca933.png)](https://github.com/ersanyamarya)

# Linux Socket Programming

* Sockets allow communication between two different processes on the same or different machines.
* A socket is just a logical endpoint for communication. They exist on the transport layer. 

* TCP socket
	* Type: SOCK_STREAM
	* reliable delivery
	* in-order guaranteed
	* connection-oriented
	* bidirectional
	
* UDP socket
	* Type: SOCK_DGRAM
	* unreliable delivery
	* no order guarantees
	* no notion of “connection” – app
	* indicates destination for each
	* packet
	* can send or receive
	
##### Visit my blog for more details

#### This repo contains linux socket programming codes.

##### Simple
* Client: Client connects to a server, recieves in buf 
* Server: Server connects to a client, sends data and and print clients IP and PORT

##### read_write
* Client: Client connects to a server, sends data and recieves in buf
* Server: Server connects to a client, recieves buf, converts it into ALLCAPS and send data

##### contSend
* Client: Client connects to a server, sends data and recieves in buf continuously
* Server: Server connects to a client, sends data and recieves in buf continuously

##### FileCOntentSend
* Client: Client Recieves the file and diconnects
* Server: Server sends a file to every client connected

#### Author: Sanyam Arya
* ersanyamarya@gmail.com
* [Facebook](https://www.facebook.com/er.sanyam.arya)
* [Linkedin](https://www.linkedin.com/in/sanyam-arya-077ab638/)
