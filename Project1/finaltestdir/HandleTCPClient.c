#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h>     /* for close() */
#include <stdlib.h>    /* for malloc() and free() */
#include <string.h>    /* for memcpy() */
#define RCVBUFSIZE 1024   /* Size of receive buffer (1KB) */
#define MAXCHUNKSIZE 1024
#define OK200HTML "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8"
#define OK200JPG "HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\n"
#define OK200GIF "HTTP/1.1 200 OK\r\nContent-Type: image/gif\r\n"
#define NOTFOUND404 "HTTP/1.1 404 Not Found \r\n"
#define HTMLFILETYPE 1
#define JPGFILETYPE 2
#define GIFFILETYPE 3

const char* GET = "GET";

char* httpPath;
int fileType;

void DieWithError(char *errorMessage);  /* Error handling function */

int DetermineFileType(char* path);

char* ParseHttpRequest(char *wholeMsg, char* httpRootDir) {
	const char* delim = " ";
	//split the incoming message along its space characters.
	char* requestType = strtok(wholeMsg, delim);
	//this server only supports GET requests for this project.
	if (strcmp(requestType, GET) != 0) {
		DieWithError("only GET requests supported");
	}
	char* path = strtok(0, delim); //get the next segment after the space: this is path to file.

	//if the path isn't just a '/' character, determine the file type (.html, .gif, etc), and form the absolute
	//file path.
	if (strcmp(path, "/") != 0) {
		fileType = DetermineFileType(path);
		httpPath = malloc(strlen(httpRootDir)+strlen(path)+1);
		strcpy(httpPath, httpRootDir);
		strcat(httpPath, path);
		return httpPath;
	} else {
		// the '/' is a special case: change it to /index.html
		//printf("Thinks its a /");
		fileType = HTMLFILETYPE;
		httpPath = calloc(strlen(httpRootDir)+12, 1);
		strcpy(httpPath, httpRootDir);
		strcat(httpPath, "/index.html");
		return httpPath;
	}
}
/*
Determine the file type of a character. The integer returned is defined by the #DEFINE statements at the top of the file.
*/
int DetermineFileType(char* realPath) {	
	const char* delim = ".";
	//don't want to corrupt the original path
	char path[strlen(realPath)+1];
	strcpy(path, realPath);
	//look for a '.' to signify a file type. if there isn't one, return -1 as error.
	char* relativePathSeg = strtok(path, delim);
	if ((void*) relativePathSeg == NULL) return -1;
	//now look up until the end of the line. we assume there are no '.' characters before the file type at the end of the request path.
	relativePathSeg = strtok(0, " ");
	//return the correct headers for each file extension.
	if (strcmp(relativePathSeg, "html") == 0 || strcmp(relativePathSeg, "txt") == 0) {
		return HTMLFILETYPE;
	} else if (strcmp(relativePathSeg, "jpg") == 0) {
		return JPGFILETYPE;
	} else if (strcmp(relativePathSeg, "gif") == 0) {
		return GIFFILETYPE;
	} else {
		return -1;
	}
}
/*
Actually send the HTTP Response. This can be a 404 if the file is not found, or a 200 with the file. Sends in MAXCHUNKSIZE byte chunks to allow large files to be transferred.
*/
void SendHttpMessage(int clntSocket, int filetype) {
	//attempt to open the file the client asked for.
	FILE *requestedFile = fopen(httpPath, "r");
	//if the file can't be opened, send a 404 and we're done.
	if ((void*) requestedFile == NULL) {
		send(clntSocket, NOTFOUND404, strlen(NOTFOUND404), 0);
		DieWithError("File not found.");
	}
	char httpResponse[200];
	//Load up the appropriate headers for each response type.
	switch(filetype) {
		case HTMLFILETYPE :
			strcpy(httpResponse, OK200HTML);
			break;
		case JPGFILETYPE :
			strcpy(httpResponse, OK200JPG);
			break;
		case GIFFILETYPE :
			strcpy(httpResponse, OK200GIF);
			break;
		default :
			DieWithError("Unsupported file type");
	}
	char buffer[MAXCHUNKSIZE];
	//find the size of the file: we need to know that before we read it.
	fseek(requestedFile, 0L, SEEK_END);
	int fileSize = ftell(requestedFile);
	rewind(requestedFile);
	
	//send the appropriate header response first.		
	send(clntSocket, httpResponse, strlen(httpResponse), 0);
	//send content-length
	char contentLength[50];
	sprintf(contentLength, "Content-Length: %d\r\n\r\n", fileSize);
	send(clntSocket, contentLength, strlen(contentLength), 0);
	//read bytes of the given file, and send them in MAXCHUNKSIZE chunks if needed.
	while (fileSize > MAXCHUNKSIZE) {
		fileSize -= fread(buffer, sizeof(char), MAXCHUNKSIZE, requestedFile);
		send(clntSocket, buffer, MAXCHUNKSIZE, 0);
	}
	//read/send the last few bytes
	fread(buffer, sizeof(char), fileSize, requestedFile);
	send(clntSocket, buffer, fileSize, 0);
	//dont forget the last few carriage returns
	send(clntSocket, "\r\n\r\n", 4, 0);
}


void HandleTCPClient(int clntSocket, char* httpRootDir) {

    char *wholeBuffer = calloc(RCVBUFSIZE, 1);
    int recvMsgSize;                    /* Size of received message */
    int Kcount=0;   //size (in KB) of recieved message, rounded up to nearest integer

    /* Receive message from client */
    if ((recvMsgSize = recv(clntSocket, wholeBuffer, RCVBUFSIZE, 0)) < 0)
        DieWithError("recv() failed");
    Kcount++; //this can only happen if recv works.
	
    /* if RCVBUFSIZE bytes were successfully read, we need to try and read again. */
    while (recvMsgSize == RCVBUFSIZE) {
	//we need to allocate more space for the incoming message. make a new buffer, which holds 1k more than the last.
	char initBuffer[RCVBUFSIZE];
	char *newBuffer = calloc(RCVBUFSIZE*(Kcount+1), 1); 
	
	//copy over the contents of the previous message.
	memcpy(newBuffer, wholeBuffer, RCVBUFSIZE*Kcount);
	free(wholeBuffer); //free the contents of the old whole buffer
	wholeBuffer = newBuffer; //now, the whole buffer is the new, bigger one, but with the same contents as before.
	if ((recvMsgSize = recv(clntSocket, initBuffer, RCVBUFSIZE, 0)) < 0)
		DieWithError("recv() failed");
	
	//copy over the new bytes for this loop into the buffer.
	memcpy(wholeBuffer+(Kcount*RCVBUFSIZE), initBuffer, recvMsgSize);
	Kcount++; //each loop indicates we have 1 more RCVBUFSIZE of memory space allocated. 
    }
	
    //parse and send our response.
    ParseHttpRequest(wholeBuffer, httpRootDir);
    SendHttpMessage(clntSocket, fileType);
    //free up allocated memory at the end.	 
    free(wholeBuffer);
    free(httpPath);
    close(clntSocket);    /* Close client socket */
}
