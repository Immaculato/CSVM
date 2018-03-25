var aString = "Beginning ";
var didUpdate;

var myTimer = setTimeout(function () {
	aString += "Middle ";
	didUpdate = "I'm updated!";
	console.log("Did we make it here?");
	console.log("aString (inside callback)= "+aString);
	}, 0);

aString += "End";

console.log("aString = "+aString);
console.log("didUpdate? = "+didUpdate);
