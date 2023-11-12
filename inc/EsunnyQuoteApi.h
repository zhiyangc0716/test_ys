
#ifndef __ESUNNY_QUOTE_API_SECTION__
#define __ESUNNY_QUOTE_API_SECTION__

#include "EsunnyQuoteApiStruct.h"

#ifdef ESUNNYQUOTEAPI_EXPORTS
#define ESUNNYQUOTEAPI _declspec(dllexport)
#else
#define ESUNNYQUOTEAPI
#endif

namespace esunny_quote_api {
//����Api�ص�����
class CEsunnyQuoteSpi {
 public:
  //���ͻ������������������ʱ����δ��¼ǰ�����÷��������á�??
  //ͨ����������е�¼����??
  virtual void OnFrontConnected() {};

  //���ͻ�������������ӶϿ�ʱ���÷��������á�??
  //��������������API���Զ��������ӡ�
  //@param  nReason ����ԭ��
  //        0x1001 �����ʧ��??
  //        0x1002 ����дʧ��
  //        0x2001 ����������ʱ
  //        0x2002 ��������ʧ��
  //        0x2003 �յ�������
  virtual void OnFrontDisconnected(int nReason) {};

  //��¼Ӧ��
  //@param  pRspUserLogin Ӧ�����??
  //@param  errorInfo ������Ϣ����
  //@param requestID ����ID
  //@param  bIsLast �Ƿ������һ��Ӧ��??
  virtual void OnRspQuoteLogin(ESunnyQuoteRspUserLoginField* pRspUserLogin,
                               ESunnyQuoteErrorInfo* errorInfo, int requestID,
                               bool bIsLast) {};

  //�ǳ�Ӧ��
  //@param  errorInfo ������Ϣ����
  //@param requestID ����ID
  virtual void OnRspQuoteLogout(ESunnyQuoteErrorInfo* errorInfo,
                                int requestID) {};

  //�޸�����Ӧ��
  //@param  errorInfo ������Ϣ����
  //@param requestID ����ID
  virtual void OnRspChangePassword(ESunnyQuoteErrorInfo* errorInfo,
                                   int requestID) {};

  //���Ϳͻ����˳���Ϣ�������������߳��ͻ���
  //@param  errorInfo ������Ϣ����
  virtual void OnRtnClientExit(ESunnyQuoteErrorInfo* errorInfo) {};

  //���ͽ������б���Ϣ����½�ɹ�ʱ����
  //@param  data
  //��������Ϣ����̨֧�ֵĽ�������
  //@param  bIsLast �Ƿ������һ�����?
  virtual void OnRtnExchangeList(ESunnyExchangeItemField* pData,
                                 bool isLast) {};

  //����UDP��Ϣ�����init�Ĳ���servertype=QST_UDPTICK�����¼�ɹ�����յ�һ������
  //@param  data UDP��Ϣ��SubscribeUdpInfo�õ������ݣ�
  //@param  bIsLast �Ƿ������һ�����?
  virtual void OnRtnUdpInfoData(const ESunnyUdpInfoField& data, bool isLast) {};

  //����������Ӧ
  //@param  pSpecificInstrument Ӧ�����??
  //@param  errorInfo ������Ϣ����
  //@param requestID ����ID
  //@param  bIsLast �Ƿ������һ��Ӧ��??
  virtual void OnRspSubscribeMarketData(
      ESunnyQuoteSpecificInstrumentField* pSpecificInstrument,
      ESunnyQuoteErrorInfo* errorInfo, int nRequestID, bool bIsLast) {};

  //ȡ������������Ӧ
  //@param  pSpecificInstrument Ӧ�����??
  //@param  errorInfo ������Ϣ����
  //@param requestID ����ID
  //@param  bIsLast �Ƿ������һ��Ӧ��??
  virtual void OnRspUnSubscribeMarketData(
      ESunnyQuoteSpecificInstrumentField* pSpecificInstrument,
      ESunnyQuoteErrorInfo* errorInfo, int nRequestID, bool bIsLast) {};

