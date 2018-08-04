console.log('hello, world');
const test = process.binding('embedtest');
console.log(test.hello(5));
const android = process.binding('android');
console.log(android.android);
for (var f in android.android) {
	console.log(`  ${f}`);
}
console.log(android.android.getClass());
console.log(android.getClass);
console.log(android.getClass());
