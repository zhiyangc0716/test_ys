
#ifndef __ESUNNY_QUOTEAPISTRUCT_SECTION__
#define __ESUNNY_QUOTEAPISTRUCT_SECTION__

#include "EsunnyQuoteApiDataType.h"

namespace esunny_quote_api {
//��������ַ����
struct ServerIpPort {
  char ip[20];
  int port;
};

//������Ϣ����
struct ESunnyQuoteErrorInfo {
  //����id
  TEsunnyQuoteErrorCode errorcode;
  //������Ϣ
  TEsunnyQuoteErrorMsg errormsg;
};

//����ʱ����󣨲�ѯK��ʹ�ã�
struct ESunnyQuoteDateTime {
  //����
  TEsunnyQuoteDate quoteDay;
  //ʱ��
  TEsunnyQuoteTime quoteTime;
};

//�����ն���
struct ESunnyTradingDayField {
  //����������
  TEsunnyQuoteExchange exchangeID;
  //�������б�
  TEsunnyTradingDayField tradingday;
  // ���ͣ�0-�������б�1-��ǰ�����գ�2-��һ�����գ�3-��һ������
  int type = 3;
};

//����ʱ�����
struct ESunnyQuoteTradeTimeField {
  //������
  TEsunnyQuoteExchange exchangeid;
  //Ʒ��
  TEsunnyQuoteProductInfo productid;
  //������
  TEsunnyQuoteDate tradeday;
  //��ʼʱ��
  TEsunnyQuoteTime starttime;
  //����ʱ��
  TEsunnyQuoteTime stoptime;
};

// UDP��Ϣ����
struct ESunnyUdpInfoField {
  //ͨ���ţ��磺9382
  char channelno[20];
  //ͨ�������磺9382-a
  char channelname[50];
  //���������磺NYMEX
  EXCHANGE_TYPE_ID exchange;
  //Ʒ�ּ��ϣ��磺CL|NG
  char products[8000];
  char sUdpAdr_a[32];
  char sUdpAdr_b[32];
};

//��������Ŀ����
struct ESunnyExchangeItemField {
  //������ID������Ϊö�ٲ���
  int id;
  //����������
  TEsunnyQuoteExchange exchangeid;
};

//���ĺ�Լ����
struct ESunnyQuoteSpecificInstrumentField {
  //��Լ����
  TEsunnyQuoteInstrumentID InstrumentID;
  //����������
  EXCHANGE_TYPE_ID ExchangeID;
};

// K�߶���
struct ESunnyQuoteKLine {
  //��Լ����
  TEsunnyQuoteInstrumentID instrumentID;
  //����������
  TEsunnyQuoteExchange exchangeID;
  // K��������
  KLINE_TYPE_ID klineType;
  //��������
  TEsunnyQuoteDate quoteDay;
  //����ʱ��
  TEsunnyQuoteTime quoteTime;
  //��߼�
  TEsunnyQuotePrice highestPrice;
  //��ͼ�
  TEsunnyQuotePrice lowestPrice;
  //���̼�
  TEsunnyQuotePrice openPrice;
  //���̼�
  TEsunnyQuotePrice closePrice;
  //�ɽ����
  TEsunnyQuoteMoney turnover;
  //�ɽ���
  TEsunnyQuoteVolume volume;
  //�ֲ���
  TEsunnyQuoteVolume openinterest;
  ///������
  TEsunnyQuoteDate tradingday;
  ///�վ���
  TEsunnyQuotePrice averageprice;
  ///�����ھ���
  TEsunnyQuotePrice averageprice_min;
};

//��Լ����
struct ESunnyInstrumentField {
  //����������
  TEsunnyQuoteExchange exchangeid;
  //��Լ����
  TEsunnyQuoteInstrumentID instrumentid;
  //��Լ����
  TEsunnyQuoteInstrumentName instrumentname;
  //��Լ�ڽ������Ĵ���
  TEsunnyQuoteInstrumentID exchangeinstid;
  //Ʒ�ִ���
  TEsunnyQuoteProductInfo productid;
  //Ʒ�����
  TEsunnyQuoteProductClass productclass;
  //������Ʒ����
  TEsunnyQuoteString underlyinginstrid;
  //��Ʒ�����
  TEsunnyQuoteString productgroupid;
  //��ǰ�Ƿ���
  TEsunnyQuoteBool istrading;
  //�ֲ�����
  TEsunnyQuotePositionType positiontype;
  //��Ȩ����
  TEsunnyQuoteOptionsType optionstype;
  //ִ�м�
  TEsunnyQuotePrice strikeprice;
  //��С�䶯��λ
  TEsunnyQuotePrice pricetick;
  //��Լ����
  TEsunnyQuoteVolumeMultiple volumemultiple;
  //��Լ������Ʒ����
  TEsunnyQuoteUnderlyingMultipleType underlyingmultiple;
  //�м۵�����µ���
  TEsunnyQuoteVolumeType maxmarketordervolume;
  //�м۵���С�µ���
  TEsunnyQuoteVolumeType minmarketordervolume;
  //�޼۵���С�µ���
  TEsunnyQuoteVolumeType maxlimitordervolume;
  //�޼۵���С�µ���
  TEsunnyQuoteVolumeType minlimitordervolume;
  //������
  TEsunnyQuoteYear deliveryyear;
  //������
  TEsunnyQuoteMonth deliverymonth;
  //������
  TEsunnyQuoteDate createdate;
  //������
  TEsunnyQuoteDate opendate;
  //������
  TEsunnyQuoteDate expiredate;
  //��ʼ������
  TEsunnyQuoteDate startdelivdate;
  //��󽻸���
  TEsunnyQuoteDate enddelivdate;
  //��ʾ����
  TEsunnyQuotePrice displayfactor;
  //��Ʒ�����
  TEsunnyQuoteRemark tradetime;
  //��ͣ��
  TEsunnyQuotePrice upperlimitprice;
  //��ͣ��
  TEsunnyQuotePrice lowerlimitprice;
};

//������ն���
struct ESunnyQuoteMarketField {
  // ��Լ���
  int rptseq;
  // ����
  TEsunnyQuoteMsgSeqNum msgseqnum;

