#include "com_ullink_jni_femas_wrapper_Session.h"
#include "TraderSpi.h"
#include "FemasUtility.h"
#include "FemasWrapperInitializer.h"


JNIEXPORT void JNICALL Java_com_ullink_jni_femas_wrapper_Session_femasInitialize (JNIEnv *env, jclass wrapperCls)
{
    _E_;

    if (NativeWrapperException_Class == NULL)
    {
        jclass cls = env->FindClass("com/ullink/jni/common/NativeWrapperException");
        JNU_checkInit(env, cls);
        NativeWrapperException_Class = (jclass) (env->NewGlobalRef(cls));
        env->DeleteLocalRef(cls);
        JNU_checkInit(env, NativeWrapperException_Class);
    }

    if (Session_Class == NULL)
    {
        Session_Class = (jclass) (env->NewGlobalRef(wrapperCls));
        env->DeleteLocalRef(wrapperCls);
        JNU_checkInit(env, Session_Class);
    }

    if (SessionClassOnRspUserLogin == NULL)
    {
        SessionClassOnRspUserLogin = env->GetMethodID(Session_Class, "onRspUserLogin", "(I[BLjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;IIIIZ)V");
        JNU_checkInit(env, SessionClassOnRspUserLogin);
    }

    if (SessionClassOnFrontDisconnected == NULL)
    {
        SessionClassOnFrontDisconnected = env->GetStaticMethodID(Session_Class, "onFrontDisconnected", "(I)V");
        JNU_checkInit(env, SessionClassOnFrontDisconnected);
    }

	if (SessionClassOnRspQryInstrument == NULL)
	{
		SessionClassOnRspQryInstrument = env->GetMethodID(Session_Class, "onRspQryInstrument", "(Lcom/ullink/jni/femas/wrapper/struct/CUstpFtdcRspInstrumentField;Lcom/ullink/jni/femas/wrapper/struct/CUstpFtdcRspInfoField;IZ)V");
		JNU_checkInit(env, SessionClassOnRspQryInstrument);
	}

	if (SessionClassOnRtnInstrumentStatus == NULL)
	{
		SessionClassOnRtnInstrumentStatus = env->GetMethodID(Session_Class, "onRtnInstrumentStatus", "(Lcom/ullink/jni/femas/wrapper/struct/CUstpFtdcRspInstrumentField;)V");
		JNU_checkInit(env, SessionClassOnRtnInstrumentStatus);
	}

	if (CUstpFtdcQryInstrumentField_Class == NULL)
	{
		jclass cls = env->FindClass("com/ullink/jni/femas/wrapper/struct/CUstpFtdcQryInstrumentField");
		JNU_checkInit(env, cls);
		CUstpFtdcQryInstrumentField_Class = (jclass)(env->NewGlobalRef(cls));
		env->DeleteLocalRef(cls);
		JNU_checkInit(env, CUstpFtdcQryInstrumentField_Class);

		CUstpFtdcQryInstrumentFieldExchangeID_Field = env->GetFieldID(CUstpFtdcQryInstrumentField_Class, "exchangeID", "Ljava/lang/String");
		CUstpFtdcQryInstrumentFieldProductID_Field = env->GetFieldID(CUstpFtdcQryInstrumentField_Class, "productID", "Ljava/lang/String");
		CUstpFtdcQryInstrumentFieldInstrumentID_Field = env->GetFieldID(CUstpFtdcQryInstrumentField_Class, "instrumentID", "Ljava/lang/String");
	}

	if (CUstpFtdcRspInfoField_Class == NULL)
	{
		jclass cls = env->FindClass("com/ullink/jni/femas/wrapper/struct/CUstpFtdcRspInfoField");
		JNU_checkInit(env, cls);
		CUstpFtdcRspInfoField_Class = (jclass)(env->NewGlobalRef(cls));
		env->DeleteLocalRef(cls);
		JNU_checkInit(env, CUstpFtdcRspInfoField_Class);

		CUstpFtdcRspInfoField_Init = env->GetMethodID(CUstpFtdcRspInfoField_Class, "<init>", "(ILjava/lang/String;)V");
	}

	if (CUstpFtdcRspInstrumentField_Class == NULL)
	{
		jclass cls = env->FindClass("com/ullink/jni/femas/wrapper/struct/CUstpFtdcRspInstrumentField");
		JNU_checkInit(env, cls);
		CUstpFtdcRspInstrumentField_Class = (jclass)(env->NewGlobalRef(cls));
		env->DeleteLocalRef(cls);
		JNU_checkInit(env, CUstpFtdcRspInstrumentField_Class);

		CUstpFtdcRspInstrumentField_Init = env->GetMethodID(CUstpFtdcRspInstrumentField_Class, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;IIIIIIIDCIIDDDCLjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;DZLjava/lang/String;ICDC)V");
	}

	if (CUstpFtdcInstrumentStatusField_Class == NULL)
	{
		jclass cls = env->FindClass("com/ullink/jni/femas/wrapper/struct/CUstpFtdcInstrumentStatusField");
		JNU_checkInit(env, cls);
		CUstpFtdcInstrumentStatusField_Class = (jclass)(env->NewGlobalRef(cls));
		env->DeleteLocalRef(cls);
		JNU_checkInit(env, CUstpFtdcInstrumentStatusField_Class);

		CUstpFtdcInstrumentStatusField_Init = env->GetMethodID(CUstpFtdcInstrumentStatusField_Class, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;IIIIIIIDCIIDDDCLjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;DZLjava/lang/String;ICDC)V");
	}

    _L_;
}

