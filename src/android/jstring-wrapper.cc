#include "jstring-wrapper.h"

JStringWrapper::JStringWrapper(JNIEnv *env, jstring jstr)
    : env(env), jstr(jstr) {
  cstr = env->GetStringUTFChars(jstr, NULL);
}

JStringWrapper::~JStringWrapper() { env->ReleaseStringUTFChars(jstr, cstr); }

const char *JStringWrapper::val() { return cstr; }