
#ifndef __ESUNNY_QUOTEAPISTRUCT_SECTION__
#define __ESUNNY_QUOTEAPISTRUCT_SECTION__

#include "EsunnyQuoteApiDataType.h"

namespace esunny_quote_api {
//服务器地址对象
struct ServerIpPort {
  char ip[20];
  int port;
};

//错误信息对象
struct ESunnyQuoteErrorInfo {
  //错误id
  TEsunnyQuoteErrorCode errorcode;
  //错误信息
  TEsunnyQuoteErrorMsg errormsg;
};

//日期时间对象（查询K线使用）
struct ESunnyQuoteDateTime {
  //日期
  TEsunnyQuoteDate quoteDay;
  //时间
  TEsunnyQuoteTime quoteTime;
};

//交易日对象
struct ESunnyTradingDayField {
  //交易所代码
  TEsunnyQuoteExchange exchangeID;
  //交易日列表
  TEsunnyTradingDayField tradingday;
  // 类型：0-交易日列表，1-当前交易日，2-上一交易日，3-下一交易日
  int type = 3;
};

//交易时间对象
struct ESunnyQuoteTradeTimeField {
  //交易所
  TEsunnyQuoteExchange exchangeid;
  //品种
  TEsunnyQuoteProductInfo productid;
  //交易日
  TEsunnyQuoteDate tradeday;
  //开始时间
  TEsunnyQuoteTime starttime;
  //结束时间
  TEsunnyQuoteTime stoptime;
};

// UDP信息对象
struct ESunnyUdpInfoField {
  //通道号，如：9382
  char channelno[20];
  //通道名，如：9382-a
  char channelname[50];
  //交易所，如：NYMEX
  EXCHANGE_TYPE_ID exchange;
  //品种集合，如：CL|NG
  char products[8000];
  char sUdpAdr_a[32];
  char sUdpAdr_b[32];
};

//交易所项目对象
struct ESunnyExchangeItemField {
  //交易所ID，可作为枚举参数
  int id;
  //交易所代码
  TEsunnyQuoteExchange exchangeid;
};

//订阅合约对象
struct ESunnyQuoteSpecificInstrumentField {
  //合约代码
  TEsunnyQuoteInstrumentID InstrumentID;
  //交易所代码
  EXCHANGE_TYPE_ID ExchangeID;
};

// K线对象
struct ESunnyQuoteKLine {
  //合约代码
  TEsunnyQuoteInstrumentID instrumentID;
  //交易所代码
  TEsunnyQuoteExchange exchangeID;
  // K行情类型
  KLINE_TYPE_ID klineType;
  //行情日期
  TEsunnyQuoteDate quoteDay;
  //行情时间
  TEsunnyQuoteTime quoteTime;
  //最高价
  TEsunnyQuotePrice highestPrice;
  //最低价
  TEsunnyQuotePrice lowestPrice;
  //开盘价
  TEsunnyQuotePrice openPrice;
  //收盘价
  TEsunnyQuotePrice closePrice;
  //成交金额
  TEsunnyQuoteMoney turnover;
  //成交量
  TEsunnyQuoteVolume volume;
  //持仓量
  TEsunnyQuoteVolume openinterest;
  ///交易日
  TEsunnyQuoteDate tradingday;
  ///日均价
  TEsunnyQuotePrice averageprice;
  ///分钟内均价
  TEsunnyQuotePrice averageprice_min;
};

//合约对象
struct ESunnyInstrumentField {
  //交易所代码
  TEsunnyQuoteExchange exchangeid;
  //合约代码
  TEsunnyQuoteInstrumentID instrumentid;
  //合约名称
  TEsunnyQuoteInstrumentName instrumentname;
  //合约在交易所的代码
  TEsunnyQuoteInstrumentID exchangeinstid;
  //品种代码
  TEsunnyQuoteProductInfo productid;
  //品种类别
  TEsunnyQuoteProductClass productclass;
  //基础商品代码
  TEsunnyQuoteString underlyinginstrid;
  //产品组代码
  TEsunnyQuoteString productgroupid;
  //当前是否交易
  TEsunnyQuoteBool istrading;
  //持仓类型
  TEsunnyQuotePositionType positiontype;
  //期权类型
  TEsunnyQuoteOptionsType optionstype;
  //执行价
  TEsunnyQuotePrice strikeprice;
  //最小变动价位
  TEsunnyQuotePrice pricetick;
  //合约乘数
  TEsunnyQuoteVolumeMultiple volumemultiple;
  //合约基础商品乘数
  TEsunnyQuoteUnderlyingMultipleType underlyingmultiple;
  //市价单最大下单量
  TEsunnyQuoteVolumeType maxmarketordervolume;
  //市价单最小下单量
  TEsunnyQuoteVolumeType minmarketordervolume;
  //限价单最小下单量
  TEsunnyQuoteVolumeType maxlimitordervolume;
  //限价单最小下单量
  TEsunnyQuoteVolumeType minlimitordervolume;
  //交割年
  TEsunnyQuoteYear deliveryyear;
  //交割月
  TEsunnyQuoteMonth deliverymonth;
  //创建日
  TEsunnyQuoteDate createdate;
  //上市日
  TEsunnyQuoteDate opendate;
  //到期日
  TEsunnyQuoteDate expiredate;
  //开始交割日
  TEsunnyQuoteDate startdelivdate;
  //最后交割日
  TEsunnyQuoteDate enddelivdate;
  //显示因子
  TEsunnyQuotePrice displayfactor;
  //产品组代码
  TEsunnyQuoteRemark tradetime;
  //涨停价
  TEsunnyQuotePrice upperlimitprice;
  //跌停价
  TEsunnyQuotePrice lowerlimitprice;
};

//行情快照对象
struct ESunnyQuoteMarketField {
  // 合约序号
  int rptseq;
  // 包号
  TEsunnyQuoteMsgSeqNum msgseqnum;