  //����K��������Ӧ
  //@param  pSpecificInstrument Ӧ�����??
  //@param  errorInfo ������Ϣ����
  //@param requestID ����ID
  //@param  bIsLast �Ƿ������һ��Ӧ��??
  virtual void OnRspSubscribeKLineData(
      ESunnyQuoteSpecificInstrumentField* pSpecificInstrument,
      ESunnyQuoteErrorInfo* errorInfo, int nRequestID, bool bIsLast) {};

  //ȡ������K��������Ӧ
  //@param  pSpecificInstrument Ӧ�����??
  //@param  errorInfo ������Ϣ����
  //@param requestID ����ID
  //@param  bIsLast �Ƿ������һ��Ӧ��??
  virtual void OnRspUnSubscribeKLineData(
      ESunnyQuoteSpecificInstrumentField* pSpecificInstrument,
      ESunnyQuoteErrorInfo* errorInfo, int nRequestID, bool bIsLast) {};

  //��ѯ��ԼӦ��
  //@param  pData Ӧ�����??
  //@param  errorInfo ������Ϣ����
  //@param requestID ����ID
  //@param  bIsLast �Ƿ������һ��Ӧ��??
  virtual void OnRspQryInstrument(ESunnyInstrumentField* pData,
                                  ESunnyQuoteErrorInfo* errorInfo,
                                  int requestID, bool isLast) {};

  //��ѯ��ʷ��������Ӧ��
  //@param  pData Ӧ�����??
  //@param  errorInfo ������Ϣ����
  //@param requestID ����ID
  //@param  bIsLast �Ƿ������һ��Ӧ��??
  virtual void OnRspQryHisSnapshotQuote(ESunnyQuoteMarketField* pData,
                                        ESunnyQuoteErrorInfo* errorInfo,
                                        int requestID, bool isLast) {};

  //��ѯ����K��Ӧ��
  //@param  pData Ӧ�����??
  //@param  errorInfo ������Ϣ����
  //@param requestID ����ID
  //@param  bIsLast �Ƿ������һ��Ӧ��??
  virtual void OnRspQryKLineQuote(ESunnyQuoteKLine* pData,
                                  ESunnyQuoteErrorInfo* errorInfo,
                                  int requestID, bool isLast) {};

  //���Ϳ��������??����Ӧ���Ŀ���
  // SubscribeMarketData
  // �˿������Ͱ�������ͨ��Ƭ���պ���ʿ���??
  //@param  pData Ӧ�����??
  virtual void OnRtnDepthMarketData(ESunnyQuoteMarketField* pData) {};

  //����K�ߣ���Ӧ����K�� SubscribeKLineData
  //@param  pData Ӧ�����??
  virtual void OnRtnKLineQuoteData(ESunnyQuoteKLine* pData) {};

  //////////////////////////////////////////////////////////////////////////
  /// ����Ϊ��չ���ܣ���������?�ɲ���ע
  //////////////////////////////////////////////////////////////////////////
  //��������������?
  //@param  pSpecificInstrument Ӧ�����??
  //@param  errorInfo ������Ϣ����
  //@param requestID ����ID
  //@param  bIsLast �Ƿ������һ��Ӧ��??
  virtual void OnRspSubscribeTickData(
      ESunnyQuoteSpecificInstrumentField* pSpecificInstrument,
      ESunnyQuoteErrorInfo* errorInfo, int nRequestID, bool bIsLast) {};

  //ȡ����������������?
  //@param  pSpecificInstrument Ӧ�����??
  //@param  errorInfo ������Ϣ����
  //@param requestID ����ID
  //@param  bIsLast �Ƿ������һ��Ӧ��??
  virtual void OnRspUnSubscribeTickData(
      ESunnyQuoteSpecificInstrumentField* pSpecificInstrument,
      ESunnyQuoteErrorInfo* errorInfo, int nRequestID, bool bIsLast) {};

