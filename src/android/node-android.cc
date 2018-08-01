#include "node-android.h"
#include "node_buffer.h"
#include "node_internals.h"
#include "v8.h"
#include "node.h"
#include <uv.h>
#include <iostream>

using namespace v8;
namespace node {

void testMethod(const v8::FunctionCallbackInfo<v8::Value>& args) {
  v8::Isolate* isolate = args.GetIsolate();
  args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, "world"));
}

void testinit(Local<Object> target,
         Local<Value> unused,
         Local<Context> context) {
        using namespace std;
    cout << "init atest." << endl;
    Environment* env = Environment::GetCurrent(context);
    env->SetMethod(target, "hello", testMethod);
    // NODE_SET_METHOD(exports, "hello", Method);
}

}

// NODE_MODULE_X(atest, init, NULL, 1)
// NODE_MODULE(atest, init)
NODE_BUILTIN_MODULE_CONTEXT_AWARE(atest, node::testinit)
