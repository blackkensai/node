#ifndef SRC_NODE_ANDROID_H_
#define SRC_NODE_ANDROID_H_

#include "jni.h"

namespace node {
namespace android {
void SaveJniObject(JNIEnv *env, jobject object);
}
}

#endif  // SRC_NODE_ANDROID_H_