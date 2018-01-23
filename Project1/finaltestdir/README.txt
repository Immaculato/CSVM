Name: Tristan Basil
Date: 2/24/2017
Assignment: CS371-001 Programming Assignment 1
Title: Programming Assignment 1

Files included: AcceptTCPConnection.c HandleTCPClient.c Makefile CreateTCPServerSocket.c DieWithError.c TCPEcho-Server-Fork.c TCPEchoServer.h README.txt

Compilation: use the command `make` to compile the "myserver" executable.

Usage: use `myserver <port_no> <http_root_dir_name>` to run the server on the specified port, using the specified directory as its base to serve files.

Description: A barebones HTTP web server, supporting only GET functionality for .txt, .html, .gif, and .jpg files. Responses are (currently) sent in 1KB chunks; this can be modified by changing the #DEFINE constant for that value in HandleTCPClient.c. If the file is available and readable, it will be transferred back via HTTP protocal with a 200 OK value. If the file cannot be accessed, a 404 Not Found response will be sent instead. Note that requesting just the base URL of the hosted server will result in serving the index.html file in the root directory specified by the user by default.

Limitations: requesting a file without a filetype extension or requesting a directory will result in no response being sent, eg. if a user requested cs.uky.edu:3000/testfile, this would result in no response rather than a 404.
