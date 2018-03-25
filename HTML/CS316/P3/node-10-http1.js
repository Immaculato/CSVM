// https://nodejs.org/api/http.html
//
// This example uses an anonymous function() for the callback function
// sent to the createServer() method.
//
// It also adds an anonymous function to the .listen() method.  Note that
// methods are overloaded and can accept differing numbers of parameters.

var http = require("http"),
	url = require('url');

const hostname = 'belgarath.cs.uky.edu';
const port = 3332;

var server = http.createServer(function(request, response) {
	var xurl = request.url;
	response.statusCode = 200;
	response.setHeader('Content-Type', 'text/plain');
	response.end('Hello, World!  You requested the following URL: '+xurl+'\n');
});

server.listen(port, hostname, function() {
	console.log('Server running at http://'+ hostname +':'+ port +'/');
	console.log('Hello, World!');
});










