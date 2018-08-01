console.log('hello, world');
// const NativeModule = require('native_module');
// console.log(NativeModule);
// const test = require('atest');
const test = process.binding('embedtest');
console.log(test.hello(5));
console.log(process.binding('android').getService())