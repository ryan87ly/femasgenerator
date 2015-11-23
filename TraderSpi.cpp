// TraderSpi.cpp: implementation of the CTraderSpi class.
//
//////////////////////////////////////////////////////////////////////

#include "TraderSpi.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


extern FILE * g_fpRecv;


CTraderSpi::CTraderSpi(CUstpFtdcTraderApi *pTrader):m_pUserApi(pTrader)
{
	
}

CTraderSpi::~CTraderSpi()
{

}


void CTraderSpi::OnFrontConnected()
{
	CUstpFtdcReqUserLoginField reqUserLogin;
	memset(&reqUserLogin,0,sizeof(CUstpFtdcReqUserLoginField));		
	strcpy(reqUserLogin.BrokerID,g_BrokerID);
	strcpy(reqUserLogin.UserID, g_UserID);
	strcpy(reqUserLogin.Password, g_Password);	
	strcpy(reqUserLogin.UserProductInfo,g_pProductInfo);		
	int r = m_pUserApi->ReqUserLogin(&reqUserLogin, g_nOrdLocalID);	
	printf("login result %d \n", r);
	
	printf("Requesting login，BrokerID=[%s]UserID=[%s]\n",g_BrokerID,g_UserID);
#ifdef WIN32
	Sleep(1000);
#else
	usleep(1000);
#endif
}

void CTraderSpi::OnRspQryTopic(CUstpFtdcDisseminationField *pDissemination, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	printf("OnRspQryTopic\n");
	if (pRspInfo != NULL&&pRspInfo->ErrorID != 0)
	{
		printf("-----------------------------\n");
		printf("OnRspQryTopic failed...error reason：%s\n", pRspInfo->ErrorMsg);
		printf("-----------------------------\n");
		return;
	}
	printf("SequenceSeries %d\n ", pDissemination->SequenceSeries);
	printf("SequenceNo %d\n ", pDissemination->SequenceNo);
}

void CTraderSpi::OnRspSubscribeTopic(CUstpFtdcDisseminationField *pDissemination, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	printf("OnRspSubscribeTopic\n");
	if(pRspInfo != NULL&&pRspInfo->ErrorID != 0)
	{
		printf("-----------------------------\n");
		printf("OnRspSubscribeTopic failed...error reason：%s\n", pRspInfo->ErrorMsg);
		printf("-----------------------------\n");
		return;
	}
	printf("SequenceSeries %d\n ", pDissemination->SequenceSeries);
	printf("SequenceNo %d\n ", pDissemination->SequenceNo);
}

void CTraderSpi::OnFrontDisconnected(int nReason) {
	printf("OnFrontDisconnected %d\n ", nReason);
	m_pUserApi->Release();
};

void CTraderSpi::OnPackageStart(int nTopicID, int nSequenceNo) {
	printf("OnPackageStart nTopicID: %d , nSequenceNo: %d \n", nTopicID, nSequenceNo);
};

void CTraderSpi::OnPackageEnd(int nTopicID, int nSequenceNo) {
	printf("OnPackageEnd nTopicID: %d , nSequenceNo: %d \n ", nTopicID, nSequenceNo);
};


void CTraderSpi::OnRspUserLogin(CUstpFtdcRspUserLoginField *pRspUserLogin, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (pRspInfo!=NULL&&pRspInfo->ErrorID!=0)
	{
		printf("-----------------------------\n");
		printf("Login failed...error reason：%s\n",pRspInfo->ErrorMsg);
		printf("-----------------------------\n");
		return;
	}
	g_nOrdLocalID=atoi(pRspUserLogin->MaxOrderLocalID)+1;
 	printf("-----------------------------\n");
 	printf("Login success，MaxOrderLocalID:%s\n", pRspUserLogin->MaxOrderLocalID);
	printf("TradingSystemName %s\n", pRspUserLogin->TradingSystemName);
	printf("PrivateFlowSize %d\n", pRspUserLogin->PrivateFlowSize);
	printf("UserFlowSize %d\n", pRspUserLogin->UserFlowSize);
 	printf("-----------------------------\n");

 	StartAutoOrder();//连接success后就开始起一个线程开始操作 hui
}

void OnRspUserLogout(CUstpFtdcRspUserLogoutField *pRspUserLogout, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if (pRspInfo != NULL&&pRspInfo->ErrorID != 0)
	{
		printf("-----------------------------\n");
		printf("Logout failed...error reason：%s\n", pRspInfo->ErrorMsg);
		printf("-----------------------------\n");
		return;
	}
	printf("-----------Logout success------------------\n");
	printf("UserId:%s\n", pRspUserLogout->UserID);
	printf("BrokerId:%s\n", pRspUserLogout->BrokerID);
	printf("-----------------------------\n");
}

