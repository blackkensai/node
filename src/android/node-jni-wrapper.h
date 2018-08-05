#ifndef SRC_NODE_JNI_WRAPPER_H_
#define SRC_NODE_JNI_WRAPPER_H_

#include <memory>
#include "jni.h"
#include "jstring-wrapper.h"
#include "node-android.h"
#include "node.h"
#include "node_api.h"
#include "node_buffer.h"
#include "node_internals.h"
#include "node_object_wrap.h"
#include "uv.h"
#include "v8.h"

using namespace std;
using namespace v8;

namespace node {
namespace android {

class JniWrapper : public ObjectWrap {
 public:
  JniWrapper(v8::Isolate *isolate, JNIEnv *env, jobject object);
  ~JniWrapper();
  static Local<Object> CreateJSObject(v8::Isolate *isolate, JNIEnv *env,
                                      jobject object);
  void Register(Isolate *isolate, const char *name, Local<Object> object);
  static void Invoke(const v8::FunctionCallbackInfo<v8::Value> &args);

 private:
  static void GetClassName(const FunctionCallbackInfo<v8::Value> &args);
  static void FreeJvmString(const char *str);
  static Local<Object> CreateMethodInfo(v8::Isolate *isolate,
                                        const char *methodName);
  static Local<String> GetMethodName(
      const FunctionCallbackInfo<v8::Value> &args);
  static void CreateObjectMethods(Isolate *isolate, Local<Object> v8object,
                                  JNIEnv *env, jobject object);

  JNIEnv *env;
  jobject jniObject;
  static v8::Persistent<v8::Function> constructor;
};

}  // namespace android
}  // namespace node

#endif