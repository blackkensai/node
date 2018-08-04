#include "Test.h"
#include "node-embed.h"

JNIEXPORT void JNICALL Java_Test_node_1embed_1execute_1with(JNIEnv *env,
                                                            jobject o,
                                                            jstring script,
                                                            jobject object) {
  const char *str = env->GetStringUTFChars(script, NULL);
  node_embed_execute_with(str, env, object);
  env->ReleaseStringUTFChars(script, str);
}