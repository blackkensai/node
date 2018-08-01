#include "node-android.h"
#include <uv.h>
// #include "jni.h"
#include "node.h"
#include "node_buffer.h"
#include "node_internals.h"
#include "v8.h"
#include "node_api.h"

using namespace v8;

#include <iostream>
using namespace std;

namespace node {
namespace android {

class JniWrapper
{
public:
    JniWrapper();
    ~JniWrapper();
    
};

static void GetService(const v8::FunctionCallbackInfo<v8::Value>& args) {
  v8::Isolate* isolate = args.GetIsolate();
  args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, "android"));
}

static void Initialize(Local<Object> target, Local<Value> unused,
                       Local<Context> context) {
  cout << "init android." << endl;
  Environment* env = Environment::GetCurrent(context);
  env->SetMethod(target, "getService", GetService);
}

}  // namespace android
}  // namespace node

NODE_BUILTIN_MODULE_CONTEXT_AWARE(android, node::android::Initialize)