void CTraderSpi::OnRspOrderInsert(CUstpFtdcInputOrderField *pInputOrder, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (pRspInfo!=NULL&&pRspInfo->ErrorID!=0)
	{
		printf("-----------------------------\n");
		printf("order input failed, error reason：%s , nRequestID: %d \n",pRspInfo->ErrorMsg, nRequestID);
		printf("order input failed, error id：%d\n", pRspInfo->ErrorID);
		printf("-----------------------------\n");
		return;
	}
	if(pInputOrder==NULL)
	{
		printf("no order data\n");
		return;
	}
	printf("-----------------------------\n");
	printf("order input success, nRequestID: %d \n", nRequestID);
	printf("-----------------------------\n");
	return ;
	
}
void CTraderSpi::OnRtnTrade(CUstpFtdcTradeField *pTrade)
{
	printf("-----------------------------\n");
	printf("trade received\n");
	Show(pTrade);
	printf("-----------------------------\n");
	return;
}

void CTraderSpi::Show(CUstpFtdcOrderField *pOrder)
{
	printf("-----------------------------\n");
	printf("BrokerID=[%s]\n", pOrder->BrokerID);
	printf("ExchangeID=[%s]\n",pOrder->ExchangeID);
	printf("TradingDay=[%s]\n",pOrder->TradingDay);
	printf("ParticipantID=[%s]\n",pOrder->ParticipantID);
	printf("SeatID=[%s]\n",pOrder->SeatID);
	printf("UserID=[%s]\n", pOrder->UserID);
	printf("InvestorID=[%s]\n",pOrder->InvestorID);
	printf("ClientID=[%s]\n",pOrder->ClientID);
	printf("OrderSysID=[%s]\n",pOrder->OrderSysID);
	printf("OrderLocalID=[%s]\n",pOrder->OrderLocalID);
	printf("UserOrderLocalID=[%s]\n",pOrder->UserOrderLocalID);
	printf("InstrumentID=[%s]\n",pOrder->InstrumentID);
	printf("OrderPriceType=[%c]\n",pOrder->OrderPriceType);
	printf("Direction=[%c]\n",pOrder->Direction);
	printf("OffsetFlag=[%c]\n",pOrder->OffsetFlag);
	printf("HedgeFlag=[%c]\n",pOrder->HedgeFlag);
	printf("LimitPrice=[%lf]\n",pOrder->LimitPrice);
	printf("Volume=[%d]\n",pOrder->Volume);
	printf("VolumeCondition=[%]\n", pOrder->VolumeCondition);
	printf("OrderSource=[%c]\n",pOrder->OrderSource);
	printf("OrderStatus=[%c]\n",pOrder->OrderStatus);
	printf("InsertTime=[%s]\n",pOrder->InsertTime);
	printf("TimeCondition=[%c]\n",pOrder->TimeCondition);
	printf("GTDDate=[%s]\n",pOrder->GTDDate);
	printf("MinVolume=[%d]\n",pOrder->MinVolume);
	printf("StopPrice=[%lf]\n",pOrder->StopPrice);
	printf("ForceCloseReason=[%c]\n",pOrder->ForceCloseReason);
	printf("IsAutoSuspend=[%d]\n",pOrder->IsAutoSuspend);
	printf("CancelTime=[%s]\n", pOrder->CancelTime);
	printf("CancelUserID=[%s]\n", pOrder->CancelUserID);
	printf("VolumeTraded=[%d]\n", pOrder->VolumeTraded);
	printf("VolumeRemain=[%d]\n", pOrder->VolumeRemain);
	printf("-----------------------------\n");
	return ;
}

void CTraderSpi::OnRtnOrder(CUstpFtdcOrderField *pOrder)
{
	printf("-----------------------------\n");
	printf("OnRtnOrder: \n");
	Show(pOrder);
	printf("-----------------------------\n");
	return ;
}

