// TraderSpi.cpp: implementation of the CTraderSpi class.

#include "TraderSpi.h"
#include "FemasWrapperInitializer.h"

CTraderSpi::CTraderSpi(CUstpFtdcTraderApi *pTrader):m_pUserApi(pTrader){}
CTraderSpi::~CTraderSpi(){}


void CTraderSpi::OnFrontConnected()
{
    CUstpFtdcReqUserLoginField reqUserLogin;
    memset(&reqUserLogin,0,sizeof(CUstpFtdcReqUserLoginField));

    memcpy(reqUserLogin.BrokerID,g_BrokerID, sizeof(g_BrokerID));
    memcpy(reqUserLogin.UserID, g_UserID, sizeof(g_UserID));
    memcpy(reqUserLogin.Password, g_Password, sizeof(g_Password));

    m_pUserApi->ReqUserLogin(&reqUserLogin, g_nOrdLocalID++);
}

void CTraderSpi::OnFrontDisconnected(int nReason)
{
    JNIEnv *env = getJNIEnv();
    env->CallStaticVoidMethod(Session_Class, SessionClassOnFrontDisconnected, nReason);
}

void CTraderSpi::OnRspUserLogin(CUstpFtdcRspUserLoginField *pRspUserLogin, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    JNIEnv *env = getJNIEnv();

    char * errMsg = pRspInfo->ErrorMsg;
    jbyteArray errMsgBytes = JNU_newByteArray(env, strlen(errMsg), (jbyte *)errMsg);

    jstring tradingDay = JNU_newString(env, pRspUserLogin->TradingDay);
    jstring brokerID = JNU_newString(env, pRspUserLogin->BrokerID);
    jstring userID = JNU_newString(env, pRspUserLogin->UserID);
    jstring loginTime = JNU_newString(env, pRspUserLogin->LoginTime);
    jstring maxOrderLocalID = JNU_newString(env, pRspUserLogin->MaxOrderLocalID);
    jstring tradingSystemName = JNU_newString(env, pRspUserLogin->TradingSystemName);

    env->CallVoidMethod(g_sessionObj, SessionClassOnRspUserLogin,
        pRspInfo->ErrorID,
        errMsgBytes,
        tradingDay,
        brokerID,
        userID,
        loginTime,
        maxOrderLocalID,
        tradingSystemName,
        pRspUserLogin->DataCenterID,
        pRspUserLogin->PrivateFlowSize,
        pRspUserLogin->UserFlowSize,
        nRequestID,
        bIsLast);
}

void CTraderSpi::OnRspUserLogout(CUstpFtdcRspUserLogoutField *pRspUserLogout, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
}

