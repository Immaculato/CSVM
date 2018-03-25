// https://nodejs.org/api/http.html
//
// This example uses a named function doprocess() for the callback function
// sent to the createServer() method.

//https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Math/random -> used to figure out how to generate a port integer
//https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Regular_Expressions -> used to learn regex

const ignoreURL = '/favicon.ico';

var http = require("http"),
	url = require('url');

const hostname = 'iris.cs.uky.edu';
const LOWERPORT = 7170;
const UPPERPORT = 7170;
function doprocess(request, response) {
	var xurl = request.url;
	if (xurl == ignoreURL) {
		return;
	}
	response.statusCode = 200;
	response.setHeader('Content-Type', 'text/plain');
	//response.end('Hello, World!  You requested the following URL: '+xurl+'\n');
	var randomEndpoint = /\/RANDOM\/[0-9]+\:[0-9]+(?!.)/;
	var getfileEndpoint =/\/GETFILE\/[a-zA-Z0-9_\.]+(?!.)/;
	var executeEndpoint =/\/EXECUTE\/[a-zA-Z0-9_\.]+(?!.)/;
	if (xurl.match(randomEndpoint)) {
		console.log('Random');
		//parse out the URL and give a random number.
		parsedURL = xurl.split("\/");
		parsedArgs = parsedURL[2].split(':');
		console.log(parsedArgs);
		giveRandom(parseInt(parsedArgs[0]), parseInt(parsedArgs[1]), response);
	} else if (xurl.match(getfileEndpoint)) {
		console.log('Getfile');
	} else if (xurl.match(executeEndpoint)) {
		console.log('Execute');
	} else {
		console.log('False');
	}
	console.log(xurl);
}

function giveRandom(lower, upper, response) {
	var randNum = randRange(lower, upper);
	console.log(randNum);
	response.end(randNum.toString());
}
	

function printServerInfo(port, hostname) {
	console.log('Server running at http://'+ hostname +':'+ port +'/');
	console.log('Hello, World!');
}

function randRange(lower, upper) {
	return Math.floor(Math.random() * (upper - lower)) + lower;
}

var server = http.createServer(doprocess);
randomPort = randRange(LOWERPORT, UPPERPORT);

server.listen(randomPort,hostname,printServerInfo(randomPort, hostname));