  //合约代码
  TEsunnyQuoteInstrumentID instrumentID;
  //交易所代码
  TEsunnyQuoteExchange exchangeID;
  //交易所时间(YYYYMMDD-HH:MM:SS.123456789)
  TEsunnyQuoteTime exchangeupdateTime;
  //交易日(YYYYMMDD)
  TEsunnyQuoteDate tradingDay;
  //最后修改时间(HH:MM:SS)
  TEsunnyQuoteTime updateTime;
  //最后修改时间（微秒:123456）
  TESunnyFtdcSubTimeType updateTimeEx;
  //最新价
  TEsunnyQuotePrice lastPrice;
  //当日均价
  TEsunnyQuotePrice averagePrice;
  //成交数量
  TEsunnyQuoteVolume volume;
  //现手
  TEsunnyQuoteVolume newvolume;
  //成交金额
  TEsunnyQuoteMoney turnover;
  //今收盘
  TEsunnyQuotePrice closePrice;
  //昨收盘
  TEsunnyQuotePrice preClosePrice;
  //今开盘
  TEsunnyQuotePrice openPrice;
  //最低价
  TEsunnyQuotePrice lowestPrice;
  //最高价
  TEsunnyQuotePrice highestPrice;
  //跌停板价
  TEsunnyQuotePrice lowerLimitPrice;
  //涨停板价
  TEsunnyQuotePrice upperLimitPrice;
  //上次结算价
  TEsunnyQuotePrice preSettlementPrice;
  //本次结算价
  TEsunnyQuotePrice settlementPrice;
  //昨持仓量
  TEsunnyQuoteVolume preOpenInterest;
  //持仓量
  TEsunnyQuoteVolume openInterest;
  //昨虚实度
  TEsunnyQuoteRate preDelta;
  //今虚实度
  TEsunnyQuoteRate currDelta;

  //十档行情
  // 行情档位
  int price_level;
  TEsunnyQuotePrice bidprice[10];
  TEsunnyQuotePrice askprice[10];
  TEsunnyQuoteVolume bidvolume[10];
  TEsunnyQuoteVolume askvolume[10];

  // 隐含行情
  TEsunnyQuotePrice impliedbidprice[2];
  TEsunnyQuotePrice impliedaskprice[2];
  TEsunnyQuoteVolume impliedbidvolume[2];
  TEsunnyQuoteVolume impliedaskvolume[2];

  // 隐含标记，第几档包含隐含
  TEsunnyQuoteImpliedTag impliedBidPriceTag[2];
  TEsunnyQuoteImpliedTag impliedBidVolumeTag[2];
  TEsunnyQuoteImpliedTag impliedAskPriceTag[2];
  TEsunnyQuoteImpliedTag impliedAskVolumeTag[2];
};

//逐笔行情对象
struct ESunnyQuoteTickField {
  //合约代码
  TEsunnyQuoteInstrumentID instrumentID;
  //交易所代码
  TEsunnyQuoteExchange exchangeID;
  //交易所时间
  TEsunnyQuoteTime exchangeupdatetime;
  //最后修改时间
  TEsunnyQuoteTime updateTime;
  //最后修改时间（微秒）
  TESunnyFtdcSubTimeType updateTimeEx;
  //行情增量类型
  TEsunnyIncrementalQuoteType mdType;
  // Type of Market Data update action
  TEsunnyIncrementalQuoteAction mdAction;
  //手数
  TEsunnyQuoteVolume volume;
  //价格
  TEsunnyQuotePrice price;
  //价格档位
  TEsunnyQuoteVolume pricelevel;
  // MsgSeqNum
  TEsunnyQuoteMsgSeqNum msgseqnum;

