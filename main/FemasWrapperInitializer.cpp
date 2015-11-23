#include "FemasWrapperInitializer.h"
#include "FemasUtility.h"

static JavaVM* cached_jvm;


JNIEnv *getJNIEnv()
{
    JNIEnv *env;

    cached_jvm->AttachCurrentThread((void **) &env, NULL);
    return env;
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved)
{
    _E_;
    JNIEnv *env;
    cached_jvm = jvm;
    if (jvm->GetEnv((void **)&env, JNI_VERSION_1_2))
    {
        return JNI_ERR;
    }
    _L_;
    return JNI_VERSION_1_2;
}

JNIEXPORT void JNICALL
JNI_OnUnload(JavaVM *jvm, void *reserved)
{
}
