/////////////////////////////////////////////////////////////////////////
///@system 风控前置系统
///@company CFFEX
///@file USTPFtdcUserApiDataType.h
///@brief 定义了客户端接口使用的业务数据类型
///@history 
///
/////////////////////////////////////////////////////////////////////////

#ifndef USTP_FTDCDATATYPE_H
#define USTP_FTDCDATATYPE_H

enum USTP_TE_RESUME_TYPE
{
	USTP_TERT_RESTART = 0,
	USTP_TERT_RESUME,
	USTP_TERT_QUICK
};

const int USTP_TSS_DIALOG = 1;		//对话流
const int USTP_TSS_PRIVATE = 2;		//客户私有流
const int USTP_TSS_PUBLIC = 3;		//公共流
const int USTP_TSS_QUERY = 4;		//查询
const int USTP_TSS_USER = 5;		//用户私有流
const int USTP_TSS_QUOTE = 6;		//询价流

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpPriceTickType是一个最小变动价位类型
/////////////////////////////////////////////////////////////////////////
typedef double TUstpFtdcPriceTickType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpPriceType是一个价格类型
/////////////////////////////////////////////////////////////////////////
typedef double TUstpFtdcPriceType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpRatioType是一个比率类型
/////////////////////////////////////////////////////////////////////////
typedef double TUstpFtdcRatioType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpMoneyType是一个资金类型
/////////////////////////////////////////////////////////////////////////
typedef double TUstpFtdcMoneyType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpLargeVolumeType是一个大额数量类型
/////////////////////////////////////////////////////////////////////////
typedef double TUstpFtdcLargeVolumeType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpSequenceNoType是一个序列号类型
/////////////////////////////////////////////////////////////////////////
typedef int TUstpFtdcSequenceNoType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpMillisecType是一个最后修改毫秒类型
/////////////////////////////////////////////////////////////////////////
typedef int TUstpFtdcMillisecType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpVolumeType是一个数量类型
/////////////////////////////////////////////////////////////////////////
typedef int TUstpFtdcVolumeType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpUnderlyingMultipleType是一个合约乘数类型
/////////////////////////////////////////////////////////////////////////
typedef int TUstpFtdcUnderlyingMultipleType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpVolumeMultipleType是一个数量乘数类型
/////////////////////////////////////////////////////////////////////////
typedef int TUstpFtdcVolumeMultipleType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpSequenceSeriesType是一个序列系列号类型
/////////////////////////////////////////////////////////////////////////
typedef int TUstpFtdcSequenceSeriesType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpErrorIDType是一个错误代码类型
/////////////////////////////////////////////////////////////////////////
typedef int TUstpFtdcErrorIDType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpDataCenterIDType是一个数据中心代码类型
/////////////////////////////////////////////////////////////////////////
typedef int TUstpFtdcDataCenterIDType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpSettlementIDType是一个结算编号类型
/////////////////////////////////////////////////////////////////////////
typedef int TUstpFtdcSettlementIDType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpMonthType是一个月份类型
/////////////////////////////////////////////////////////////////////////
typedef int TUstpFtdcMonthType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpBoolType是一个布尔型类型
/////////////////////////////////////////////////////////////////////////
typedef int TUstpFtdcBoolType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpYearType是一个年类型
/////////////////////////////////////////////////////////////////////////
typedef int TUstpFtdcYearType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpMemTableNameType是一个内存表名类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcMemTableNameType[61];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpOrderSysIDType是一个报单编号类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcOrderSysIDType[31];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpTradeIDType是一个成交编号类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcTradeIDType[21];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpUserIDType是一个用户代码类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcUserIDType[16];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpParticipantIDType是一个会员编号类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcParticipantIDType[11];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpIPAddressType是一个IP地址类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcIPAddressType[21];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpMacAddressType是一个Mac地址类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcMacAddressType[21];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpInstrumentNameType是一个合约名称类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcInstrumentNameType[21];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpInstrumentIDType是一个合约编号类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcInstrumentIDType[31];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpExchangeNameType是一个交易所名称类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcExchangeNameType[31];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpExchangeIDType是一个交易所代码类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcExchangeIDType[11];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpDateType是一个日期类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcDateType[9];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpTimeType是一个时间类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcTimeType[9];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpClientIDType是一个客户编码类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcClientIDType[19];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpAccountIDType是一个资金帐号类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcAccountIDType[13];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpSeatIDType是一个席位号类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcSeatIDType[13];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpProductNameType是一个品种名称类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcProductNameType[41];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpUserOrderLocalIDType是一个用户本地报单号类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcUserOrderLocalIDType[21];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpOrderLocalIDType是一个本地报单编号类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcOrderLocalIDType[13];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpInvestorIDType是一个投资者编号类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcInvestorIDType[19];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpUserNameType是一个用户编码类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcUserNameType[31];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpPasswordType是一个密码类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcPasswordType[41];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpProductInfoType是一个产品信息类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcProductInfoType[41];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpProtocolInfoType是一个协议信息类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcProtocolInfoType[41];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpBusinessUnitType是一个业务单元类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcBusinessUnitType[21];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpTradingSystemNameType是一个交易系统名称类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcTradingSystemNameType[61];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpBrokerIDType是一个经纪公司代码类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcBrokerIDType[11];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpCustomType是一个用户自定义域类型类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcCustomType[65];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpTradingDayType是一个交易日类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcTradingDayType[9];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpDepartmentType是一个营业部类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcDepartmentType[41];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpGrantFuncSetType是一个授权功能号类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcGrantFuncSetType[5];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpProductIDType是一个品种编号类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcProductIDType[13];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpAccountSeqNoType是一个资金流水号类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcAccountSeqNoType[21];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpSettlementGroupIDType是一个结算组代码类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcSettlementGroupIDType[9];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpErrorMsgType是一个错误信息类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcErrorMsgType[81];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpVolumeConditionType是一个成交量类型类型
/////////////////////////////////////////////////////////////////////////
///任何数量
#define USTP_FTDC_VC_AV '1'
///最小数量
#define USTP_FTDC_VC_MV '2'
///全部数量
#define USTP_FTDC_VC_CV '3'

