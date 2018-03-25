console.log("Example1");

function hello() {
	console.log('Hello normal world!');
}

hello();

console.log("Example2");

var HW = function(who) {
	console.log('Hello '+who+' world!');
};

HW('anonymous');

console.log("Example3.1");

setTimeout(function() {
	console.log('Hello delayed1 world!');
	},
	10000);


console.log("Example3.2");

setTimeout(HW('delayed2'), 2000);

console.log("Example3.3");

setTimeout(function() {
	console.log('Hello delayed3 world!');
	},
	1000);


console.log("Example4.1");

function logArrayElements(element, index, array) {
  console.log('a[' + index + '] = ' + element);
  }

// Notice that index 2 is skipped since there is no item at
// // that position in the array.
[2, 5, , 9].forEach(logArrayElements);


console.log("Example4.2");

var x = [3, 6, 10, 15];

x.forEach(logArrayElements);