JNIEXPORT void JNICALL Java_com_ullink_jni_femas_wrapper_Session_femasDispose(JNIEnv *env, jclass wrapperCls)
{
    _E_;
    if (NativeWrapperException_Class != NULL)
    {
        env->DeleteGlobalRef(NativeWrapperException_Class);
        NativeWrapperException_Class = NULL;
    }

    if (Session_Class != NULL)
    {
        env->DeleteGlobalRef(Session_Class);
        Session_Class = NULL;
        SessionClassOnRspUserLogin = NULL;
        SessionClassOnFrontDisconnected = NULL;
		SessionClassOnRspQryInstrument = NULL;
		SessionClassOnRtnInstrumentStatus = NULL;
    }

	if (CUstpFtdcQryInstrumentField_Class != NULL)
	{
		env->DeleteGlobalRef(CUstpFtdcQryInstrumentField_Class);
	}

	if (CUstpFtdcRspInfoField_Class != NULL)
	{
		env->DeleteGlobalRef(CUstpFtdcRspInfoField_Class);
		CUstpFtdcRspInfoField_Init = NULL;
	}

	if (CUstpFtdcRspInstrumentField_Class != NULL)
	{
		env->DeleteGlobalRef(CUstpFtdcRspInstrumentField_Class);
		CUstpFtdcRspInstrumentField_Init = NULL;
	}

	if (CUstpFtdcInstrumentStatusField_Class != NULL)
	{
		env->DeleteGlobalRef(CUstpFtdcInstrumentStatusField_Class);
		CUstpFtdcInstrumentStatusField_Init = NULL;
	}


    _L_;
}

JNIEXPORT void JNICALL Java_com_ullink_jni_femas_wrapper_Session_femasLoginEx
    (JNIEnv *env, jobject wrapperObj, jstring frontAddress, jstring username, jstring password, jstring brokerId, jboolean subscribePublicTopic)
{
    _E_;
    g_sessionObj = env->NewGlobalRef(wrapperObj);
    env->DeleteLocalRef(wrapperObj);

    CUstpFtdcTraderApi *pTrader = CUstpFtdcTraderApi::CreateFtdcTraderApi("");
    g_puserapi=pTrader;

    JNU_copyString(env, username, g_UserID, sizeof(g_UserID));
    JNU_copyString(env, password, g_Password, sizeof(g_Password));
    JNU_copyString(env, brokerId, g_BrokerID, sizeof(g_BrokerID));

    char frontaddr[BUFLEN];

    JNU_copyString(env, frontAddress, frontaddr, sizeof(frontaddr));

    CTraderSpi spi(pTrader);
    pTrader->RegisterFront(frontaddr);
    pTrader->SubscribePrivateTopic(USTP_TERT_RESTART);
    if (subscribePublicTopic == JNI_TRUE)
    {
        pTrader->SubscribePublicTopic(USTP_TERT_RESTART);
    }
    pTrader->RegisterSpi(&spi);

    pTrader->Init();

    pTrader->Join();
    pTrader->Release();

    _L_;
    return;
}

JNIEXPORT void JNICALL Java_com_ullink_jni_femas_wrapper_Session_femasLogoutEx (JNIEnv *env, jobject wrapperObj, jstring brokerId, jstring username)
{
    _E_;
    CUstpFtdcReqUserLogoutField reqUserLogout;
    memset(&reqUserLogout,0,sizeof(CUstpFtdcReqUserLogoutField));

    JNU_copyString(env, brokerId, reqUserLogout.BrokerID, sizeof(reqUserLogout.BrokerID));
    JNU_copyString(env, username, reqUserLogout.UserID, sizeof(reqUserLogout.UserID));

    g_puserapi->ReqUserLogout(&reqUserLogout, g_nOrdLocalID++);
    _L_;
}

JNIEXPORT jint JNICALL Java_com_ullink_jni_femas_wrapper_Session_femasQryInstrument(JNIEnv *env, jobject wrapperObj, jobject pQryInstrument, jint nRequestID)
{
	_E_;
	CUstpFtdcQryInstrumentField qryField;
	memset(&qryField, 0, sizeof(CUstpFtdcQryInstrumentField));

	jstring exchangeID = (jstring) env->GetObjectField(pQryInstrument, CUstpFtdcQryInstrumentFieldExchangeID_Field);
	jstring productID = (jstring) env->GetObjectField(pQryInstrument, CUstpFtdcQryInstrumentFieldProductID_Field);
	jstring instrumentID = (jstring) env->GetObjectField(pQryInstrument, CUstpFtdcQryInstrumentFieldInstrumentID_Field);

	JNU_copyString(env, exchangeID, qryField.ExchangeID, sizeof(qryField.ExchangeID));
	JNU_copyString(env, productID, qryField.ProductID, sizeof(qryField.ProductID));
	JNU_copyString(env, instrumentID, qryField.InstrumentID, sizeof(qryField.InstrumentID));

	int ret = g_puserapi->ReqQryInstrument(&qryField, (int)nRequestID);

	_L_;
	return ret;
}
