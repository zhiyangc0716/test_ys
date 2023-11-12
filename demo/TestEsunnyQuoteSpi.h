#ifndef __TEST_ESUNNY_QUOTE_SPI_SECTION__
#define __TEST_ESUNNY_QUOTE_SPI_SECTION__

#include <fstream>
#include <iostream>
#include <map>
#include "EsunnyQuoteApi.h"
#include "utility.h"

using namespace esunny_quote_api;

class CTestEsunnyQuoteSpi : public CEsunnyQuoteSpi {
 public:
  CTestEsunnyQuoteSpi();
  virtual ~CTestEsunnyQuoteSpi();

  void init(CEsunnyQuoteApi* pEQapi);

  void readIni();

 public:
  //当客户端与服务器建立连接时（还未登录前），该方法被调用。
  //通常在这里进行登录请求
  virtual void OnFrontConnected();

  //当客户端与服务器连接断开时，该方法被调用。
  //当发生这个情况后，API会自动重新连接。
  //@param  nReason 错误原因
  //        0x1001 网络读失败
  //        0x1002 网络写失败
  //        0x2001 接收心跳超时
  //        0x2002 发送心跳失败
  //        0x2003 收到错误报文
  virtual void OnFrontDisconnected(int nReason);

  //登录应答
  //@param  pRspUserLogin 应答对象
  //@param  errorInfo 错误信息对象
  //@param requestID 请求ID
  //@param  bIsLast 是否是最后一个应答
  virtual void OnRspQuoteLogin(ESunnyQuoteRspUserLoginField* pRspUserLogin,
                               ESunnyQuoteErrorInfo* errorInfo, int requestID,
                               bool bIsLast);

  //登出请求应答
  //@param  errorInfo 错误信息对象
  //@param requestID 请求ID
  virtual void OnRspQuoteLogout(ESunnyQuoteErrorInfo* errorInfo, int requestID);

  //修改密码应答
  //@param  errorInfo 错误信息对象
  //@param requestID 请求ID
  virtual void OnRspChangePassword(ESunnyQuoteErrorInfo* errorInfo,
                                   int requestID);

  //订阅行情响应
  //@param  pSpecificInstrument 应答对象
  //@param  errorInfo 错误信息对象
  //@param requestID 请求ID
  //@param  bIsLast 是否是最后一个应答
  virtual void OnRspSubscribeMarketData(
      ESunnyQuoteSpecificInstrumentField* pSpecificInstrument,
      ESunnyQuoteErrorInfo* errorInfo, int nRequestID, bool bIsLast);

  //取消订阅行情响应
  //@param  pSpecificInstrument 应答对象
  //@param  errorInfo 错误信息对象
  //@param requestID 请求ID
  //@param  bIsLast 是否是最后一个应答
  virtual void OnRspUnSubscribeMarketData(
      ESunnyQuoteSpecificInstrumentField* pSpecificInstrument,
      ESunnyQuoteErrorInfo* errorInfo, int nRequestID, bool bIsLast);

  //订阅K线行情响应
  //@param  pSpecificInstrument 应答对象
  //@param  errorInfo 错误信息对象
  //@param requestID 请求ID
  //@param  bIsLast 是否是最后一个应答
  virtual void OnRspSubscribeKLineData(
      ESunnyQuoteSpecificInstrumentField* pSpecificInstrument,
      ESunnyQuoteErrorInfo* errorInfo, int nRequestID, bool bIsLast);

  //取消订阅K线行情响应
  //@param  pSpecificInstrument 应答对象
  //@param  errorInfo 错误信息对象
  //@param requestID 请求ID
  //@param  bIsLast 是否是最后一个应答
  virtual void OnRspUnSubscribeKLineData(
      ESunnyQuoteSpecificInstrumentField* pSpecificInstrument,
      ESunnyQuoteErrorInfo* errorInfo, int nRequestID, bool bIsLast);

  //查询合约应答
  //@param  pData 应答对象
  //@param  errorInfo 错误信息对象
  //@param requestID 请求ID
  //@param  bIsLast 是否是最后一个应答
  virtual void OnRspQryInstrument(ESunnyInstrumentField* pData,
                                  ESunnyQuoteErrorInfo* errorInfo,
                                  int requestID, bool isLast);