void CTraderSpi::OnRspOrderAction(CUstpFtdcOrderActionField *pOrderAction, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (pRspInfo!=NULL&&pRspInfo->ErrorID!=0)
	{
		printf("-----------------------------\n");
		printf("cancel order failed, error reason：%s\n",pRspInfo->ErrorMsg);
		printf("-----------------------------\n");
		return;
	}
	if(pOrderAction==NULL)
	{
		printf("no cancelled order data\n");
		return;
	}
	printf("-----------------------------\n");
	printf("cancel success\n");
	printf("-----------------------------\n");
	return ;
}
void CTraderSpi::OnRspUserPasswordUpdate(CUstpFtdcUserPasswordUpdateField *pUserPasswordUpdate, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (pRspInfo!=NULL&&pRspInfo->ErrorID!=0)
	{
		printf("-----------------------------\n");
		printf("修改密码failed error reason：%s\n",pRspInfo->ErrorMsg);
		printf("-----------------------------\n");
		return;
	}
	if(pUserPasswordUpdate==NULL)
	{
		printf("没有修改密码数据\n");
		return;
	}
	printf("-----------------------------\n");
	printf("修改密码success\n");
	printf("-----------------------------\n");
	return ;
}

void CTraderSpi::OnErrRtnOrderInsert(CUstpFtdcInputOrderField *pInputOrder, CUstpFtdcRspInfoField *pRspInfo)
{
	if (pRspInfo!=NULL&&pRspInfo->ErrorID!=0)
	{
		printf("-----------------------------\n");
		printf(" order insert  error  response , error reason：%s\n",pRspInfo->ErrorMsg);
		printf("-----------------------------\n");
		return;
	}
	if(pInputOrder==NULL)
	{
		printf("no data\n");
		return;
	}
	printf("-----------------------------\n");
	printf(" order insert  error  response \n");
	printf("-----------------------------\n");
	return ;
}
void CTraderSpi::OnErrRtnOrderAction(CUstpFtdcOrderActionField *pOrderAction, CUstpFtdcRspInfoField *pRspInfo)
{
	if (pRspInfo!=NULL&&pRspInfo->ErrorID!=0)
	{
		printf("-----------------------------\n");
		printf(" order cancellation  error  response, failed error reason：%s\n",pRspInfo->ErrorMsg);
		printf("-----------------------------\n");
		return;
	}
	if(pOrderAction==NULL)
	{
		printf("no data\n");
		return;
	}
	printf("-----------------------------\n");
	printf(" order cancellation  error  response \n");
	printf("-----------------------------\n");
	return ;
}

void CTraderSpi::OnRspQryOrder(CUstpFtdcOrderField *pOrder, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (pRspInfo!=NULL&&pRspInfo->ErrorID!=0)
	{
		printf("-----------------------------\n");
		printf(" query order input failed error reason：%s\n",pRspInfo->ErrorMsg);
		printf("-----------------------------\n");
		return;
	}
	if(pOrder==NULL)
	{
		printf("did not get query order input data\n");
		return;
	}
	printf("OnRspQryOrder , bIsLast: %d\n", bIsLast);
	Show(pOrder);
	return ;
}
void CTraderSpi::Show(CUstpFtdcTradeField *pTrade)
{
	printf("-----------------------------\n");
	printf("BrokerID=[%s]\n", pTrade->BrokerID);
	printf("ExchangeID=[%s]\n",pTrade->ExchangeID);
	printf("TradingDay=[%s]\n",pTrade->TradingDay);
	printf("ParticipantID=[%s]\n",pTrade->ParticipantID);
	printf("SeatID=[%s]\n",pTrade->SeatID);
	printf("InvestorID=[%s]\n",pTrade->InvestorID);
	printf("ClientID=[%s]\n",pTrade->ClientID);
	printf("UserID=[%s]\n", pTrade->UserID);
	printf("TradeID=[%s]\n",pTrade->TradeID);
	printf("OrderSysID=[%s]\n", pTrade->OrderSysID);
	printf("UserOrderLocalID=[%s]\n",pTrade->UserOrderLocalID);
	printf("InstrumentID=[%s]\n",pTrade->InstrumentID);
	printf("Direction=[%c]\n",pTrade->Direction);
	printf("OffsetFlag=[%c]\n",pTrade->OffsetFlag);
	printf("HedgeFlag=[%c]\n",pTrade->HedgeFlag);
	printf("TradePrice=[%lf]\n",pTrade->TradePrice);
	printf("TradeVolume=[%d]\n",pTrade->TradeVolume);
	printf("TradeTime=[%d]\n", pTrade->TradeTime);
	printf("ClearingPartID=[%s]\n",pTrade->ClearingPartID);
	
	printf("-----------------------------\n");
	return ;
}
void CTraderSpi::OnRspQryTrade(CUstpFtdcTradeField *pTrade, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (pRspInfo!=NULL&&pRspInfo->ErrorID!=0)
	{
		printf("-----------------------------\n");
		printf(" query trade failed, error reason：%s\n",pRspInfo->ErrorMsg);
		printf("-----------------------------\n");
		return;
	}
	if(pTrade==NULL)
	{
		printf("no trade data found");
		return;
	}
	Show(pTrade);
	return ;
}
void CTraderSpi::OnRspQryExchange(CUstpFtdcRspExchangeField *pRspExchange, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (pRspInfo!=NULL&&pRspInfo->ErrorID!=0)
	{
		printf("-----------------------------\n");
		printf(" query exchange failed, error reason：%s\n",pRspInfo->ErrorMsg);
		printf("-----------------------------\n");
		return;
	}
	if (pRspExchange==NULL)
	{
		printf("no exchange data\n");
		return ;
	}
	printf("----------OnRspQryExchange bIsLast: %d -------------------\n", bIsLast);
	printf("[%s]\n",pRspExchange->ExchangeID);
	printf("[%s]\n",pRspExchange->ExchangeName);
	printf("-----------------------------\n");
	return;
}

