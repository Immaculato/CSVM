#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h>     /* for close() */
#include <stdlib.h>    /* for malloc() and free() */
#include <string.h>    /* for memcpy() */
#define RCVBUFSIZE 1024   /* Size of receive buffer (1KB) */

void DieWithError(char *errorMessage);  /* Error handling function */

void HandleTCPClient(int clntSocket)
{
    //char initBuffer[RCVBUFSIZE];
    char *wholeBuffer = malloc(RCVBUFSIZE);
    //echoBuffer = calloc(RCVBUFSIZE, 1);        /* Buffer for echo string */
    int recvMsgSize;                    /* Size of received message */
    int Kcount=0;   //size (in KB) of recieved message, rounded up to nearest integer

    /* Receive message from client */
    if ((recvMsgSize = recv(clntSocket, wholeBuffer, RCVBUFSIZE, 0)) < 0)
        DieWithError("recv() failed");
    Kcount++; //this can only happen if recv works.
	
    /* if 1k was successfully read, we need to try and read again. */
    while (recvMsgSize == RCVBUFSIZE) {
	char initBuffer[RCVBUFSIZE];
	char *newBuffer = malloc(RCVBUFSIZE*(Kcount+1)); //we need to allocate more space for the incoming message. make a new buffer, which holds 1k more than the last.
	memcpy(newBuffer, wholeBuffer, RCVBUFSIZE*Kcount); //copy over the contents of previous whole message.
	free(wholeBuffer); //free the contents of the old whole buffer
	wholeBuffer = newBuffer; //now, the whole buffer is the new, bigger one, but with the same contents as before.
	if ((recvMsgSize = recv(clntSocket, initBuffer, RCVBUFSIZE, 0)) < 0)	//read again into a temp buffer,, then copy its contents to the new, bigger buffer.
		DieWithError("recv() failed");
	memcpy(wholeBuffer+(Kcount*RCVBUFSIZE), initBuffer, recvMsgSize); //this copies the new bytes into the whole buffer, which can be bigger than 1k.

	Kcount++; //each loop indicates we have 1 more KB (rounded up to nearest KB) of memory space needed. 
    }
	wholeBuffer[Kcount*RCVBUFSIZE]=0;
	printf(wholeBuffer, ((Kcount-1)*RCVBUFSIZE)+recvMsgSize);

	//if (recvMsgSize == 1000) recv(clntSocket, echoBuffer, RCVBUFSIZE, 0);
        /* Echo message back to client */
        //if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
        //    DieWithError("send() failed");
	 
    free(wholeBuffer);
    close(clntSocket);    /* Close client socket */
}