  //��Լ����
  TEsunnyQuoteInstrumentID instrumentID;
  //����������
  TEsunnyQuoteExchange exchangeID;
  //������ʱ��(YYYYMMDD-HH:MM:SS.123456789)
  TEsunnyQuoteTime exchangeupdateTime;
  //������(YYYYMMDD)
  TEsunnyQuoteDate tradingDay;
  //����޸�ʱ��(HH:MM:SS)
  TEsunnyQuoteTime updateTime;
  //����޸�ʱ�䣨΢��:123456��
  TESunnyFtdcSubTimeType updateTimeEx;
  //���¼�
  TEsunnyQuotePrice lastPrice;
  //���վ���
  TEsunnyQuotePrice averagePrice;
  //�ɽ�����
  TEsunnyQuoteVolume volume;
  //����
  TEsunnyQuoteVolume newvolume;
  //�ɽ����
  TEsunnyQuoteMoney turnover;
  //������
  TEsunnyQuotePrice closePrice;
  //������
  TEsunnyQuotePrice preClosePrice;
  //����
  TEsunnyQuotePrice openPrice;
  //��ͼ�
  TEsunnyQuotePrice lowestPrice;
  //��߼�
  TEsunnyQuotePrice highestPrice;
  //��ͣ���
  TEsunnyQuotePrice lowerLimitPrice;
  //��ͣ���
  TEsunnyQuotePrice upperLimitPrice;
  //�ϴν����
  TEsunnyQuotePrice preSettlementPrice;
  //���ν����
  TEsunnyQuotePrice settlementPrice;
  //��ֲ���
  TEsunnyQuoteVolume preOpenInterest;
  //�ֲ���
  TEsunnyQuoteVolume openInterest;
  //����ʵ��
  TEsunnyQuoteRate preDelta;
  //����ʵ��
  TEsunnyQuoteRate currDelta;

  //ʮ������
  // ���鵵λ
  int price_level;
  TEsunnyQuotePrice bidprice[10];
  TEsunnyQuotePrice askprice[10];
  TEsunnyQuoteVolume bidvolume[10];
  TEsunnyQuoteVolume askvolume[10];

  // ��������
  TEsunnyQuotePrice impliedbidprice[2];
  TEsunnyQuotePrice impliedaskprice[2];
  TEsunnyQuoteVolume impliedbidvolume[2];
  TEsunnyQuoteVolume impliedaskvolume[2];

  // ������ǣ��ڼ�����������
  TEsunnyQuoteImpliedTag impliedBidPriceTag[2];
  TEsunnyQuoteImpliedTag impliedBidVolumeTag[2];
  TEsunnyQuoteImpliedTag impliedAskPriceTag[2];
  TEsunnyQuoteImpliedTag impliedAskVolumeTag[2];
};

//����������
struct ESunnyQuoteTickField {
  //��Լ����
  TEsunnyQuoteInstrumentID instrumentID;
  //����������
  TEsunnyQuoteExchange exchangeID;
  //������ʱ��
  TEsunnyQuoteTime exchangeupdatetime;
  //����޸�ʱ��
  TEsunnyQuoteTime updateTime;
  //����޸�ʱ�䣨΢�룩
  TESunnyFtdcSubTimeType updateTimeEx;
  //������������
  TEsunnyIncrementalQuoteType mdType;
  // Type of Market Data update action
  TEsunnyIncrementalQuoteAction mdAction;
  //����
  TEsunnyQuoteVolume volume;
  //�۸�
  TEsunnyQuotePrice price;
  //�۸�λ
  TEsunnyQuoteVolume pricelevel;
  // MsgSeqNum
  TEsunnyQuoteMsgSeqNum msgseqnum;