  //��ѯ��ʷ���Ӧ��??
  //@param  pData Ӧ�����??
  //@param  errorInfo ������Ϣ����
  //@param requestID ����ID
  //@param  bIsLast �Ƿ������һ��Ӧ��??
  virtual void OnRspQryHisTickQuote(ESunnyQuoteTickField* pData,
                                    ESunnyQuoteErrorInfo* errorInfo,
                                    int requestID, bool isLast) {};

  //����ԭʼ���գ����������������������������Ӧ���Ŀ���??
  //@param  pData Ӧ�����??
  virtual void OnRtnOriginalSnap(ESunnyQuoteMarketField* pData) {};

  //������ʱ�??�����������������������������Ӧ�������
  // SubscribeTickData
  //@param  pData Ӧ�����??
  virtual void OnRtnTickQuoteData(ESunnyQuoteTickField* pData) {};

  //��ѯ������ս���Ӧ��??
  //@param  pData Ӧ�����??
  //@param  errorInfo ������Ϣ����
  //@param requestID ����ID
  //@param  bIsLast �Ƿ������һ��Ӧ��??
  virtual void OnRspQrySnapshotSection(ESunnyQuoteMarketField* pData,
                                       ESunnyQuoteErrorInfo* errorInfo,
                                       int requestID, bool isLast) {};

  //��ѯ������Ӧ��
  //@param  pData Ӧ�����??
  //@param  errorInfo ������Ϣ����
  //@param requestID ����ID
  //@param  bIsLast �Ƿ������һ��Ӧ��??
  virtual void OnRspQryTradingDay(ESunnyTradingDayField* pData,
                                  ESunnyQuoteErrorInfo* errorInfo,
                                  int requestID, bool isLast) {};

  //��ѯ����ʱ��Ӧ��
  //@param  pData Ӧ�����??
  //@param  errorInfo ������Ϣ����
  //@param requestID ����ID
  //@param  bIsLast �Ƿ������һ��Ӧ��??
  virtual void OnRspQryTradeTime(ESunnyQuoteTradeTimeField* pData,
                                 ESunnyQuoteErrorInfo* errorInfo, int requestID,
                                 bool isLast) {};

  //��ѯ������K��Ӧ��
  //@param  pData Ӧ�����??
  //@param  errorInfo ������Ϣ����
  //@param requestID ����ID
  //@param  bIsLast �Ƿ������һ��Ӧ��??
  virtual void OnRspQryTradedayKLine(ESunnyQuoteKLine* pData,
                                     ESunnyQuoteErrorInfo* errorInfo,
                                     int requestID, bool isLast) {};
  //////////////////////////////////////////////////////////////////////////
};

//����Api����
class ESUNNYQUOTEAPI CEsunnyQuoteApi {
 protected:
  CEsunnyQuoteApi();
  virtual ~CEsunnyQuoteApi();

 public:
  //����Apiʵ��
  static CEsunnyQuoteApi* CreateEsunnyQuoteApi();

  //�ͷ�Api����
  virtual void Release() = 0;

  //��ȡ��ǰApi�汾��Ϣ
  virtual const char* GetVersion() = 0;

  //��ȡ��ǰ���ӷ��������ͣ�ʵʱ,��ʷ,��ʻ�udp
  virtual QUOTE_SERVER_TYPE GetServerType() = 0;

  //ע��Fensǰ�õ�ַ����ע��������ͨ��Fens��ȡ����������������ϣ�Fens�Զ�ѡ���������������??
  //@param ip  ��֤������IP��ַ
  //@param port ��֤�������˿ں�
  virtual void RegisterFens(const char* ip, int port) = 0;

  //ע��Frontǰ�õ�ַ����ע��������ͨ��Frontֱ�ӽ������������??
  //@param ip  ������IP��ַ
  //@param port �������˿ں�
  virtual void RegisterFront(const char* ip, int port) = 0;

  //ע��ص�����??
  //@param pSpi �����Իص��ӿ����ʵ��??
  virtual void RegisterSpi(CEsunnyQuoteSpi* pSpi) = 0;

