console.log('hello, world');
// const NativeModule = require('native_module');
// console.log(NativeModule);
// const test = require('atest');
const test = process.binding('atest');
console.log(test.hello(5));