  //查询历史快照行情应答
  //@param  pData 应答对象
  //@param  errorInfo 错误信息对象
  //@param requestID 请求ID
  //@param  bIsLast 是否是最后一个应答
  virtual void OnRspQryHisSnapshotQuote(ESunnyQuoteMarketField* pData,
                                        ESunnyQuoteErrorInfo* errorInfo,
                                        int requestID, bool isLast);

  //查询行情K线应答
  //@param  pData 应答对象
  //@param  errorInfo 错误信息对象
  //@param requestID 请求ID
  //@param  bIsLast 是否是最后一个应答
  virtual void OnRspQryKLineQuote(ESunnyQuoteKLine* pData,
                                  ESunnyQuoteErrorInfo* errorInfo,
                                  int requestID, bool isLast);

  //推送快照行情变动，对应订阅快照 SubscribeMarketData
  //此快照推送包括：普通切片快照和逐笔快照
  //@param  pData 应答对象
  virtual void OnRtnDepthMarketData(ESunnyQuoteMarketField* pData);

  //推送K线，对应订阅K线 SubscribeKLineData
  //@param  pData 应答对象
  virtual void OnRtnKLineQuoteData(ESunnyQuoteKLine* pData);

  //推送UDP信息，如果init的参数servertype=QST_UDPTICK，则登录成功后会收到一次推送
  //@param  data UDP信息（SubscribeUdpInfo用到该数据）
  //@param  bIsLast 是否是最后一个信息
  virtual void OnRtnUdpInfoData(const ESunnyUdpInfoField& data, bool isLast);

  //推送客户端退出消息，服务器主动踢出客户端
  //@param  errorInfo 错误信息对象
  virtual void OnRtnClientExit(ESunnyQuoteErrorInfo* errorInfo);

  //推送交易所列表消息，登陆后推送
  //@param  data 交易所信息（后台支持的交易所）
  //@param  bIsLast 是否是最后一个信息
  virtual void OnRtnExchangeList(ESunnyExchangeItemField* pData, bool isLast);

  //////////////////////////////////////////////////////////////////////////
  /// 以下为扩展功能，如果不需要可不关注
  //////////////////////////////////////////////////////////////////////////
  //订阅逐笔行情响应
  //@param  pSpecificInstrument 应答对象
  //@param  errorInfo 错误信息对象
  //@param requestID 请求ID
  //@param  bIsLast 是否是最后一个应答
  virtual void OnRspSubscribeTickData(
      ESunnyQuoteSpecificInstrumentField* pSpecificInstrument,
      ESunnyQuoteErrorInfo* errorInfo, int nRequestID, bool bIsLast) {};

  //取消订阅逐笔行情响应
  //@param  pSpecificInstrument 应答对象
  //@param  errorInfo 错误信息对象
  //@param requestID 请求ID
  //@param  bIsLast 是否是最后一个应答
  virtual void OnRspUnSubscribeTickData(
      ESunnyQuoteSpecificInstrumentField* pSpecificInstrument,
      ESunnyQuoteErrorInfo* errorInfo, int nRequestID, bool bIsLast) {};

  //查询历史逐笔应答
  //@param  pData 应答对象
  //@param  errorInfo 错误信息对象
  //@param requestID 请求ID
  //@param  bIsLast 是否是最后一个应答
  virtual void OnRspQryHisTickQuote(ESunnyQuoteTickField* pData,
                                    ESunnyQuoteErrorInfo* errorInfo,
                                    int requestID, bool isLast);

  //推送原始快照（该推送由行情服务器决定），对应订阅快照
  //@param  pData 应答对象
  virtual void OnRtnOriginalSnap(ESunnyQuoteMarketField* pData) {};

  //推送逐笔变动（该推送由行情服务器决定），对应订阅逐笔 SubscribeTickData
  //@param  pData 应答对象
  virtual void OnRtnTickQuoteData(ESunnyQuoteTickField* pData) {};