  //��ʼ��,��ʼ�������������??
  //@param serverType ���������ͣ�ʵʱ����ʷ
  //@param waittime �ȴ���ʱʱ�䣺��λ����
  virtual void Init(QUOTE_SERVER_TYPE serverType = QST_REALTIME,
                    int waittime = 1) = 0;

  //��¼����
  //@param login ��¼����
  //@param requestID ����ID
  //@����ֵ 0:�ɹ�
  virtual int ReqQuoteLogin(ESunnyQuoteLogin* login, int requestID) = 0;

  //�ǳ�����
  //@param userid �û�id
  //@param requestID ����ID
  //@����ֵ 0:�ɹ�
  virtual int ReqQuoteLogout(TEsunnyQuoteID userid, int requestID) = 0;

  //�޸�����
  //@param req �޸��������??
  //@param requestID ����ID
  //@����ֵ 0:�ɹ�
  virtual int ReqChangePassword(ESunnyChangePassword* req, int requestID) = 0;

  //ȡ�ý������ַ���
  //@param exchangeEnum ������ö��ֵ
  //@����ֵ ���ؿ��ַ�����û���ҵ�
  virtual const char* GetExchangeString(
      const EXCHANGE_TYPE_ID exchangeEnum) = 0;

  //ȡ�ý�����ö��ֵ
  //@param eti
  //�������ַ������������б���OnRtnExchangeList�л�ȡ��
  //@����ֵ
  //����EXCHANGE_TYPE_ID::ETI_UNKNOWN��û���ҵ�
  virtual EXCHANGE_TYPE_ID GetExchangeEnum(const char* exchangeID) = 0;

  //���Ŀ�������
  //@param ppInstrumentID
  //��Լ���󼯺ϣ�������+��ԼID��
  //@param nCount ��Լ����
  //@����ֵ 0:�ɹ�
  virtual int SubscribeMarketData(
      ESunnyQuoteSpecificInstrumentField* ppInstrumentID[], int nCount) = 0;

  //ȡ�����Ŀ�������
  //@param ppInstrumentID
  //��Լ���󼯺ϣ�������+��ԼID��
  //@param nCount ��Լ����
  //@����ֵ 0:�ɹ�
  virtual int UnSubscribeMarketData(
      ESunnyQuoteSpecificInstrumentField* ppInstrumentID[], int nCount) = 0;

  //��������KLine
  //@param ppInstrumentID
  //��Լ���󼯺ϣ�������+��ԼID��
  //@param nCount ��Լ����
  //@����ֵ 0:�ɹ�
  virtual int SubscribeKLineData(
      ESunnyQuoteSpecificInstrumentField* ppInstrumentID[], int nCount,
      KLINE_TYPE_ID klineType = KLINE_TYPE_ID::KTI_MIN) = 0;

  //ȡ����������KLine
  //@param ppInstrumentID
  //��Լ���󼯺ϣ�������+��ԼID��
  //@param nCount ��Լ����
  //@����ֵ 0:�ɹ�
  virtual int UnSubscribeKLineData(
      ESunnyQuoteSpecificInstrumentField* ppInstrumentID[], int nCount,
      KLINE_TYPE_ID klineType = KLINE_TYPE_ID::KTI_MIN) = 0;

  //��ѯ��Լ
  //@param req
  //��ѯ���󣨸��ݲ���ֵ��ͬ�ɲ�ѯ���к�Լ��ָ����������Լ��������Լ�ȣ�
  //@param requestID ����ID
  //@����ֵ 0:�ɹ�
  virtual int ReqQryInstrument(ESunnyQuoteReqQryInstrument* req,
                               int requestID) = 0;

  //��ѯ��ʷ�������飨���ݿͻ�Ȩ�ޣ��ɲ�ѯ��ͬ��������ͬ��ݵ�����??
  //@param req ��ѯ����
  //@param requestID ����ID
  //@����ֵ 0:�ɹ�
  virtual int ReqQrySnapshotQuote(ESunnyQuoteReqQrySnapshot* req,
                                  int requestID) = 0;

