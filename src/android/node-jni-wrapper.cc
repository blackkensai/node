#include "node-jni-wrapper.h"

#include <string.h>
#include <iostream>
using namespace std;

namespace node {
namespace android {

const char *CALLBACK_METHOD_NAME_KEY = "CALLBACK_METHOD_NAME";
const char *CALLBACK_METHOD_SIGNATURE_KEY = "CALLBACK_METHOD_SIGNATURE";

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
  wrapper->Wrap(v8object);

  v8object->Set(String::NewFromUtf8(isolate, "getClass", NewStringType::kNormal)
                    .ToLocalChecked(),
                FunctionTemplate::New(isolate, GetClassName,
                                      CreateMethodInfo(isolate, "getClass"))
                    ->GetFunction());
  CreateObjectMethods(isolate, v8object, env, object);
  return v8object;
}

void PrintMethods(JNIEnv *env, jobject object) {
  jclass objcls = env->GetObjectClass(object);
  jmethodID mid = env->GetMethodID(objcls, "getClass", "()Ljava/lang/Class;");
  jobject clsObj = env->CallObjectMethod(object, mid);
  cout << " ===============================" << endl;
  jclass cls = env->GetObjectClass(clsObj);
  mid = env->GetMethodID(cls, "getDeclaredMethods",
                         "()[Ljava/lang/reflect/Method;");
  jobjectArray array = (jobjectArray)env->CallObjectMethod(clsObj, mid);
  for (int i = 0; i < env->GetArrayLength(array); i++) {
    jobject methodobj = env->GetObjectArrayElement(array, i);
    jclass methodcls = env->GetObjectClass(methodobj);
    const char *str = NULL;

    mid = env->GetMethodID(methodcls, "getName", "()Ljava/lang/String;");
    jstring name = (jstring)env->CallObjectMethod(methodobj, mid);
    str = env->GetStringUTFChars(name, NULL);
    cout << "  >> " << str << endl;
    env->ReleaseStringUTFChars(name, str);
  }
}

jmethodID GetGenericSignatureMethod(JNIEnv *env, jobject object) {  // method
  jclass objcls = env->GetObjectClass(object);  // class<method>
  jmethodID mid = env->GetMethodID(objcls, "getClass", "()Ljava/lang/Class;");
  jobject clsObj =
      env->CallObjectMethod(object, mid);  // class<method> (object)
  cout << " ===============================" << endl;
  jclass cls = env->GetObjectClass(clsObj); // class of class
  mid = env->GetMethodID(cls, "getDeclaredMethods",
                         "()[Ljava/lang/reflect/Method;");
  jobjectArray array = (jobjectArray)env->CallObjectMethod(clsObj, mid);
  for (int i = 0; i < env->GetArrayLength(array); i++) {
    jobject methodobj = env->GetObjectArrayElement(array, i);
    jclass methodcls = env->GetObjectClass(methodobj);
    const char *str = NULL;

    mid = env->GetMethodID(methodcls, "getName", "()Ljava/lang/String;");
    jstring name = (jstring)env->CallObjectMethod(methodobj, mid);
    str = env->GetStringUTFChars(name, NULL);
    cout << "  compare " << str << endl;
    if (strcmp(str, "getGenericSignature") == 0) {
      env->ReleaseStringUTFChars(name, str);
      cout<<" xxx "<<env->FromReflectedMethod(methodobj)<< endl;
      return env->FromReflectedMethod(methodobj);
    }
    env->ReleaseStringUTFChars(name, str);
  }
  return NULL;
}

void JniWrapper::CreateObjectMethods(Isolate *isolate, Local<Object> v8object,
                                     JNIEnv *env, jobject object) {
  jclass objcls = env->GetObjectClass(object);
  jmethodID mid = env->GetMethodID(objcls, "getClass", "()Ljava/lang/Class;");
  jobject clsObj = env->CallObjectMethod(object, mid);
  jclass cls = env->GetObjectClass(clsObj);
  mid = env->GetMethodID(cls, "getDeclaredMethods",
                         "()[Ljava/lang/reflect/Method;");
  jobjectArray array = (jobjectArray)env->CallObjectMethod(clsObj, mid);
  for (int i = 0; i < env->GetArrayLength(array); i++) {
    jobject methodobj = env->GetObjectArrayElement(array, i);
    jclass methodcls = env->GetObjectClass(methodobj);
    const char *str = NULL;
    // PrintMethods(env, methodobj);

    mid = env->GetMethodID(methodcls, "getName", "()Ljava/lang/String;");
    jstring name = (jstring)env->CallObjectMethod(methodobj, mid);
    str = env->GetStringUTFChars(name, NULL);
    cout << "  >> " << str << endl;
    env->ReleaseStringUTFChars(name, str);

     mid = env->GetMethodID(methodcls, "getGenericSignature", "()Ljava/lang/String;");
    cout << mid << endl;
    name = (jstring)env->CallObjectMethod(methodobj, mid);
    cout << "   name   "<< name << endl;

    mid = GetGenericSignatureMethod(env, methodobj);
    cout << mid << endl;
    jstring signature = (jstring)env->CallObjectMethod(methodobj, mid);
    cout << "  >> " << signature << endl;
    str = env->GetStringUTFChars(signature, NULL);
    cout << "  >> " << str << endl;
    env->ReleaseStringUTFChars(signature, str);
  }
}

void JniWrapper::Register(Isolate *isolate, const char *name,
                          Local<Object> object) {
  isolate->GetCurrentContext()->Global()->Set(
      String::NewFromUtf8(isolate, name, NewStringType::kNormal)
          .ToLocalChecked(),
      object);
}

void JniWrapper::Invoke(const v8::FunctionCallbackInfo<v8::Value> &args) {
  Isolate *isolate = args.GetIsolate();
  JniWrapper *wrapper = ObjectWrap::Unwrap<JniWrapper>(args.Holder());
  JNIEnv *env = wrapper->env;
  jobject object = wrapper->jniObject;
  Local<String> methodName = GetMethodName(args);
}

Local<Object> JniWrapper::CreateMethodInfo(v8::Isolate *isolate,
                                           const char *methodName) {
  Local<ObjectTemplate> tpl = v8::ObjectTemplate::New(isolate);
  tpl->Set(String::NewFromUtf8(isolate, CALLBACK_METHOD_NAME_KEY,
                               NewStringType::kNormal)
               .ToLocalChecked(),
           String::NewFromUtf8(isolate, methodName, NewStringType::kNormal)
               .ToLocalChecked());
  return tpl->NewInstance();
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

  args.GetReturnValue().Set(
      String::NewFromUtf8(isolate, str, NewStringType::kNormal)
          .ToLocalChecked());

  env->ReleaseStringUTFChars(strObj, str);
}

Local<String> JniWrapper::GetMethodName(
    const FunctionCallbackInfo<v8::Value> &args) {
  Isolate *isolate = args.GetIsolate();
  Local<Object> obj = Local<Object>::Cast(args.Data());
  return Local<String>::Cast(
      obj->Get(String::NewFromUtf8(isolate, CALLBACK_METHOD_NAME_KEY,
                                   NewStringType::kNormal)
                   .ToLocalChecked()));
}

}  // namespace android
}  // namespace node