  //查询行情快照截面应答
  //@param  pData 应答对象
  //@param  errorInfo 错误信息对象
  //@param requestID 请求ID
  //@param  bIsLast 是否是最后一个应答
  virtual void OnRspQrySnapshotSection(ESunnyQuoteMarketField* pData,
                                       ESunnyQuoteErrorInfo* errorInfo,
                                       int requestID, bool isLast);

  //查询交易日应答
  //@param  pData 应答对象
  //@param  errorInfo 错误信息对象
  //@param requestID 请求ID
  //@param  bIsLast 是否是最后一个应答
  virtual void OnRspQryTradingDay(ESunnyTradingDayField* pData,
                                  ESunnyQuoteErrorInfo* errorInfo,
                                  int requestID, bool isLast);

  //查询交易时间应答
  //@param  pData 应答对象
  //@param  errorInfo 错误信息对象
  //@param requestID 请求ID
  //@param  bIsLast 是否是最后一个应答
  virtual void OnRspQryTradeTime(ESunnyQuoteTradeTimeField* pData,
                                 ESunnyQuoteErrorInfo* errorInfo, int requestID,
                                 bool isLast);

  //查询交易日K线应答
  //@param  pData 应答对象
  //@param  errorInfo 错误信息对象
  //@param requestID 请求ID
  //@param  bIsLast 是否是最后一个应答
  virtual void OnRspQryTradedayKLine(ESunnyQuoteKLine* pData,
                                     ESunnyQuoteErrorInfo* errorInfo,
                                     int requestID, bool isLast);
  //////////////////////////////////////////////////////////////////////////

 public:
  void setCurrPath(const std::string& value) { curr_path_ = value; }
  void setIp(const std::string& value) { sip_ = value; }
  std::string getIp() { return sip_; }
  void setPort(int value) { nport_ = value; }
  int getPort() { return nport_; }
  void setUserId(const std::string& value) { userid_ = value; }
  void setPassword(const std::string& value) { password_ = value; }
  void setServerType(QUOTE_SERVER_TYPE value) { serverType_ = value; }
  QUOTE_SERVER_TYPE getServerType() { return serverType_; }
  void setInterface_addr(const std::string& value) { interface_addr_ = value; }
  void setExchangeID(const std::string& value) { exchangeId_ = value; }
  void setInstrumetID(const std::string& value) { instrumentId_ = value; }

 private:
  //  查询合约
  void query_instrument();

  // 自定义操作
  void test_operation(int operation);

  // 订阅合约
  void sub_instrument(const std::string& exchangeid,
                      const std::string& instrumentid);

 private:
  int m_nRequestID;
  CEsunnyQuoteApi* m_pEQapi_;

  std::string curr_path_;

  //////////////////////////////////////////////////////////////////////////
  // test info
  string sip_;
  string localip_;
  int nport_;
  string userid_;
  string password_;
  // 服务器类型
  QUOTE_SERVER_TYPE serverType_;
  // 本地接收udp网卡信息（网卡ip或网卡设备名）
  std::string interface_addr_;
  // 测试的交易所
  std::string exchangeId_;
  // 测试的合约
  std::string instrumentId_;
  ESunnyQuoteSpecificInstrumentField* Instruments_[100];
  ESunnyQuoteSpecificInstrumentField filed_[100];
  int instrumentCount_;

  // 合约类型
  int instrumentType_;
  std::string productid_;
  int productclass_;
  int optionstype_;

  //测试类型：
  int operationType_;

  // 测试的交易日
  std::string tradingday_;
  std::string startdatetime_;
  std::string enddatetime_;
  //测试的K线类型
  int klinettype_;
  // 测试的K线数量
  int klinecount_;
  // 测试的K线时间
  std::string klinedate_;
  std::string klinetime_;
  //////////////////////////////////////////////////////////////////////////

  // 测试成员
  long instrument_record_count_;
  long his_record_count_;
  long his_tick_count_;

  long min_record_count_;
  long day_record_count_;
  long rtn_record_count_;
  long rtn_tick_count_;

  std::ofstream outFile_;
  std::ofstream instrumentFile_;
  std::ofstream errorFile_;
};

#endif