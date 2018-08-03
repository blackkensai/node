#include "jni.h"

class JStringWrapper {
public:
  JStringWrapper(JNIEnv *env, jstring jstr);
  virtual ~JStringWrapper();
  const char *val();

private:
  JNIEnv *env;
  jstring jstr;
  const char *cstr;
};