void CTraderSpi::OnRspOrderInsert(CUstpFtdcInputOrderField *pInputOrder, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void CTraderSpi::OnRtnTrade(CUstpFtdcTradeField *pTrade)
{

}

void CTraderSpi::OnRtnOrder(CUstpFtdcOrderField *pOrder)
{

}

void CTraderSpi::OnRspOrderAction(CUstpFtdcOrderActionField *pOrderAction, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void CTraderSpi::OnRspUserPasswordUpdate(CUstpFtdcUserPasswordUpdateField *pUserPasswordUpdate, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void CTraderSpi::OnErrRtnOrderInsert(CUstpFtdcInputOrderField *pInputOrder, CUstpFtdcRspInfoField *pRspInfo)
{

}

void CTraderSpi::OnErrRtnOrderAction(CUstpFtdcOrderActionField *pOrderAction, CUstpFtdcRspInfoField *pRspInfo)
{

}

void CTraderSpi::OnRspQryOrder(CUstpFtdcOrderField *pOrder, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void CTraderSpi::OnRspQryTrade(CUstpFtdcTradeField *pTrade, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void CTraderSpi::OnRspQryExchange(CUstpFtdcRspExchangeField *pRspExchange, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void CTraderSpi::OnRspQryInvestorAccount(CUstpFtdcRspInvestorAccountField *pRspInvestorAccount, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void CTraderSpi::OnRspQryUserInvestor(CUstpFtdcRspUserInvestorField *pUserInvestor, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

jobject ConvertCUstpFtdcRspInfoField(CUstpFtdcRspInfoField *pRspInfo)
{
	JNIEnv *env = getJNIEnv();
	return env->NewObject(
		CUstpFtdcRspInfoField_Class,
		CUstpFtdcRspInfoField_Init,
		pRspInfo->ErrorID,
		JNU_newString(env, pRspInfo->ErrorMsg)
	);
}

jobject ConvertCUstpFtdcRspInstrumentField(CUstpFtdcRspInstrumentField *pRspInstrument)
{
	JNIEnv *env = getJNIEnv();
	return env->NewObject(
		CUstpFtdcRspInstrumentField_Class,
		CUstpFtdcRspInstrumentField_Init,
		JNU_newString(env, pRspInstrument->ExchangeID),
		JNU_newString(env, pRspInstrument->ProductID),
		JNU_newString(env, pRspInstrument->ProductName),
		JNU_newString(env, pRspInstrument->InstrumentID),
		JNU_newString(env, pRspInstrument->InstrumentName),
		pRspInstrument->DeliveryYear,
		pRspInstrument->DeliveryMonth,
		pRspInstrument->MaxLimitOrderVolume,
		pRspInstrument->MinLimitOrderVolume,
		pRspInstrument->MaxMarketOrderVolume,
		pRspInstrument->MinMarketOrderVolume,
		pRspInstrument->VolumeMultiple,
		pRspInstrument->PriceTick,
		pRspInstrument->Currency,
		pRspInstrument->LongPosLimit,
		pRspInstrument->ShortPosLimit,
		pRspInstrument->LowerLimitPrice,
		pRspInstrument->UpperLimitPrice,
		pRspInstrument->PreSettlementPrice,
		pRspInstrument->InstrumentStatus,
		JNU_newString(env, pRspInstrument->CreateDate),
		JNU_newString(env, pRspInstrument->OpenDate),
		JNU_newString(env, pRspInstrument->ExpireDate),
		JNU_newString(env, pRspInstrument->StartDelivDate),
		JNU_newString(env, pRspInstrument->EndDelivDate),
		pRspInstrument->BasisPrice,
		pRspInstrument->IsTrading,
		JNU_newString(env, pRspInstrument->UnderlyingInstrID),
		pRspInstrument->UnderlyingMultiple,
		pRspInstrument->PositionType,
		pRspInstrument->StrikePrice,
		pRspInstrument->OptionsType
	);
}

jobject ConvertOnRtnInstrumentStatus(CUstpFtdcInstrumentStatusField *pInstrumentStatus)
{
	JNIEnv *env = getJNIEnv();
	return env->NewObject(
		CUstpFtdcInstrumentStatusField_Class,
		CUstpFtdcInstrumentStatusField_Init,
		JNU_newString(env, pInstrumentStatus->ExchangeID),
		JNU_newString(env, pInstrumentStatus->ProductID),
		JNU_newString(env, pInstrumentStatus->ProductName),
		JNU_newString(env, pInstrumentStatus->InstrumentID),
		JNU_newString(env, pInstrumentStatus->InstrumentName),
		pInstrumentStatus->DeliveryYear,
		pInstrumentStatus->DeliveryMonth,
		pInstrumentStatus->MaxLimitOrderVolume,
		pInstrumentStatus->MinLimitOrderVolume,
		pInstrumentStatus->MaxMarketOrderVolume,
		pInstrumentStatus->MinMarketOrderVolume,
		pInstrumentStatus->VolumeMultiple,
		pInstrumentStatus->PriceTick,
		pInstrumentStatus->Currency,
		pInstrumentStatus->LongPosLimit,
		pInstrumentStatus->ShortPosLimit,
		pInstrumentStatus->LowerLimitPrice,
		pInstrumentStatus->UpperLimitPrice,
		pInstrumentStatus->PreSettlementPrice,
		pInstrumentStatus->InstrumentStatus,
		JNU_newString(env, pInstrumentStatus->CreateDate),
		JNU_newString(env, pInstrumentStatus->OpenDate),
		JNU_newString(env, pInstrumentStatus->ExpireDate),
		JNU_newString(env, pInstrumentStatus->StartDelivDate),
		JNU_newString(env, pInstrumentStatus->EndDelivDate),
		pInstrumentStatus->BasisPrice,
		pInstrumentStatus->IsTrading,
		JNU_newString(env, pInstrumentStatus->UnderlyingInstrID),
		pInstrumentStatus->UnderlyingMultiple,
		pInstrumentStatus->PositionType,
		pInstrumentStatus->StrikePrice,
		pInstrumentStatus->OptionsType
	);
}

void CTraderSpi::OnRspQryInstrument(CUstpFtdcRspInstrumentField *pRspInstrument, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	JNIEnv *env = getJNIEnv();
	jobject rspInfo = ConvertCUstpFtdcRspInfoField(pRspInfo);
	jobject instrument = NULL;
	if (pRspInfo == NULL  || pRspInfo->ErrorID != 0)
	{
		instrument = ConvertCUstpFtdcRspInstrumentField(pRspInstrument);
	}
	env->CallVoidMethod(g_sessionObj, SessionClassOnRspQryInstrument, instrument, rspInfo, nRequestID, bIsLast);
}

void CTraderSpi::OnRspQryTradingCode(CUstpFtdcRspTradingCodeField *pTradingCode, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void CTraderSpi::OnRspQryInvestorPosition(CUstpFtdcRspInvestorPositionField *pRspInvestorPosition, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void CTraderSpi::OnRspQryInvestorFee(CUstpFtdcInvestorFeeField *pInvestorFee, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void CTraderSpi::OnRspQryInvestorMargin(CUstpFtdcInvestorMarginField *pInvestorMargin, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void CTraderSpi::OnRspQryComplianceParam(CUstpFtdcRspComplianceParamField *pRspComplianceParam, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void CTraderSpi::OnRtnInstrumentStatus(CUstpFtdcInstrumentStatusField *pInstrumentStatus)
{
	JNIEnv *env = getJNIEnv();
	jobject instrument = instrument = ConvertOnRtnInstrumentStatus(pInstrumentStatus);
	env->CallVoidMethod(g_sessionObj, SessionClassOnRtnInstrumentStatus, instrument);
}


void CTraderSpi::OnRtnInvestorAccountDeposit(CUstpFtdcInvestorAccountDepositResField *pInvestorAccountDepositRes)
{

}

void CTraderSpi::OnRspQuoteInsert(CUstpFtdcInputQuoteField* pInputQuote, CUstpFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{

}

void CTraderSpi::OnRspQuoteAction(CUstpFtdcQuoteActionField* pQuoteAction, CUstpFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{

}

void CTraderSpi::OnRspForQuote(CUstpFtdcReqForQuoteField* pReqForQuote, CUstpFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{

}

void CTraderSpi::OnRtnQuote(CUstpFtdcRtnQuoteField* pRtnQuote)
{

}

void CTraderSpi::OnErrRtnQuoteInsert(CUstpFtdcInputQuoteField* pInputQuote, CUstpFtdcRspInfoField* pRspInfo)
{

}

