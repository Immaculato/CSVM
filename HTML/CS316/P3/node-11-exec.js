// NOTE: this example uses a callback function.  As stated in class, these
// are placed in the Event queue and are asyncronously executed.  Be very
// careful and aware of when and which lines are executed!!
//
const exec = require('child_process').exec;


function getthedate() {
var theDate = "UNSET";
	exec('date', {env: {'PATH': '/bin'}}, function(error, stdout, stderr) {

		if (error) {
			console.error('exec error'+error);
			return;
		}
		console.log('stdout:'+ stdout);
//		console.log('stderr:'+ stderr);              // unneeded for example
		theDate = "DATE:" + stdout
		console.log("Hey, theDate = " + theDate);
		console.log("Returning that to calling statement");
		return theDate;
	});
}

console.log("Step 0 - establish where we are!");
console.log("Step 1 - call getthedate()");
var theAnswer = getthedate();
console.log("Step 2 - print out theAnswer, returned from getthedate()");
console.log("         theAnswer = " + theAnswer);
console.log("Step 3 - pull hair out!");
console.log("Step 4 - note what prints out after this line!");