  int rptseq;
  int matcheventindicator;
};

//��¼����
struct ESunnyQuoteLogin {
  //�˺�
  TEsunnyQuoteID userid;
  //�˺�����
  TEsunnyQuotePassWord password;
  //�ͻ���IP
  TEsunnyQuoteAddress clientip;
  //�ͻ��˰汾
  TEsunnyQuoteVersion clientversion;
  //˵��
  TEsunnyQuoteRemark remark;
  //�ն�����
  char terminaltype[128];
  //��Ʒ����
  char productname[128];
};

//�޸�����
struct ESunnyChangePassword {
  //�˺�
  TEsunnyQuoteID userid;
  //������
  TEsunnyQuotePassWord oldpassword;
  //������
  TEsunnyQuotePassWord newpassword;
};

//��¼Ӧ��
struct ESunnyQuoteRspUserLoginField {
  //�����������Ϣ
  TEsunnyQuoteSvrInfo QuoteSvrInfo;
  //��¼�ɹ�ʱ��
  TEsunnyQuoteTime LoginTime;
  //�û�����
  TEsunnyQuoteID UserID;
  //ǰ�ñ��
  TEsunnyQuoteFrontIDType FrontID;
  //�Ự���
  TEsunnyQuoteSessionIDType SessionID;
};

//��ѯ��Լ���󣬲����򲻹���
struct ESunnyQuoteReqQryInstrument {
  //��Լ����
  TEsunnyQuoteInstrumentID instrumentID;
  //����������
  EXCHANGE_TYPE_ID exchangeID;
  //Ʒ�ִ���
  TEsunnyQuoteProductInfo productID;
  //����������0--�����ˣ� 2--ָ���������� 4--���������� 8--��������
  TEsunnyQuoteFiltertype filtertype;
  //Ʒ�����
  TEsunnyQuoteProductClass productclass;
  //��Ȩ����
  TEsunnyQuoteOptionsType optionstype;
  //�����գ�ѡ�
  TEsunnyQuoteDate tradeday;
};

//��ѯ��������
struct ESunnyQuoteReqQrySnapshot {
  //��Լ���루���
  TEsunnyQuoteInstrumentID instrumentID;
  //���������루���
  EXCHANGE_TYPE_ID exchangeID;
  //��ѯ�����գ����
  TEsunnyQuoteDate TradeDay;
  //��ʼʱ�� 20191210-10:00:00������Ĭ�ϴӵ�ǰ�����տ�ʼ
  TEsunnyQuoteTime StartDatetime;
  //����ʱ�� 20191210-20:00:00������Ĭ�ϵ���ǰ�����ս���
  TEsunnyQuoteTime EndDatetime;
};

//��ѯ����K��
struct ESunnyQuoteReqQryKLine {
  //��Լ����
  TEsunnyQuoteInstrumentID instrumentID;
  //����������
  EXCHANGE_TYPE_ID exchangeID;
  //����ʱ��
  ESunnyQuoteDateTime quoteTime;
  // K����������ǰ������
  TEsunnyQuoteVolumeType klineCount;
  // K������
  KLINE_TYPE_ID klineType;
};

//��ѯ�������
struct ESunnyQuoteReqQryTick {
  //��Լ���루���
  TEsunnyQuoteInstrumentID instrumentID;
  //���������루���
  EXCHANGE_TYPE_ID exchangeID;
  //��ѯ�����գ����
  TEsunnyQuoteDate TradeDay;
  //��ʼʱ�� 20191210-10:00:00������Ĭ�ϴӵ�ǰ�����տ�ʼ
  TEsunnyQuoteTime StartDatetime;
  //����ʱ�� 20191210-20:00:00������Ĭ�ϵ���ǰ�����ս���
  TEsunnyQuoteTime EndDatetime;
};

//��ѯ������ս�������
struct ESunnyQuoteReqQrySnapshotSection {
  //��Լ����
  TEsunnyQuoteInstrumentID instrumentID;
  //����������
  EXCHANGE_TYPE_ID exchangeID;
};

//��ѯ����������
struct ESunnyQuoteReqQryTradingDay {
  //����������
  EXCHANGE_TYPE_ID exchangeID;
  // ���ͣ�0-�������б�1-��ǰ�����գ�2-��һ�����գ�3-��һ������
  int type = 3;
};

//��ѯ����ʱ������
struct EsunnyQuoteReqQryTradetime {
  //����������
  EXCHANGE_TYPE_ID exchangeID;
  //��Լ����
  TEsunnyQuoteProductInfo productid;
  //������
  TEsunnyQuoteDate tradeDay;
};

//��ѯ������K-min������
struct EsunnyQuoteReqQryTradedayKline {
  //����������
  EXCHANGE_TYPE_ID exchangeID;
  //��Լ����
  TEsunnyQuoteInstrumentID instrumentID;
  //������
  TEsunnyQuoteDate tradeDay;
};

}  // namespace esunny_quote_api
#endif