void CTraderSpi::OnRspQryInvestorAccount(CUstpFtdcRspInvestorAccountField *pRspInvestorAccount, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (pRspInfo!=NULL&&pRspInfo->ErrorID!=0)
	{
		printf("-----------------------------\n");
		printf(" query investor account failed, error reason：%s\n",pRspInfo->ErrorMsg);
		printf("-----------------------------\n");
		return;
	}
	
	if (pRspInvestorAccount==NULL)
	{
		printf("no investor acc data\n");
		return ;
	}
	printf("-----------------------------\n");
	printf("InvestorID=[%s]\n",pRspInvestorAccount->InvestorID);
	printf("AccountID=[%s]\n",pRspInvestorAccount->AccountID);
	printf("PreBalance=[%lf]\n",pRspInvestorAccount->PreBalance);
	printf("Deposit=[%lf]\n",pRspInvestorAccount->Deposit);
	printf("Withdraw=[%lf]\n",pRspInvestorAccount->Withdraw);
	printf("FrozenMargin=[%lf]\n",pRspInvestorAccount->FrozenMargin);
	printf("FrozenFee=[%lf]\n",pRspInvestorAccount->FrozenFee);
	printf("Fee=[%lf]\n",pRspInvestorAccount->Fee);
	printf("CloseProfit=[%lf]\n",pRspInvestorAccount->CloseProfit);
	printf("PositionProfit=[%lf]\n",pRspInvestorAccount->PositionProfit);
	printf("Available=[%lf]\n",pRspInvestorAccount->Available);
	printf("LongFrozenMargin=[%lf]\n",pRspInvestorAccount->LongFrozenMargin);
	printf("ShortFrozenMargin=[%lf]\n",pRspInvestorAccount->ShortFrozenMargin);
	printf("LongMargin=[%lf]\n",pRspInvestorAccount->LongMargin);
	printf("ShortMargin=[%lf]\n",pRspInvestorAccount->ShortMargin);
	printf("-----------------------------\n");

}

void CTraderSpi::OnRspQryUserInvestor(CUstpFtdcRspUserInvestorField *pUserInvestor, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (pRspInfo!=NULL&&pRspInfo->ErrorID!=0)
	{
		printf("-----------------------------\n");
		printf(" query Investor failed error reason：%s\n",pRspInfo->ErrorMsg);
		printf("-----------------------------\n");
		return;
	}
	if (pUserInvestor==NULL)
	{
		printf("No data\n");
		return ;
	}
	
	printf("InvestorID=[%s]\n",pUserInvestor->InvestorID);
}