  //��ѯ����K�����󣨸��ݿͻ�Ȩ�ޣ��ɲ�ѯ��ͬ�����������飩
  //@param req ��ѯ����
  //@param requestID ����ID
  //@����ֵ 0:�ɹ�
  virtual int ReqQryKLineQuote(ESunnyQuoteReqQryKLine* req, int requestID) = 0;

  //����UDP��Ϣ����OnRtnUdpInfoData�е��øú���
  //�ͻ��˸���udpinfo�е�exchange��products���жϣ��Ƿ���
  //@param udpinfo UDP��Ϣ
  //@����ֵ 0:�ɹ�
  virtual int SubscribeUdpInfo(const ESunnyUdpInfoField& udpinfo) = 0;

  //����UDP����
  //@param interface_addr
  //���ؽ���udp������Ϣ������ip�������豸����
  //@����ֵ 0:�ɹ�
  virtual int StartUdpWork(const char* interface_addr = nullptr) = 0;

  //////////////////////////////////////////////////////////////////////////
  /// ����Ϊ��չ���ܣ���������?�ɲ���ע
  //////////////////////////////////////////////////////////////////////////
  //�����������??
  //@param ppInstrumentID
  //��Լ���󼯺ϣ�������+��ԼID��
  //@param nCount ��Լ����
  //@����ֵ 0:�ɹ�
  virtual int SubscribeTickData(
      ESunnyQuoteSpecificInstrumentField* ppInstrumentID[], int nCount) = 0;

  //ȡ�������������??
  //@param ppInstrumentID
  //��Լ���󼯺ϣ�������+��ԼID��
  //@param nCount ��Լ����
  //@����ֵ 0:�ɹ�
  virtual int UnSubscribeTickData(
      ESunnyQuoteSpecificInstrumentField* ppInstrumentID[], int nCount) = 0;

  //��ѯ��ʷ������󣨸��ݿͻ��?�ޣ��ɲ�ѯ��ͬ��������ͬ��ݵ�����??
  //@param req ��ѯ����
  //@param requestID ����ID
  //@����ֵ 0:�ɹ�
  virtual int ReqQryTickQuote(ESunnyQuoteReqQryTick* req, int requestID) = 0;

  //��ѯ���ս���
  //@param req ��ѯ����CTestEsunnyQuoteSpi
  //@param requestID ����ID
  //@����ֵ 0:�ɹ�
  virtual int ReqQrySnapshotSection(ESunnyQuoteReqQrySnapshotSection* req,
                                    int requestID) = 0;

  //��ѯ�����գ���ѯĳ���������ĵ�ǰ�������б���
  //@param req ��ѯ����
  //@param requestID ����ID
  //@����ֵ 0:�ɹ�
  virtual int ReqQryTradingDay(ESunnyQuoteReqQryTradingDay* req,
                               int requestID) = 0;

  //��ѯ����ʱ��Σ����?ĳ��������ĳ��Ʒ��ĳ�������յĽ���ʱ��Σ�??
  //@param req ��ѯ����
  //@param requestID ����ID
  //@����ֵ 0:�ɹ�
  virtual int ReqQryTradeTime(EsunnyQuoteReqQryTradetime* req,
                              int requestID) = 0;

  //��ѯ������K-min�ߣ���ѯĳ��������ĳ����Լĳ�������յ����з����ߣ�
  //@param req ��ѯ����
  //@param requestID ����ID
  //@����ֵ 0:�ɹ�
  virtual int ReqQryTradedayKline(EsunnyQuoteReqQryTradedayKline* req,
                                  int requestID) = 0;

  // ������?��ķ��������?����������ע�ᣩ
  //@param bFens
  //�Ƿ������Fens��Ϣ��Ĭ�����Front��Ϣ
  virtual void ClearServerInfo(bool bFens = false) = 0;
  //////////////////////////////////////////////////////////////////////////
};
}  // namespace esunny_quote_api

#endif
