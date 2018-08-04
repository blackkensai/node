#ifndef SRC_NODE_EMBED_H_
#define SRC_NODE_EMBED_H_

#include "jni.h"

extern "C" {
	int node_embed_execute(const char * script);
	int node_embed_execute_with(const char * script, JNIEnv *env, jobject object);
}

#endif