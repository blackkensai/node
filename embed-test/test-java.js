console.log('hello, world');
const test = process.binding('embedtest');
console.log(test.hello(5));
console.log(process.binding('android').getClass());