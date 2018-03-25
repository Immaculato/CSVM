#!/usr/bin/nodejs
// nodejs script to trivially demonstrate asyncronous execution
//


//
// sleepprint: call the setTimeout method which delays delay*1000 
//             milliseconds before execution the function (), which
//             simply outputs note to the console.
//             Please notice: setTimeout() takes 2 parameters, a
//             callback function and a delay in milliseconds.
//             In this example, the callback function is anonymous.
//             
//             NOTE: see unexpected results due to callback's 
//             functions asyncronous execution!!!!

function createServer() {

	console.log("Sleeping for "+delay+" seconds: ");
	setTimeout(function () {
		console.log(note);
	}, delay*1000);
		
}

console.log("Example of asyncronous execution");
http.createServer(serveURL)
