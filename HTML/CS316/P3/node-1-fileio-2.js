// Load the fs (filesystem) module
var fs = require('fs');

// Read the contents of the file into memory.
fs.readFile('example_log.txt', (err, logData) => {
  
// If an error occurred, throwing it will
  // display the exception and end our app.
  if (err) throw err;
  
// logData is a Buffer, convert to string.
	var text = logData.toString();

	var results = {};

// Break up the file into lines.
	var lines = text.split('\n');
  
lines.forEach(function(line) {
    var parts = line.split(' ');
    var letter = parts[1];
	console.log("line = "+line);
	if (letter != undefined) {
	    var count = parseInt(parts[2]);
    
		if(!results[letter]) {
		      results[letter] = 0;
	    }
    
		results[letter] += parseInt(count);
//		console.log("Letter is", letter);
	} else {
//		console.log("Letter doesn't exist");
	}
  });
  
console.log(results);
  // { A: 2, B: 14, C: 6 }

});