void CTraderSpi::Show(CUstpFtdcRspInstrumentField *pRspInstrument)
{
	printf("-----------------------------\n");
	printf("ExchangeID=[%s]\n",pRspInstrument->ExchangeID);
	printf("ProductID=[%s]\n",pRspInstrument->ProductID);
	printf("ProductName=[%s]\n",pRspInstrument->ProductName);
	printf("InstrumentID=[%s]\n",pRspInstrument->InstrumentID);
	printf("InstrumentName=[%s]\n",pRspInstrument->InstrumentName);
	printf("DeliveryYear=[%d]\n",pRspInstrument->DeliveryYear);
	printf("DeliveryMonth=[%d]\n",pRspInstrument->DeliveryMonth);
	printf("MaxLimitOrderVolume=[%d]\n",pRspInstrument->MaxLimitOrderVolume);
	printf("MinLimitOrderVolume=[%d]\n",pRspInstrument->MinLimitOrderVolume);
	printf("MaxMarketOrderVolume=[%d]\n",pRspInstrument->MaxMarketOrderVolume);
	printf("MinMarketOrderVolume=[%d]\n",pRspInstrument->MinMarketOrderVolume);
	
	printf("VolumeMultiple=[%d]\n",pRspInstrument->VolumeMultiple);
	printf("PriceTick=[%lf]\n",pRspInstrument->PriceTick);
	printf("Currency=[%c]\n",pRspInstrument->Currency);
	printf("LongPosLimit=[%d]\n",pRspInstrument->LongPosLimit);
	printf("ShortPosLimit=[%d]\n",pRspInstrument->ShortPosLimit);
	printf("LowerLimitPrice=[%lf]\n",pRspInstrument->LowerLimitPrice);
	printf("UpperLimitPrice=[%lf]\n",pRspInstrument->UpperLimitPrice);
	printf("PreSettlementPrice=[%lf]\n",pRspInstrument->PreSettlementPrice);
	printf("InstrumentStatus=[%c]\n",pRspInstrument->InstrumentStatus);
	printf("InstrumentStatusInt=[%d]\n", pRspInstrument->InstrumentStatus - 0);
	
	printf("CreateDate=[%s]\n",pRspInstrument->CreateDate);
	printf("OpenDate=[%s]\n",pRspInstrument->OpenDate);
	printf("ExpireDate=[%s]\n",pRspInstrument->ExpireDate);
	printf("StartDelivDate=[%s]\n",pRspInstrument->StartDelivDate);
	printf("EndDelivDate=[%s]\n",pRspInstrument->EndDelivDate);
	printf("BasisPrice=[%lf]\n",pRspInstrument->BasisPrice);
	printf("IsTrading=[%d]\n",pRspInstrument->IsTrading);
	printf("UnderlyingInstrID=[%s]\n",pRspInstrument->UnderlyingInstrID);
	printf("PositionType=[%c]\n",pRspInstrument->PositionType);
	printf("StrikePrice=[%e]\n",pRspInstrument->StrikePrice);
	printf("OptionsType=[%c]\n",pRspInstrument->OptionsType);
	printf("-----------------------------\n");
		//return ;
	
}
FILE *stream;
void CTraderSpi::OnRspQryInstrument(CUstpFtdcRspInstrumentField *pRspInstrument, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if (pRspInfo!=NULL&&pRspInfo->ErrorID!=0)
	{
		printf(" query instrument failed error reason：%s\n",pRspInfo->ErrorMsg);
		return;
	}
	
	if (pRspInstrument==NULL)
	{
		printf("no instrument data\n");
		return ;
	}
	if (stream == NULL)
	{
		if ((stream = freopen("filenon.txt", "w", stdout)) == NULL)
			exit(-1);
	}
	printf("-------OnRspQryInstrument, isLast: %d , nRequestID: %d -------- \n", bIsLast, nRequestID);
	Show(pRspInstrument);
	if (bIsLast == 1 && stream != NULL)
	{
		fclose(stream);
	}
	return ;
}

void CTraderSpi::OnRspQryTradingCode(CUstpFtdcRspTradingCodeField *pTradingCode, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (pRspInfo!=NULL&&pRspInfo->ErrorID!=0)
	{
		printf(" query trading code failed error reason：%s\n",pRspInfo->ErrorMsg);
		return;
	}
	
	if (pTradingCode==NULL)
	{
		printf("no query trading code \n");
		return ;
	}
	printf("-----------------------------\n");
	printf("ExchangeID=[%s]\n",pTradingCode->ExchangeID);
	printf("BrokerID=[%s]\n",pTradingCode->BrokerID);
	printf("InvestorID=[%s]\n",pTradingCode->InvestorID);
	printf("ClientID=[%s]\n",pTradingCode->ClientID);
	printf("ClientRight=[%d]\n",pTradingCode->ClientRight);
	printf("IsActive=[%c]\n",pTradingCode->IsActive);
	printf("-----------------------------\n");
	return ;
}

void CTraderSpi::OnRspQryInvestorPosition(CUstpFtdcRspInvestorPositionField *pRspInvestorPosition, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if (pRspInfo!=NULL&&pRspInfo->ErrorID!=0)
	{
		printf(" query Investor Position failed, error reason：%s\n",pRspInfo->ErrorMsg);
		return;
	}
	
	if (pRspInvestorPosition==NULL)
	{
		printf("no Investor Position data\n");
		return ;
	}
	printf("-----------------------------\n");
	printf("ExchangeID=[%s]\n",pRspInvestorPosition->ExchangeID);
	printf("BrokerID=[%s]\n",pRspInvestorPosition->BrokerID);
	printf("InvestorID=[%s]\n",pRspInvestorPosition->InvestorID);
	printf("ClientID=[%s]\n",pRspInvestorPosition->ClientID);
	printf("InstrumentID=[%s]\n",pRspInvestorPosition->InstrumentID);
	printf("Direction=[%c]\n",pRspInvestorPosition->Direction);
	printf("Position=[%d]\n",pRspInvestorPosition->Position);
	printf("-----------------------------\n");
	return ;

}

	///投资者手续费率 query应答
