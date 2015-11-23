#include "FemasUtility.h"

jobject g_sessionObj;
CUstpFtdcTraderApi * g_puserapi=NULL;
int g_nOrdLocalID=0;

TUstpFtdcBrokerIDType g_BrokerID;
TUstpFtdcUserIDType g_UserID;
TUstpFtdcPasswordType g_Password;

jclass NativeWrapperException_Class = NULL;
jclass Session_Class = NULL;
jmethodID SessionClassOnRspUserLogin = NULL;
jmethodID SessionClassOnFrontDisconnected = NULL;
jmethodID SessionClassOnRspQryInstrument = NULL;
jmethodID SessionClassOnRtnInstrumentStatus = NULL;

//CUstpFtdcQryInstrumentField
jclass CUstpFtdcQryInstrumentField_Class = NULL;
jfieldID CUstpFtdcQryInstrumentFieldExchangeID_Field = NULL;
jfieldID CUstpFtdcQryInstrumentFieldProductID_Field = NULL;
jfieldID CUstpFtdcQryInstrumentFieldInstrumentID_Field = NULL;

//CUstpFtdcRspInfoField
jclass CUstpFtdcRspInfoField_Class = NULL;
jmethodID CUstpFtdcRspInfoField_Init = NULL;

//CUstpFtdcRspInstrumentField
jclass CUstpFtdcRspInstrumentField_Class = NULL;
jmethodID CUstpFtdcRspInstrumentField_Init = NULL;

//CUstpFtdcInstrumentStatusField
jclass CUstpFtdcInstrumentStatusField_Class = NULL;
jmethodID CUstpFtdcInstrumentStatusField_Init = NULL;


// ********************** JNI utilities begin

void JNU_checkInit(JNIEnv *env, void* toCheck)
{
    if (toCheck == NULL)
    {
        env->ThrowNew(NativeWrapperException_Class, JNIINIT_ERROR);
    }
}

jstring JNU_newString(JNIEnv *env, const char* str)
{
    jstring ret = NULL;
    ret = env->NewStringUTF(str == NULL ? "" : str);
    if (ret == NULL)
    {
        env->ThrowNew(NativeWrapperException_Class, NEWSTRING_ERROR);
    }
    return ret;
}

bool JNU_copyString(JNIEnv *env, const jstring& original, char *destination, int dlen)
{
    int olen = env->GetStringUTFLength(original);
    int len = (olen < dlen - 1 ? olen : dlen - 1);
    jboolean iscopy;
    const char *str = env->GetStringUTFChars(original, &iscopy);
    if (str == NULL)
    {
        env->ThrowNew(NativeWrapperException_Class, COPYSTRING_ERROR);
        return false;
    }
    memcpy(destination, str, len);
    env->ReleaseStringUTFChars(original, str);
    destination[len] = '\0';
    return true;
}

jbyteArray JNU_newByteArray(JNIEnv *env, jsize length, jbyte *buf)
{
    jbyteArray byteArray;
    if ((byteArray=env->NewByteArray(length)) == NULL)
    {
        env->ThrowNew(NativeWrapperException_Class, NEWBYTEARRAY_ERROR);
    }

    if (buf != NULL && length > 0)
    {
        env->SetByteArrayRegion(byteArray,0,length,buf);
    }
    return byteArray;
}

