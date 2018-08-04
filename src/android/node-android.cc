#include "node-android.h"
#include "jni.h"
#include "node-jni-wrapper.h"
#include "node.h"
#include "node_api.h"
#include "node_buffer.h"
#include "node_internals.h"
#include "uv.h"
#include "v8.h"

using namespace v8;

#include <iostream>
using namespace std;

namespace node {
namespace android {

static JNIEnv* _env = NULL;
static jobject _object = NULL;

void SaveJniObject(JNIEnv* env, jobject object) {
  _env = env;
  _object = object;
}

// inline void NODE_SET(v8::Local<v8::Template> recv,
//                             const char* name,
//                             v8::FunctionCallback callback) {
//   v8::Isolate* isolate = v8::Isolate::GetCurrent();
//   v8::HandleScope handle_scope(isolate);
//   v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(isolate,
//                                                                 callback);
//   v8::Local<v8::String> fn_name = v8::String::NewFromUtf8(isolate, name);
//   t->SetClassName(fn_name);
//   recv->Set(fn_name, t);
// }

static void GetService(const v8::FunctionCallbackInfo<v8::Value>& args) {
  v8::Isolate* isolate = args.GetIsolate();
  args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, "android"));
}

static void Initialize(Local<Object> target, Local<Value> unused,
                       Local<Context> context) {
  cout << "init android." << endl;
  Environment* env = Environment::GetCurrent(context);
  Isolate* isolate = context->GetIsolate();
  v8::Local<v8::String> fn_name = v8::String::NewFromUtf8(isolate, "android");
  if (_object) {
    target->Set(context, fn_name,
                JniWrapper::CreateJSObject(isolate, _env, _object));
  } else {
  	env->SetMethod(target, "getService", GetService);
  }
}

}  // namespace android
}  // namespace node

NODE_BUILTIN_MODULE_CONTEXT_AWARE(android, node::android::Initialize)