  int rptseq;
  int matcheventindicator;
};

//登录请求
struct ESunnyQuoteLogin {
  //账号
  TEsunnyQuoteID userid;
  //账号密码
  TEsunnyQuotePassWord password;
  //客户端IP
  TEsunnyQuoteAddress clientip;
  //客户端版本
  TEsunnyQuoteVersion clientversion;
  //说明
  TEsunnyQuoteRemark remark;
  //终端类型
  char terminaltype[128];
  //产品名称
  char productname[128];
};

//修改密码
struct ESunnyChangePassword {
  //账号
  TEsunnyQuoteID userid;
  //旧密码
  TEsunnyQuotePassWord oldpassword;
  //新密码
  TEsunnyQuotePassWord newpassword;
};

//登录应答
struct ESunnyQuoteRspUserLoginField {
  //行情服务器信息
  TEsunnyQuoteSvrInfo QuoteSvrInfo;
  //登录成功时间
  TEsunnyQuoteTime LoginTime;
  //用户代码
  TEsunnyQuoteID UserID;
  //前置编号
  TEsunnyQuoteFrontIDType FrontID;
  //会话编号
  TEsunnyQuoteSessionIDType SessionID;
};

//查询合约请求，不填则不过滤
struct ESunnyQuoteReqQryInstrument {
  //合约代码
  TEsunnyQuoteInstrumentID instrumentID;
  //交易所代码
  EXCHANGE_TYPE_ID exchangeID;
  //品种代码
  TEsunnyQuoteProductInfo productID;
  //过滤主力：0--不过滤， 2--指定交易所， 4--内盘主力， 8--外盘主力
  TEsunnyQuoteFiltertype filtertype;
  //品种类别
  TEsunnyQuoteProductClass productclass;
  //期权类型
  TEsunnyQuoteOptionsType optionstype;
  //交易日（选填）
  TEsunnyQuoteDate tradeday;
};

//查询快照请求
struct ESunnyQuoteReqQrySnapshot {
  //合约代码（必填）
  TEsunnyQuoteInstrumentID instrumentID;
  //交易所代码（必填）
  EXCHANGE_TYPE_ID exchangeID;
  //查询交易日（必填）
  TEsunnyQuoteDate TradeDay;
  //开始时间 20191210-10:00:00，不填默认从当前交易日开始
  TEsunnyQuoteTime StartDatetime;
  //结束时间 20191210-20:00:00，不填默认到当前交易日结束
  TEsunnyQuoteTime EndDatetime;
};

//查询行情K线
struct ESunnyQuoteReqQryKLine {
  //合约代码
  TEsunnyQuoteInstrumentID instrumentID;
  //交易所代码
  EXCHANGE_TYPE_ID exchangeID;
  //行情时间
  ESunnyQuoteDateTime quoteTime;
  // K线数量（向前数量）
  TEsunnyQuoteVolumeType klineCount;
  // K线类型
  KLINE_TYPE_ID klineType;
};

//查询逐笔请求
struct ESunnyQuoteReqQryTick {
  //合约代码（必填）
  TEsunnyQuoteInstrumentID instrumentID;
  //交易所代码（必填）
  EXCHANGE_TYPE_ID exchangeID;
  //查询交易日（必填）
  TEsunnyQuoteDate TradeDay;
  //开始时间 20191210-10:00:00，不填默认从当前交易日开始
  TEsunnyQuoteTime StartDatetime;
  //结束时间 20191210-20:00:00，不填默认到当前交易日结束
  TEsunnyQuoteTime EndDatetime;
};

//查询行情快照截面请求
struct ESunnyQuoteReqQrySnapshotSection {
  //合约代码
  TEsunnyQuoteInstrumentID instrumentID;
  //交易所代码
  EXCHANGE_TYPE_ID exchangeID;
};

//查询交易日请求
struct ESunnyQuoteReqQryTradingDay {
  //交易所代码
  EXCHANGE_TYPE_ID exchangeID;
  // 类型：0-交易日列表，1-当前交易日，2-上一交易日，3-下一交易日
  int type = 3;
};

//查询交易时间请求
struct EsunnyQuoteReqQryTradetime {
  //交易所代码
  EXCHANGE_TYPE_ID exchangeID;
  //合约代码
  TEsunnyQuoteProductInfo productid;
  //交易日
  TEsunnyQuoteDate tradeDay;
};

//查询交易日K-min线请求
struct EsunnyQuoteReqQryTradedayKline {
  //交易所代码
  EXCHANGE_TYPE_ID exchangeID;
  //合约代码
  TEsunnyQuoteInstrumentID instrumentID;
  //交易日
  TEsunnyQuoteDate tradeDay;
};

}  // namespace esunny_quote_api
#endif