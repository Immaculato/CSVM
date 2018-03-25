// http://javascriptissexy.com/understand-javascript-callback-functions-and-use-them/
//
// First, setup the generic poem creator function; it will be the 
// callback function in the getUserInput function below.
function genericPoemMaker(name, noun) {
    console.log(name + " is finer than fine wine.");
    console.log("Altruistic and noble for the modern time.");
    console.log("Always admirably adorned with the latest style.");
    console.log("A " + noun + " of unfortunate tragedies who still ");
	console.log("manages a perpetual smile");
}

// The callback, which is the last item in the parameter, will be 
// our genericPoemMaker function we defined above.
function getUserInput(firstName, lastName, gender, callback) {
    var fullName = firstName + " " + lastName;

    // Make sure the callback is a function
    if (typeof callback === "function") {
    // Execute the callback function and pass the parameters to it
    callback(fullName, gender);
    }
}

console.log("Example1\n");

getUserInput("Michael", "Fassbender", "person", genericPoemMaker);

function greetUser(customerName, course)  {
   var thiscourse = course && course === "316" ? "Web Programming" : "some boring class";
  console.log("Hello, " + customerName + " welcome to " + thiscourse);
}

console.log("\nExample2\n");

// Pass the greetUser function as a callback to getUserInput
getUserInput("Bill", "Gates", "316", greetUser);
