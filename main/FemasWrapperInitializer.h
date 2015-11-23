#ifndef FEMAS_WRAPPER_INITIALIZER_H
#define FEMAS_WRAPPER_INITIALIZER_H

#include <jni.h>

JNIEnv *getJNIEnv();
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved);

#endif
