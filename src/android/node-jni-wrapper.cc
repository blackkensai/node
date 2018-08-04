#include "node-jni-wrapper.h"

namespace node {
namespace android {

Persistent<Function> JniWrapper::constructor;

JniWrapper::JniWrapper(v8::Isolate *isolate, JNIEnv *env, jobject object)
    : env(env), jniObject(object) {}

JniWrapper::~JniWrapper() {}

Local<Object> JniWrapper::CreateJSObject(Isolate *isolate, JNIEnv *env,
                                         jobject object) {
  // TODO primitive types
  JniWrapper *wrapper = new JniWrapper(isolate, env, object);
  Local<ObjectTemplate> tpl = v8::ObjectTemplate::New(isolate);
  // TODO methods & fields
  tpl->SetInternalFieldCount(1);
  // tpl->Set(String::NewFromUtf8(isolate, "getClass", NewStringType::kNormal)
  //              .ToLocalChecked(),
  //          FunctionTemplate::New(isolate, GetClassName));

  Local<Object> v8object = tpl->NewInstance();
  v8object->Set(String::NewFromUtf8(isolate, "getClass", NewStringType::kNormal)
               .ToLocalChecked(),
           FunctionTemplate::New(isolate, GetClassName)->GetFunction());
  wrapper->Wrap(v8object);
  return v8object;
}

void JniWrapper::Register(Isolate *isolate, const char *name, Local<Object> object) {
  isolate->GetCurrentContext()->Global()->Set(String::NewFromUtf8(isolate, name, NewStringType::kNormal)
               .ToLocalChecked(), object);
}

void JniWrapper::GetClassName(const FunctionCallbackInfo<v8::Value> &args) {
  Isolate *isolate = args.GetIsolate();
  JniWrapper *wrapper = ObjectWrap::Unwrap<JniWrapper>(args.Holder());
  JNIEnv *env = wrapper->env;
  jobject object = wrapper->jniObject;
  jclass cls = env->GetObjectClass(object);

  // First get the class object
  jmethodID mid = env->GetMethodID(cls, "getClass", "()Ljava/lang/Class;");
  jobject clsObj = env->CallObjectMethod(object, mid);

  // Now get the class object's class descriptor
  cls = env->GetObjectClass(clsObj);

  // Find the getName() method on the class object
  mid = env->GetMethodID(cls, "getName", "()Ljava/lang/String;");

  // Call the getName() to get a jstring object back
  jstring strObj = (jstring)env->CallObjectMethod(clsObj, mid);

  // Now get the c string from the java jstring object
  const char *str = env->GetStringUTFChars(strObj, NULL);

  args.GetReturnValue().Set(String::NewFromUtf8(isolate, str, NewStringType::kNormal).ToLocalChecked());

  env->ReleaseStringUTFChars(strObj, str);
}

} // namespace android
} // namespace node