void CTraderSpi::OnRspQryInvestorFee(CUstpFtdcInvestorFeeField *pInvestorFee, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if (pRspInfo!=NULL&&pRspInfo->ErrorID!=0)
	{
		printf(" query Investor Fee failed error reason：%s\n",pRspInfo->ErrorMsg);
		return;
	}
	
	if (pInvestorFee==NULL)
	{
		printf("no Investor Fee data\n");
		return ;
	}
	printf("-----------------------------\n");
	printf("BrokerID=[%s]\n",pInvestorFee->BrokerID);
	printf("InstrumentID=[%s]\n",pInvestorFee->InstrumentID);
	printf("ClientID=[%s]\n",pInvestorFee->ClientID);
	printf("OpenFeeRate=[%f]\n",pInvestorFee->OpenFeeRate);
	printf("OpenFeeAmt=[%f]\n",pInvestorFee->OpenFeeAmt);
	printf("OffsetFeeRate=[%f]\n",pInvestorFee->OffsetFeeRate);
	printf("OffsetFeeAmt=[%f]\n",pInvestorFee->OffsetFeeAmt);
	printf("OTFeeRate=[%f]\n",pInvestorFee->OTFeeRate);
	printf("OTFeeAmt=[%f]\n",pInvestorFee->OTFeeAmt);
	printf("-----------------------------\n");
	return ;

}

	///投资者保证金率 query应答
void CTraderSpi::OnRspQryInvestorMargin(CUstpFtdcInvestorMarginField *pInvestorMargin, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if (pRspInfo!=NULL&&pRspInfo->ErrorID!=0)
	{
		printf(" QryInvestorMargin  failed error reason：%s\n",pRspInfo->ErrorMsg);
		return;
	}
	
	if (pInvestorMargin==NULL)
	{
		printf("no Investor Margin data \n");
		return ;
	}
	printf("-----------------------------\n");
	printf("BrokerID=[%s]\n",pInvestorMargin->BrokerID);
	printf("InstrumentID=[%s]\n",pInvestorMargin->InstrumentID);
	printf("ClientID=[%s]\n",pInvestorMargin->ClientID);
	printf("LongMarginRate=[%f]\n",pInvestorMargin->LongMarginRate);
	printf("LongMarginAmt=[%f]\n",pInvestorMargin->LongMarginAmt);
	printf("ShortMarginRate=[%f]\n",pInvestorMargin->ShortMarginRate);
	printf("ShortMarginAmt=[%f]\n",pInvestorMargin->ShortMarginAmt);
	printf("-----------------------------\n");
	return ;

}


void CTraderSpi::OnRspQryComplianceParam(CUstpFtdcRspComplianceParamField *pRspComplianceParam, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	if (pRspInfo!=NULL&&pRspInfo->ErrorID!=0)
	{
		printf(" query Compliance Param failed, error reason：%s\n",pRspInfo->ErrorMsg);
		return;
	}
	
	if (pRspComplianceParam==NULL)
	{
		printf("no Compliance Param data\n");
		return ;
	}
	printf("-----------------------------\n");
	printf("BrokerID=[%s]\n",pRspComplianceParam->BrokerID);
	printf("ClientID=[%s]\n",pRspComplianceParam->ClientID);
	printf("DailyMaxOrder=[%d]\n",pRspComplianceParam->DailyMaxOrder);
	printf("DailyMaxOrderAction=[%d]\n",pRspComplianceParam->DailyMaxOrderAction);
	printf("DailyMaxErrorOrder=[%d]\n",pRspComplianceParam->DailyMaxErrorOrder);
	printf("DailyMaxOrderVolume=[%d]\n",pRspComplianceParam->DailyMaxOrderVolume);
	printf("DailyMaxOrderActionVolume=[%d]\n",pRspComplianceParam->DailyMaxOrderActionVolume);
	printf("-----------------------------\n");
	return ;


}


