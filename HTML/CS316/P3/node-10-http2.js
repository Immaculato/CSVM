// https://nodejs.org/api/http.html
//
// This example uses an anonymous function() for the callback function
// sent to the createServer() method.
//
// Note also that the .listen() method is appended to the createServer()
// object/method.  Syntax is non-intuitive!  Whitespace is ignored, as are
// any comments between the closing paren ) of createServer() and the period .
// before listen() .  I am somewhat against this syntax.  IMO it is somewhat
// convoluted.

var http = require("http"),
	url = require('url');

const hostname = 'iris.cs.uky.edu';
const port = 6969;

http.createServer(function(request, response) {
	var xurl = request.url;
	response.statusCode = 200;
	response.setHeader('Content-Type', 'text/plain');
	response.end('Hello, World!  You requested the following URL: '+xurl+'\n');
})

//  this is crazy - I can put comments in the middle of a call!!!

.listen(port, hostname, function() {
	console.log('Server running at http://'+ hostname +':'+ port +'/');
	console.log('Hello, World!');
});











