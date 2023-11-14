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
  //���ͻ������������������ʱ����δ��¼ǰ�����÷��������á�
  //ͨ����������е�¼����
  virtual void OnFrontConnected();

  //���ͻ�������������ӶϿ�ʱ���÷��������á�
  //��������������API���Զ��������ӡ�
  //@param  nReason ����ԭ��
  //        0x1001 �����ʧ��
  //        0x1002 ����дʧ��
  //        0x2001 ����������ʱ
  //        0x2002 ��������ʧ��
  //        0x2003 �յ�������
  virtual void OnFrontDisconnected(int nReason);

  //��¼Ӧ��
  //@param  pRspUserLogin Ӧ�����
  //@param  errorInfo ������Ϣ����
  //@param requestID ����ID
  //@param  bIsLast �Ƿ������һ��Ӧ��
  virtual void OnRspQuoteLogin(ESunnyQuoteRspUserLoginField* pRspUserLogin,
                               ESunnyQuoteErrorInfo* errorInfo, int requestID,
                               bool bIsLast);

  //�ǳ�����Ӧ��
  //@param  errorInfo ������Ϣ����
  //@param requestID ����ID
  virtual void OnRspQuoteLogout(ESunnyQuoteErrorInfo* errorInfo, int requestID);

  //�޸�����Ӧ��
  //@param  errorInfo ������Ϣ����
  //@param requestID ����ID
  virtual void OnRspChangePassword(ESunnyQuoteErrorInfo* errorInfo,
                                   int requestID);

  //����������Ӧ
  //@param  pSpecificInstrument Ӧ�����
  //@param  errorInfo ������Ϣ����
  //@param requestID ����ID
  //@param  bIsLast �Ƿ������һ��Ӧ��
  virtual void OnRspSubscribeMarketData(
      ESunnyQuoteSpecificInstrumentField* pSpecificInstrument,
      ESunnyQuoteErrorInfo* errorInfo, int nRequestID, bool bIsLast);

  //ȡ������������Ӧ
  //@param  pSpecificInstrument Ӧ�����
  //@param  errorInfo ������Ϣ����
  //@param requestID ����ID
  //@param  bIsLast �Ƿ������һ��Ӧ��
  virtual void OnRspUnSubscribeMarketData(
      ESunnyQuoteSpecificInstrumentField* pSpecificInstrument,
      ESunnyQuoteErrorInfo* errorInfo, int nRequestID, bool bIsLast);

  //����K��������Ӧ
  //@param  pSpecificInstrument Ӧ�����
  //@param  errorInfo ������Ϣ����
  //@param requestID ����ID
  //@param  bIsLast �Ƿ������һ��Ӧ��
  virtual void OnRspSubscribeKLineData(
      ESunnyQuoteSpecificInstrumentField* pSpecificInstrument,
      ESunnyQuoteErrorInfo* errorInfo, int nRequestID, bool bIsLast);

  //ȡ������K��������Ӧ
  //@param  pSpecificInstrument Ӧ�����
  //@param  errorInfo ������Ϣ����
  //@param requestID ����ID
  //@param  bIsLast �Ƿ������һ��Ӧ��
  virtual void OnRspUnSubscribeKLineData(
      ESunnyQuoteSpecificInstrumentField* pSpecificInstrument,
      ESunnyQuoteErrorInfo* errorInfo, int nRequestID, bool bIsLast);

  //��ѯ��ԼӦ��
  //@param  pData Ӧ�����
  //@param  errorInfo ������Ϣ����
  //@param requestID ����ID
  //@param  bIsLast �Ƿ������һ��Ӧ��
  virtual void OnRspQryInstrument(ESunnyInstrumentField* pData,
                                  ESunnyQuoteErrorInfo* errorInfo,
                                  int requestID, bool isLast);

  //��ѯ��ʷ��������Ӧ��
  //@param  pData Ӧ�����
  //@param  errorInfo ������Ϣ����
  //@param requestID ����ID
  //@param  bIsLast �Ƿ������һ��Ӧ��
  virtual void OnRspQryHisSnapshotQuote(ESunnyQuoteMarketField* pData,
                                        ESunnyQuoteErrorInfo* errorInfo,
                                        int requestID, bool isLast);

  //��ѯ����K��Ӧ��
  //@param  pData Ӧ�����
  //@param  errorInfo ������Ϣ����
  //@param requestID ����ID
  //@param  bIsLast �Ƿ������һ��Ӧ��
  virtual void OnRspQryKLineQuote(ESunnyQuoteKLine* pData,
                                  ESunnyQuoteErrorInfo* errorInfo,
                                  int requestID, bool isLast);

  //���Ϳ�������䶯����Ӧ���Ŀ��� SubscribeMarketData
  //�˿������Ͱ�������ͨ��Ƭ���պ���ʿ���
  //@param  pData Ӧ�����
  virtual void OnRtnDepthMarketData(ESunnyQuoteMarketField* pData);

  //����K�ߣ���Ӧ����K�� SubscribeKLineData
  //@param  pData Ӧ�����
  virtual void OnRtnKLineQuoteData(ESunnyQuoteKLine* pData);

  //����UDP��Ϣ�����init�Ĳ���servertype=QST_UDPTICK�����¼�ɹ�����յ�һ������
  //@param  data UDP��Ϣ��SubscribeUdpInfo�õ������ݣ�
  //@param  bIsLast �Ƿ������һ����Ϣ
  virtual void OnRtnUdpInfoData(const ESunnyUdpInfoField& data, bool isLast);

  //���Ϳͻ����˳���Ϣ�������������߳��ͻ���
  //@param  errorInfo ������Ϣ����
  virtual void OnRtnClientExit(ESunnyQuoteErrorInfo* errorInfo);

  //���ͽ������б���Ϣ����½������
  //@param  data ��������Ϣ����̨֧�ֵĽ�������
  //@param  bIsLast �Ƿ������һ����Ϣ
  virtual void OnRtnExchangeList(ESunnyExchangeItemField* pData, bool isLast);

  //////////////////////////////////////////////////////////////////////////
  /// ����Ϊ��չ���ܣ��������Ҫ�ɲ���ע
  //////////////////////////////////////////////////////////////////////////
  //�������������Ӧ
  //@param  pSpecificInstrument Ӧ�����
  //@param  errorInfo ������Ϣ����
  //@param requestID ����ID
  //@param  bIsLast �Ƿ������һ��Ӧ��
  virtual void OnRspSubscribeTickData(
      ESunnyQuoteSpecificInstrumentField* pSpecificInstrument,
      ESunnyQuoteErrorInfo* errorInfo, int nRequestID, bool bIsLast) {};

  //ȡ���������������Ӧ
  //@param  pSpecificInstrument Ӧ�����
  //@param  errorInfo ������Ϣ����
  //@param requestID ����ID
  //@param  bIsLast �Ƿ������һ��Ӧ��
  virtual void OnRspUnSubscribeTickData(
      ESunnyQuoteSpecificInstrumentField* pSpecificInstrument,
      ESunnyQuoteErrorInfo* errorInfo, int nRequestID, bool bIsLast) {};

  //��ѯ��ʷ���Ӧ��
  //@param  pData Ӧ�����
  //@param  errorInfo ������Ϣ����
  //@param requestID ����ID
  //@param  bIsLast �Ƿ������һ��Ӧ��
  virtual void OnRspQryHisTickQuote(ESunnyQuoteTickField* pData,
                                    ESunnyQuoteErrorInfo* errorInfo,
                                    int requestID, bool isLast);

  //����ԭʼ���գ����������������������������Ӧ���Ŀ���
  //@param  pData Ӧ�����
  virtual void OnRtnOriginalSnap(ESunnyQuoteMarketField* pData) {};

  //������ʱ䶯�����������������������������Ӧ������� SubscribeTickData
  //@param  pData Ӧ�����
  virtual void OnRtnTickQuoteData(ESunnyQuoteTickField* pData) {};

  //��ѯ������ս���Ӧ��
  //@param  pData Ӧ�����
  //@param  errorInfo ������Ϣ����
  //@param requestID ����ID
  //@param  bIsLast �Ƿ������һ��Ӧ��
  virtual void OnRspQrySnapshotSection(ESunnyQuoteMarketField* pData,
                                       ESunnyQuoteErrorInfo* errorInfo,
                                       int requestID, bool isLast);

  //��ѯ������Ӧ��
  //@param  pData Ӧ�����
  //@param  errorInfo ������Ϣ����
  //@param requestID ����ID
  //@param  bIsLast �Ƿ������һ��Ӧ��
  virtual void OnRspQryTradingDay(ESunnyTradingDayField* pData,
                                  ESunnyQuoteErrorInfo* errorInfo,
                                  int requestID, bool isLast);

  //��ѯ����ʱ��Ӧ��
  //@param  pData Ӧ�����
  //@param  errorInfo ������Ϣ����
  //@param requestID ����ID
  //@param  bIsLast �Ƿ������һ��Ӧ��
  virtual void OnRspQryTradeTime(ESunnyQuoteTradeTimeField* pData,
                                 ESunnyQuoteErrorInfo* errorInfo, int requestID,
                                 bool isLast);

  //��ѯ������K��Ӧ��
  //@param  pData Ӧ�����
  //@param  errorInfo ������Ϣ����
  //@param requestID ����ID
  //@param  bIsLast �Ƿ������һ��Ӧ��
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
  //  ��ѯ��Լ
  void query_instrument();

  // �Զ������
  void test_operation(int operation);

  // ���ĺ�Լ
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
  // ����������
  QUOTE_SERVER_TYPE serverType_;
  // ���ؽ���udp������Ϣ������ip�������豸����
  std::string interface_addr_;
  // ���ԵĽ�����
  std::string exchangeId_;
  // ���Եĺ�Լ
  std::string instrumentId_;
  ESunnyQuoteSpecificInstrumentField* Instruments_[100];
  ESunnyQuoteSpecificInstrumentField filed_[100];
  int instrumentCount_;

  // ��Լ����
  int instrumentType_;
  std::string productid_;
  int productclass_;
  int optionstype_;

  //�������ͣ�
  int operationType_;

  // ���ԵĽ�����
  std::string tradingday_;
  std::string startdatetime_;
  std::string enddatetime_;
  //���Ե�K������
  int klinettype_;
  // ���Ե�K������
  int klinecount_;
  // ���Ե�K��ʱ��
  std::string klinedate_;
  std::string klinetime_;
  //////////////////////////////////////////////////////////////////////////

  // ���Գ�Ա
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