int icount=0;
void CTraderSpi::OnRtnInstrumentStatus(CUstpFtdcInstrumentStatusField *pInstrumentStatus)
{
	if (pInstrumentStatus==NULL)
	{
		printf("no instrument status\n");
		return ;
	}
	icount++;
	
	printf("-------------OnRtnInstrumentStatus----------------\n");
	printf("ExchangeID=[%s]\n",pInstrumentStatus->ExchangeID);
	printf("ProductID=[%s]\n",pInstrumentStatus->ProductID);
	printf("ProductName=[%s]\n",pInstrumentStatus->ProductName);
	printf("InstrumentID=[%s]\n",pInstrumentStatus->InstrumentID);
	printf("InstrumentName=[%s]\n",pInstrumentStatus->InstrumentName);
	printf("DeliveryYear=[%d]\n",pInstrumentStatus->DeliveryYear);
	printf("DeliveryMonth=[%d]\n",pInstrumentStatus->DeliveryMonth);
	printf("MaxLimitOrderVolume=[%d]\n",pInstrumentStatus->MaxLimitOrderVolume);
	printf("MinLimitOrderVolume=[%d]\n",pInstrumentStatus->MinLimitOrderVolume);
	printf("MaxMarketOrderVolume=[%d]\n",pInstrumentStatus->MaxMarketOrderVolume);
	printf("MinMarketOrderVolume=[%d]\n",pInstrumentStatus->MinMarketOrderVolume);
	
	printf("VolumeMultiple=[%d]\n",pInstrumentStatus->VolumeMultiple);
	printf("PriceTick=[%lf]\n",pInstrumentStatus->PriceTick);
	printf("Currency=[%c]\n",pInstrumentStatus->Currency);
	printf("LongPosLimit=[%d]\n",pInstrumentStatus->LongPosLimit);
	printf("ShortPosLimit=[%d]\n",pInstrumentStatus->ShortPosLimit);
	printf("LowerLimitPrice=[%lf]\n",pInstrumentStatus->LowerLimitPrice);
	printf("UpperLimitPrice=[%lf]\n",pInstrumentStatus->UpperLimitPrice);
	printf("PreSettlementPrice=[%lf]\n",pInstrumentStatus->PreSettlementPrice);
	printf("InstrumentStatus=[%c]\n",pInstrumentStatus->InstrumentStatus);
	
	printf("CreateDate=[%s]\n",pInstrumentStatus->CreateDate);
	printf("OpenDate=[%s]\n",pInstrumentStatus->OpenDate);
	printf("ExpireDate=[%s]\n",pInstrumentStatus->ExpireDate);
	printf("StartDelivDate=[%s]\n",pInstrumentStatus->StartDelivDate);
	printf("EndDelivDate=[%s]\n",pInstrumentStatus->EndDelivDate);
	printf("BasisPrice=[%lf]\n",pInstrumentStatus->BasisPrice);
	printf("IsTrading=[%d]\n",pInstrumentStatus->IsTrading);
	printf("UnderlyingInstrID=[%s]\n",pInstrumentStatus->UnderlyingInstrID);
	printf("PositionType=[%c]\n",pInstrumentStatus->PositionType);
	printf("StrikePrice=[%lf]\n",pInstrumentStatus->StrikePrice);
	printf("OptionsType=[%c]\n",pInstrumentStatus->OptionsType);

	printf("-----------------------------\n");
	printf("[%d]",icount);
	return ;

}


void CTraderSpi::OnRtnInvestorAccountDeposit(CUstpFtdcInvestorAccountDepositResField *pInvestorAccountDepositRes)
{
	if (pInvestorAccountDepositRes==NULL)
	{
		printf("没有资金推送信息\n");
		return ;
	}

	printf("-----------------------------\n");
	printf("BrokerID=[%s]\n",pInvestorAccountDepositRes->BrokerID);
	printf("UserID＝[%s]\n",pInvestorAccountDepositRes->UserID);
	printf("InvestorID=[%s]\n",pInvestorAccountDepositRes->InvestorID);
	printf("AccountID=[%s]\n",pInvestorAccountDepositRes->AccountID);
	printf("AccountSeqNo＝[%s]\n",pInvestorAccountDepositRes->AccountSeqNo);
	printf("Amount＝[%s]\n",pInvestorAccountDepositRes->Amount);
	printf("AmountDirection＝[%s]\n",pInvestorAccountDepositRes->AmountDirection);
	printf("Available＝[%s]\n",pInvestorAccountDepositRes->Available);
	printf("Balance＝[%s]\n",pInvestorAccountDepositRes->Balance);
	printf("-----------------------------\n");
	return ;

}

void CTraderSpi::OnRspQuoteInsert(CUstpFtdcInputQuoteField* pInputQuote, CUstpFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	if (pRspInfo!=NULL&&pRspInfo->ErrorID!=0)
	{
		printf("-----------------------------\n");
		printf("报价录入failed error reason：%s\n",pRspInfo->ErrorMsg);
		printf("-----------------------------\n");
		return;
	}
	if(pInputQuote==NULL)
	{
		printf("没有报价录入数据\n");
		return;
	}
	printf("-----------------------------\n");
	printf("报价录入success\n");
	printf("-----------------------------\n");
	return ;
}

