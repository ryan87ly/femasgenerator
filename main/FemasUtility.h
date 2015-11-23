#ifndef _Included_FemasUtility
#define _Included_FemasUtility

#include <jni.h>
#include "debug.h"
#include "USTPFtdcTraderApi.h"

#define COPYSTRING_ERROR "GetStringUTFChars failure"
#define NEWSTRING_ERROR "NewStringUTF failure"
#define NEWOBJECT_ERROR "NewObject failure"
#define JNIINIT_ERROR "JNI Initialization failed"
#define NEWBYTEARRAY_ERROR "NewByteArray failed"

extern int g_nOrdLocalID;
const int BUFLEN=512;
extern jobject g_sessionObj;
extern CUstpFtdcTraderApi * g_puserapi;
extern TUstpFtdcBrokerIDType g_BrokerID;
extern TUstpFtdcUserIDType g_UserID;
extern TUstpFtdcPasswordType g_Password;

extern jclass NativeWrapperException_Class;
extern jclass Session_Class;
extern jmethodID SessionClassOnRspUserLogin;
extern jmethodID SessionClassOnFrontDisconnected;
extern jmethodID SessionClassOnRspQryInstrument;
extern jmethodID SessionClassOnRtnInstrumentStatus;

//CUstpFtdcQryInstrumentField
extern jclass CUstpFtdcQryInstrumentField_Class;
extern jfieldID CUstpFtdcQryInstrumentFieldExchangeID_Field;
extern jfieldID CUstpFtdcQryInstrumentFieldProductID_Field;
extern jfieldID CUstpFtdcQryInstrumentFieldInstrumentID_Field;

//CUstpFtdcRspInfoField
extern jclass CUstpFtdcRspInfoField_Class;
extern jmethodID CUstpFtdcRspInfoField_Init;

//CUstpFtdcRspInstrumentField
extern jclass CUstpFtdcRspInstrumentField_Class;
extern jmethodID CUstpFtdcRspInstrumentField_Init;

//CUstpFtdcInstrumentStatusField
extern jclass CUstpFtdcInstrumentStatusField_Class;
extern jmethodID CUstpFtdcInstrumentStatusField_Init;


void JNU_checkInit(JNIEnv *env, void* toCheck);
jstring JNU_newString(JNIEnv *env, const char* str);
bool JNU_copyString(JNIEnv *env, const jstring& original, char *destination, int dlen);
jbyteArray JNU_newByteArray(JNIEnv *env, jsize length, jbyte *buf);

#endif