typedef char TUstpFtdcVolumeConditionType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpForceCloseReasonType是一个强平原因类型
/////////////////////////////////////////////////////////////////////////
///非强平
#define USTP_FTDC_FCR_NotForceClose '0'
///资金不足
#define USTP_FTDC_FCR_LackDeposit '1'
///客户超仓
#define USTP_FTDC_FCR_ClientOverPositionLimit '2'
///会员超仓
#define USTP_FTDC_FCR_MemberOverPositionLimit '3'
///持仓非整数倍
#define USTP_FTDC_FCR_NotMultiple '4'

typedef char TUstpFtdcForceCloseReasonType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpInstrumentStatusType是一个合约交易状态类型
/////////////////////////////////////////////////////////////////////////
///开盘前
#define USTP_FTDC_IS_BeforeTrading '0'
///非交易
#define USTP_FTDC_IS_NoTrading '1'
///连续交易
#define USTP_FTDC_IS_Continous '2'
///集合竞价报单
#define USTP_FTDC_IS_AuctionOrdering '3'
///集合竞价价格平衡
#define USTP_FTDC_IS_AuctionBalance '4'
///集合竞价撮合
#define USTP_FTDC_IS_AuctionMatch '5'
///收盘
#define USTP_FTDC_IS_Closed '6'

typedef char TUstpFtdcInstrumentStatusType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpOffsetFlagType是一个开平标志类型
/////////////////////////////////////////////////////////////////////////
///开仓
#define USTP_FTDC_OF_Open '0'
///平仓
#define USTP_FTDC_OF_Close '1'
///强平
#define USTP_FTDC_OF_ForceClose '2'
///平今
#define USTP_FTDC_OF_CloseToday '3'
///平昨
#define USTP_FTDC_OF_CloseYesterday '4'

typedef char TUstpFtdcOffsetFlagType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpOrderPriceTypeType是一个报单价格条件类型
/////////////////////////////////////////////////////////////////////////
///任意价
#define USTP_FTDC_OPT_AnyPrice '1'
///限价
#define USTP_FTDC_OPT_LimitPrice '2'

typedef char TUstpFtdcOrderPriceTypeType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpOrderStatusType是一个报单状态类型
/////////////////////////////////////////////////////////////////////////
///全部成交
#define USTP_FTDC_OS_AllTraded '0'
///部分成交还在队列中
#define USTP_FTDC_OS_PartTradedQueueing '1'
///部分成交不在队列中
#define USTP_FTDC_OS_PartTradedNotQueueing '2'
///未成交还在队列中
#define USTP_FTDC_OS_NoTradeQueueing '3'
///未成交不在队列中
#define USTP_FTDC_OS_NoTradeNotQueueing '4'
///撤单
#define USTP_FTDC_OS_Canceled '5'
///订单已报入交易所未应答
#define USTP_FTDC_OS_AcceptedNoReply '6'

typedef char TUstpFtdcOrderStatusType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpUserTypeType是一个用户类型类型
/////////////////////////////////////////////////////////////////////////
///自然人
#define USTP_FTDC_UT_Person '1'
///理财产品
#define USTP_FTDC_UT_Product '2'
///期货公司管理员
#define USTP_FTDC_UT_Manager '3'
///席位
#define USTP_FTDC_UT_Seat '4'

typedef char TUstpFtdcUserTypeType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpTradingRightType是一个交易权限类型
/////////////////////////////////////////////////////////////////////////
///可以交易
#define USTP_FTDC_TR_Allow '0'
///只能平仓
#define USTP_FTDC_TR_CloseOnly '1'
///不能交易
#define USTP_FTDC_TR_Forbidden '2'