void CTraderSpi::OnRspQuoteAction(CUstpFtdcQuoteActionField* pQuoteAction, CUstpFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	if (pRspInfo!=NULL&&pRspInfo->ErrorID!=0)
	{
		printf("-----------------------------\n");
		printf("撤销报价failed error reason：%s\n",pRspInfo->ErrorMsg);
		printf("-----------------------------\n");
		return;
	}
	if(pQuoteAction==NULL)
	{
		printf("没有撤销报价数据\n");
		return;
	}
	printf("-----------------------------\n");
	printf("撤销报价success\n");
	printf("-----------------------------\n");
	return ;
}

void CTraderSpi::OnRspForQuote(CUstpFtdcReqForQuoteField* pReqForQuote, CUstpFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	if (pRspInfo!=NULL&&pRspInfo->ErrorID!=0)
	{
		printf("-----------------------------\n");
		printf("询价failed error reason：%s\n",pRspInfo->ErrorMsg);
		printf("-----------------------------\n");
		return;
	}
	if(pReqForQuote==NULL)
	{
		printf("没有询价数据\n");
		return;
	}
	printf("-----------------------------\n");
	printf("询价success\n");
	printf("-----------------------------\n");
	return ;
}

void CTraderSpi::OnRtnQuote(CUstpFtdcRtnQuoteField* pRtnQuote)
{
	printf("-----------------------------\n");
	printf(" received 报价 response \n");
	Show(pRtnQuote);
	printf("-----------------------------\n");
	return ;
}

void CTraderSpi::OnErrRtnQuoteInsert(CUstpFtdcInputQuoteField* pInputQuote, CUstpFtdcRspInfoField* pRspInfo)
{
	if (pRspInfo!=NULL&&pRspInfo->ErrorID!=0)
	{
		printf("-----------------------------\n");
		printf("报价录入 error  response failed error reason：%s\n",pRspInfo->ErrorMsg);
		printf("-----------------------------\n");
		return;
	}
	if( pInputQuote==NULL)
	{
		printf("no data\n");
		return;
	}
	printf("-----------------------------\n");
	printf("报价录入 error  response \n");
	printf("-----------------------------\n");
	return ;
}
void CTraderSpi::Show(CUstpFtdcRtnQuoteField* pQuote)
{
	printf("-----------------------------\n");
	printf("ExchangeID=[%s]\n",pQuote->ExchangeID);
	printf("InvestorID=[%s]\n",pQuote->InvestorID);
	printf("UserID=[%s]\n",pQuote->UserID);
	printf("InstrumentID=[%s]\n",pQuote->InstrumentID);
	printf("QuoteSysID=[%s]\n",pQuote->QuoteSysID);
	printf("用户本地报价编号=[%s]\n",pQuote->UserQuoteLocalID);
	printf("本地报价编号=[%s]\n",pQuote->QuoteLocalID);

	printf("买方买入数量=[%d]\n",pQuote->BidVolume);
	printf("买方开平标志=[%c]\n",pQuote->BidOffsetFlag);
	printf("买方投机套保标志=[%c]\n",pQuote->BidHedgeFlag);
	printf("买方买入价格=[%lf]\n",pQuote->BidPrice);
	printf("卖方卖出数量=[%d]\n",pQuote->AskVolume);
	printf("卖方开平标志=[%c]\n",pQuote->AskOffsetFlag);
	printf("卖方投机套保标志=[%c]\n",pQuote->AskHedgeFlag);
	printf("卖方卖出价格=[%lf]\n",pQuote->AskPrice);

	printf("拆分出来的买方用户OrderLocalID=[%s]\n",pQuote->BidUserOrderLocalID);
	printf("拆分出来的卖方用户OrderLocalID=[%s]\n",pQuote->AskUserOrderLocalID);
	printf("买方OrderSysID=[%s]\n",pQuote->BidOrderSysID);
	printf("卖方OrderSysID=[%s]\n",pQuote->AskOrderSysID);

	printf("报价单状态=[%s]\n",pQuote->QuoteStatus);


	printf("插入时间=[%s]\n",pQuote->InsertTime);
	printf("撤销时间=[%s]\n",pQuote->CancelTime);
	printf("成交时间=[%s]\n",pQuote->TradeTime);

	printf("-----------------------------\n");
	return ;
}
