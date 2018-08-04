#include "jni.h"
#include "node-android.h"
#include "node.h"
#include "node_api.h"
#include "node_buffer.h"
#include "node_internals.h"
#include "uv.h"
#include "v8.h"
#include "node_object_wrap.h"
#include <memory>
#include "jstring-wrapper.h"

using namespace std;
using namespace v8;

namespace node {
namespace android {

class JniWrapper : public ObjectWrap {
public:
  JniWrapper(v8::Isolate *isolate, JNIEnv *env, jobject object);
  ~JniWrapper();
  static Local<Object> CreateJSObject(v8::Isolate* isolate, JNIEnv *env, jobject object);
  // void invoke();
private:
  static void GetClassName(const FunctionCallbackInfo<v8::Value>& args);
  static void FreeJvmString(const char * str);
  JNIEnv *env;
  jobject jniObject;
  static v8::Persistent<v8::Function> constructor;
};

} // namespace android
} // namespace node