typedef char TUstpFtdcTradingRightType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpTimeConditionType是一个有效期类型类型
/////////////////////////////////////////////////////////////////////////
///立即完成，否则撤销
#define USTP_FTDC_TC_IOC '1'
///本节有效
#define USTP_FTDC_TC_GFS '2'
///当日有效
#define USTP_FTDC_TC_GFD '3'
///指定日期前有效
#define USTP_FTDC_TC_GTD '4'
///撤销前有效
#define USTP_FTDC_TC_GTC '5'
///集合竞价有效
#define USTP_FTDC_TC_GFA '6'

typedef char TUstpFtdcTimeConditionType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpOrderSourceType是一个报单来源类型
/////////////////////////////////////////////////////////////////////////
///来自参与者
#define USTP_FTDC_OS_Participant '0'
///来自管理员
#define USTP_FTDC_OS_Administrator '1'
///报价单拆分出来的买单或卖单
#define USTP_FTDC_OS_QuoteSplit '2'

typedef char TUstpFtdcOrderSourceType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpDirectionType是一个买卖方向类型
/////////////////////////////////////////////////////////////////////////
///买
#define USTP_FTDC_D_Buy '0'
///卖
#define USTP_FTDC_D_Sell '1'

typedef char TUstpFtdcDirectionType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpCurrencyType是一个币种类型
/////////////////////////////////////////////////////////////////////////
///人民币
#define USTP_FTDC_C_RMB '1'
///美元
#define USTP_FTDC_C_UDOLLAR '2'

typedef char TUstpFtdcCurrencyType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpAccountDirectionType是一个出入金方向类型
/////////////////////////////////////////////////////////////////////////
///入金
#define USTP_FTDC_AD_In '1'
///出金
#define USTP_FTDC_AD_Out '2'

typedef char TUstpFtdcAccountDirectionType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpHedgeFlagType是一个投机套保标志类型
/////////////////////////////////////////////////////////////////////////
///投机
#define USTP_FTDC_CHF_Speculation '1'
///套利
#define USTP_FTDC_CHF_Arbitrage '2'
///套保
#define USTP_FTDC_CHF_Hedge '3'

typedef char TUstpFtdcHedgeFlagType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpActionFlagType是一个操作标志类型
/////////////////////////////////////////////////////////////////////////
///删除
#define USTP_FTDC_AF_Delete '0'
///挂起
#define USTP_FTDC_AF_Suspend '1'
///激活
#define USTP_FTDC_AF_Active '2'
///修改
#define USTP_FTDC_AF_Modify '3'

typedef char TUstpFtdcActionFlagType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpPositionTypeType是一个持仓类型类型
/////////////////////////////////////////////////////////////////////////
///净持仓
#define USTP_FTDC_PT_Net '1'
///综合持仓
#define USTP_FTDC_PT_Gross '2'

typedef char TUstpFtdcPositionTypeType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpOptionsTypeType是一个期权类型类型
/////////////////////////////////////////////////////////////////////////
///非期权
#define USTP_FTDC_OT_NotOptions '0'
///看涨
#define USTP_FTDC_OT_CallOptions '1'
///看跌
#define USTP_FTDC_OT_PutOptions '2'

typedef char TUstpFtdcOptionsTypeType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpIsActiveType是一个是否活跃类型
/////////////////////////////////////////////////////////////////////////
///不活跃
#define USTP_FTDC_UIA_NoActive '0'
///活跃
#define USTP_FTDC_UIA_Active '1'

typedef char TUstpFtdcIsActiveType;

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpCurrencyIDType是一个币种代码类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcCurrencyIDType[4];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpQuoteSysIDType是一个报价编号类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcQuoteSysIDType[31];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpUserQuoteLocalIDType是一个用户本地报价编号类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcUserQuoteLocalIDType[21];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpQuoteLocalIDType是一个飞马本地报价编号类型
/////////////////////////////////////////////////////////////////////////
typedef char TUstpFtdcQuoteLocalIDType[13];

/////////////////////////////////////////////////////////////////////////
///TFtdcUstpQuoteStatusType是一个报价单状态类型类型
/////////////////////////////////////////////////////////////////////////
///在飞马中还未进入交易系统
#define USTP_FTDC_QS_Inited_InFEMAS '0'
///已经报入交易系统中
#define USTP_FTDC_QS_Accepted_InTradingSystem '1'
///已经撤掉单腿
#define USTP_FTDC_QS_Canceled_SingleLeg '2'
///已经全部撤掉
#define USTP_FTDC_QS_Canceled_All '3'
///已经有单腿成交
#define USTP_FTDC_QS_Traded_SingleLeg '4'
///已经全部成交
#define USTP_FTDC_QS_Traded_All '5'
///错误的撤消报价请求
#define USTP_FTDC_QS_Error_QuoteAction '6'

typedef char TUstpFtdcQuoteStatusType;

#endif
