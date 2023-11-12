#include "TestEsunnyQuoteSpi.h"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <set>
#include "ini_parser.h"
#include "stdafx.h"

CTestEsunnyQuoteSpi::CTestEsunnyQuoteSpi()
    : m_nRequestID(1), m_pEQapi_(nullptr) {
  instrument_record_count_ = 0;
  his_record_count_ = 0;
  his_tick_count_ = 0;

  min_record_count_ = 0;
  day_record_count_ = 0;
  rtn_record_count_ = 0;
  rtn_tick_count_ = 0;
  operationType_ = 0;
  tradingday_ = "";
  klinettype_ = 0;
  klinecount_ = 0;
  klinedate_ = "";
  klinetime_ = "";
  productclass_ = 0;
  optionstype_ = 0;
  std::string dir = "data";
  createDir(dir);

  //???
  std::string file = dir + PATH_SEPARATOR + "instrument.csv";
  instrumentFile_.open(file.c_str(), std::ios::ate);
  instrumentFile_
      << "instrumentid, exchangeid, productid, underlyinginstrid, exchangeinstid, \
		instrumentname, createdate, opendate, expiredate, productclass, optionstype, positiontype, \
		displayfactor, pricetick, volumemultiple, upperlimitprice, lowerlimitprice"
      << endl;
  instrumentFile_.flush();

  //????
  file = dir + PATH_SEPARATOR + "snapshot.csv";
  outFile_.open(file.c_str(), std::ios::ate);
  char content[2048] = {'\0'};
  sprintf(content,
          "msgseqnum, rptseq, exchangeID, instrumentID, CurrentTime, "
          "exchangeupdateTime, lastPrice, volume, newvolume, settlementPrice"
          ", bidprice_1-bidvolume_1"
          ", bidprice_2-bidvolume_2"
          ", bidprice_3-bidvolume_3"
          ", bidprice_4-bidvolume_4"
          ", bidprice_5-bidvolume_5"
          ", bidprice_6-bidvolume_6"
          ", bidprice_7-bidvolume_7"
          ", bidprice_8-bidvolume_8"
          ", bidprice_9-bidvolume_9"
          ", bidprice_10-bidvolume_10"
          ", askprice_1-askvolume_1"
          ", askprice_2-askvolume_2"
          ", askprice_3-askvolume_3"
          ", askprice_4-askvolume_4"
          ", askprice_5-askvolume_5"
          ", askprice_6-askvolume_6"
          ", askprice_7-askvolume_7"
          ", askprice_8-askvolume_8"
          ", askprice_9-askvolume_9"
          ", askprice_10-askvolume_10"
          ", impliedbidprice-impliedbidvolume"
          ", impliedaskprice-impliedaskvolume\n");

  outFile_ << content;
  outFile_.flush();

  //??????????
  file = dir + PATH_SEPARATOR + "error.csv";
  errorFile_.open(file.c_str(), std::ios::ate);
  char cEcontent[2048] = {'\0'};
  sprintf(cEcontent,
          "msgseqnum, rptseq, exchangeID, instrumentID, CurrentTime, "
          "exchangeupdateTime, lastPrice, volume, newvolume"
          ", bidprice_1-bidvolume_1, askprice_1-askvolume_1\n");
  errorFile_ << cEcontent;
  errorFile_.flush();
}

CTestEsunnyQuoteSpi::~CTestEsunnyQuoteSpi() { OnFrontDisconnected(0); }

void CTestEsunnyQuoteSpi::init(CEsunnyQuoteApi* pEQapi) { m_pEQapi_ = pEQapi; }

void CTestEsunnyQuoteSpi::readIni() {
  INIParser iniPaser;
  std::cout << "Current path: " << curr_path_ << std::endl;
  iniPaser.ReadINI(curr_path_ + PATH_SEPARATOR + "config.ini");

  sip_ = iniPaser.GetValue("comm", "ip");
  localip_ = iniPaser.GetValue("comm", "localip");
  nport_ = std::atoi(iniPaser.GetValue("comm", "port").c_str());
  userid_ = iniPaser.GetValue("comm", "userid");
  password_ = iniPaser.GetValue("comm", "password");
  exchangeId_ = iniPaser.GetValue("comm", "exchangeid");
  instrumentId_ = iniPaser.GetValue("comm", "instrumentid");
  std::cout << "FFFFFF: " << instrumentId_ << std::endl;
  serverType_ = (QUOTE_SERVER_TYPE)std::atoi(
      iniPaser.GetValue("comm", "servertype").c_str());
  interface_addr_ = iniPaser.GetValue("comm", "interfaceaddr");
  instrumentType_ =
      std::atoi(iniPaser.GetValue("comm", "instrumenttype").c_str());
  operationType_ =
      std::atoi(iniPaser.GetValue("comm", "operationtype").c_str());
  tradingday_ = iniPaser.GetValue("comm", "tradingday");
  klinettype_ = std::atoi(iniPaser.GetValue("comm", "klinettype").c_str());
  klinecount_ = std::atoi(iniPaser.GetValue("comm", "klinecount").c_str());
  klinedate_ = iniPaser.GetValue("comm", "klinedate");
  klinetime_ = iniPaser.GetValue("comm", "klinetime");
  startdatetime_ = iniPaser.GetValue("comm", "startdatetime");
  enddatetime_ = iniPaser.GetValue("comm", "enddatetime");
  productid_ = iniPaser.GetValue("comm", "productid");
  productclass_ = std::atoi(iniPaser.GetValue("comm", "productclass").c_str());
  optionstype_ = std::atoi(iniPaser.GetValue("comm", "optionstype").c_str());
}

///???????????????????????????????��?????????��????????��?
void CTestEsunnyQuoteSpi::OnFrontConnected() {
  printf("\nOnFrontConnected\n");

  //???
  ESunnyQuoteLogin login;
  memset(&login, 0, sizeof(login));
  strcpy(login.userid, userid_.c_str());
  strcpy(login.clientip, localip_.c_str());
  strcpy(login.password, password_.c_str());
  m_pEQapi_->ReqQuoteLogin(&login, ++m_nRequestID);
};

///??????????????????????????��????????��???????????????API?????????????????????????????
/// @param  nReason ???????
///        0x1001 ????????
///        0x1002 ????��???
///        0x2001 ???????????
///        0x2002 ???????????
///        0x2003 ?????????
void CTestEsunnyQuoteSpi::OnFrontDisconnected(int nReason) {
  if (nReason != 0) {
    printf("OnFrontDisconnected, nReason = %d\n", nReason);
  }

  instrument_record_count_ = 0;
  his_record_count_ = 0;
  his_tick_count_ = 0;

  min_record_count_ = 0;
  day_record_count_ = 0;
  rtn_record_count_ = 0;
  rtn_tick_count_ = 0;

  instrumentFile_.close();
  outFile_.close();
  errorFile_.close();
};

//????????
//??????
void CTestEsunnyQuoteSpi::OnRspQuoteLogin(
    ESunnyQuoteRspUserLoginField* pRspUserLogin,
    ESunnyQuoteErrorInfo* errorInfo, int requestID, bool bIsLast) {
  std::cout << "PPPPPPPPPPPPPPPPPPpp" << std::endl;
  if (errorInfo != nullptr && errorInfo->errorcode != 0) {
    printf("OnRspQuoteLogin errinfo : %d - %s\n", errorInfo->errorcode,
           errorInfo->errormsg);
  } else {
    printf("OnRspQuoteLogin success\n");

    // ???????
    std::vector<std::string> vecInstrumentId;
    stringsplit(instrumentId_, "|", vecInstrumentId);
    instrumentCount_ = 0;
    for (auto it = vecInstrumentId.begin(); it != vecInstrumentId.end();
         ++it, ++instrumentCount_) {
      filed_[instrumentCount_].ExchangeID =
          m_pEQapi_->GetExchangeEnum(exchangeId_.c_str());
      strcpy(filed_[instrumentCount_].InstrumentID, it->c_str());
      Instruments_[instrumentCount_] = &filed_[instrumentCount_];
    }

    //  ??????
    query_instrument();

    // ???????��???
    test_operation(operationType_);

    ////0.???????
    // ESunnyChangePassword reqChangePassword;
    // strcpy(reqChangePassword.userid, "user001");
    // strcpy(reqChangePassword.oldpassword, "123");
    // strcpy(reqChangePassword.newpassword, "456");
    // m_pEQapi_->ReqChangePassword(&reqChangePassword, ++m_nRequestID);

    /////5.???????????
    // EsunnyQuoteReqQryTradetime reqTradetime;
    // memset(&reqTradetime, 0, sizeof(reqTradetime));
    // reqTradetime.exchangeID = EXCHANGE_TYPE_ID::ETI_SHFE;
    // strcpy(reqTradetime.productid, "CU");
    // strcpy(reqTradetime.tradeDay, "20190919");
    // m_pEQapi_->ReqQryTradeTime(&reqTradetime, ++m_nRequestID);

    //// ?????????
    // ESunnyQuoteReqQryTradingDay reqTradeDay;
    // memset(&reqTradeDay, 0, sizeof(reqTradeDay));
    // reqTradeDay.exchangeID = EXCHANGE_TYPE_ID::ETI_CZCE;
    // reqTradeDay.type = 1;
    // m_pEQapi_->ReqQryTradingDay(&reqTradeDay, ++m_nRequestID);

    /////6.?????????K-min
    // EsunnyQuoteReqQryTradedayKline reqTradedayKline;
    // memset(&reqTradedayKline, 0, sizeof(reqTradedayKline));
    // reqTradedayKline.exchangeID = EXCHANGE_TYPE_ID::ETI_DCE;
    // strcpy(reqTradedayKline.instrumentID, "b2009");
    // strcpy(reqTradedayKline.tradeDay, "20191014");
    // m_pEQapi_->ReqQryTradedayKline(&reqTradedayKline, ++m_nRequestID);

    /// 7.??????????
    // ESunnyQuoteReqQrySnapshotSection reqSnapshotSection;
    // memset(&reqSnapshotSection, 0, sizeof(reqSnapshotSection));
    // reqSnapshotSection.exchangeID =
    //     m_pEQapi_->GetExchangeEnum(exchangeId_.c_str());
    // strcpy(reqSnapshotSection.instrumentID, instrumentId_.c_str());
    // m_pEQapi_->ReqQrySnapshotSection(&reqSnapshotSection, ++m_nRequestID);
    // m_pEQapi_->ReqQryTickQuote(&reqSnapshotSection, ++m_nRequestID);

    ////9.???
    // TEsunnyQuoteID logout_userid = "visitor";
    // m_pEQapi_->ReqQuoteLogout(logout_userid, ++m_nRequestID);
  }
};

//  ??????
void CTestEsunnyQuoteSpi::query_instrument() {
  // 1.??????
  std::cout << "CCCCCCCCC: " << std::endl;
  ESunnyQuoteReqQryInstrument reqInstrument;
  memset(&reqInstrument, 0, sizeof(reqInstrument));
  strcpy(reqInstrument.productID, "");
  reqInstrument.filtertype = instrumentType_;
  if (!exchangeId_.empty()) {
    reqInstrument.exchangeID = m_pEQapi_->GetExchangeEnum(exchangeId_.c_str());
  }
  if (!productid_.empty()) {
    strcpy(reqInstrument.productID, productid_.c_str());
  }
  if (productclass_ != 0) {
    reqInstrument.productclass = productclass_;
  }
  if (optionstype_ != 0) {
    reqInstrument.optionstype = optionstype_;
  }
  if (!tradingday_.empty()) {
    strcpy(reqInstrument.tradeday, this->tradingday_.c_str());
  }

  if (instrumentCount_ > 0) {
    for (int i = 0; i < instrumentCount_; ++i) {
      strcpy(reqInstrument.instrumentID, filed_[i].InstrumentID);
      m_pEQapi_->ReqQryInstrument(&reqInstrument, ++m_nRequestID);
    }
  } else {
    m_pEQapi_->ReqQryInstrument(&reqInstrument, ++m_nRequestID);
  }
}

// ??????
void CTestEsunnyQuoteSpi::sub_instrument(const std::string& exchangeid,
                                         const std::string& instrumentid) {
  ESunnyQuoteSpecificInstrumentField* Instruments[1];
  ESunnyQuoteSpecificInstrumentField filed[1];
  filed[0].ExchangeID = m_pEQapi_->GetExchangeEnum(exchangeid.c_str());
  strcpy(filed[0].InstrumentID, instrumentid.c_str());
  Instruments[0] = &filed[0];
  m_pEQapi_->SubscribeMarketData(&Instruments[0], 1);
}

void CTestEsunnyQuoteSpi::test_operation(int operation) {
  switch (operationType_) {
    case 0: {
      // ???????
      if (instrumentCount_ > 0)
        m_pEQapi_->SubscribeMarketData(&Instruments_[0], instrumentCount_);
      break;
    }
    case 1: {
      // ????k??
      if (instrumentCount_ > 0)
        m_pEQapi_->SubscribeKLineData(&Instruments_[0], instrumentCount_,
                                      (KLINE_TYPE_ID)klinettype_);
      break;
    }
    case 2: {
      // ??????????
      ESunnyQuoteReqQrySnapshot reqHisQuote;
      memset(&reqHisQuote, 0, sizeof(reqHisQuote));
      reqHisQuote.exchangeID = m_pEQapi_->GetExchangeEnum(exchangeId_.c_str());
      strcpy(reqHisQuote.instrumentID, instrumentId_.c_str());
      strcpy(reqHisQuote.TradeDay, tradingday_.c_str());
      strcpy(reqHisQuote.StartDatetime, startdatetime_.c_str());
      strcpy(reqHisQuote.EndDatetime, enddatetime_.c_str());
      m_pEQapi_->ReqQrySnapshotQuote(&reqHisQuote, ++m_nRequestID);
      break;
    }
    case 3: {
      // ???????K??
      ESunnyQuoteReqQryKLine reqKLine;
      memset(&reqKLine, 0, sizeof(reqKLine));
      reqKLine.exchangeID = m_pEQapi_->GetExchangeEnum(exchangeId_.c_str());
      strcpy(reqKLine.instrumentID, instrumentId_.c_str());
      reqKLine.klineType = (KLINE_TYPE_ID)klinettype_;
      strcpy(reqKLine.quoteTime.quoteDay, klinedate_.c_str());
      strcpy(reqKLine.quoteTime.quoteTime, klinetime_.c_str());
      reqKLine.klineCount = klinecount_;
      m_pEQapi_->ReqQryKLineQuote(&reqKLine, ++m_nRequestID);
      break;
    }
    case 4: {
      // ??????
      ESunnyQuoteReqQryTick reqHisQuote;
      memset(&reqHisQuote, 0, sizeof(reqHisQuote));
      reqHisQuote.exchangeID = m_pEQapi_->GetExchangeEnum(exchangeId_.c_str());
      strcpy(reqHisQuote.instrumentID, instrumentId_.c_str());
      strcpy(reqHisQuote.TradeDay, tradingday_.c_str());
      strcpy(reqHisQuote.StartDatetime, startdatetime_.c_str());
      strcpy(reqHisQuote.EndDatetime, enddatetime_.c_str());
      m_pEQapi_->ReqQryTickQuote(&reqHisQuote, ++m_nRequestID);
      break;
    }
    case 5: {
      /// ??????????
      ESunnyQuoteReqQrySnapshotSection reqSnapshotSection;
      memset(&reqSnapshotSection, 0, sizeof(reqSnapshotSection));
      reqSnapshotSection.exchangeID =
          m_pEQapi_->GetExchangeEnum(exchangeId_.c_str());

      if (instrumentCount_ > 0) {
        for (int i = 0; i < instrumentCount_; ++i) {
          strcpy(reqSnapshotSection.instrumentID, filed_[i].InstrumentID);
          m_pEQapi_->ReqQrySnapshotSection(&reqSnapshotSection, ++m_nRequestID);
        }
      } else {
        m_pEQapi_->ReqQrySnapshotSection(&reqSnapshotSection, ++m_nRequestID);
      }
      break;
    }
    default:
      break;
  }
}

//??????????
//@param  errorInfo ???????????
//@param requestID ????ID
void CTestEsunnyQuoteSpi::OnRspQuoteLogout(ESunnyQuoteErrorInfo* errorInfo,
                                           int requestID) {
  if (errorInfo != nullptr && errorInfo->errorcode != 0) {
    printf("OnRspQuoteLogout errinfo : %d - %s\n", errorInfo->errorcode,
           errorInfo->errormsg);
  } else {
    printf("OnRspQuoteLogout success\n");
  }
}

//??????????
//@param  errorInfo ???????????
//@param requestID ????ID
void CTestEsunnyQuoteSpi::OnRspChangePassword(ESunnyQuoteErrorInfo* errorInfo,
                                              int requestID) {
  if (errorInfo != nullptr && errorInfo->errorcode != 0) {
    printf("OnRspChangePassword errinfo : %d - %s\n", errorInfo->errorcode,
           errorInfo->errormsg);
  } else {
    printf("OnRspChangePassword success\n");
  }
}

//???????????(????)
void CTestEsunnyQuoteSpi::OnRspSubscribeMarketData(
    ESunnyQuoteSpecificInstrumentField* pSpecificInstrument,
    ESunnyQuoteErrorInfo* errorInfo, int nRequestID, bool bIsLast) {
  printf("OnRspSubscribeMarketData pSpecificInstrument: %d - %s\n",
         pSpecificInstrument->ExchangeID, pSpecificInstrument->InstrumentID);
  if (errorInfo != nullptr && errorInfo->errorcode != 0) {
    printf("OnRspSubscribeMarketData errinfo : %d - %s\n", errorInfo->errorcode,
           errorInfo->errormsg);
  } else {
    printf("OnRspSubscribeMarketData success\n");
  }
};
//??????????????(????)
void CTestEsunnyQuoteSpi::OnRspUnSubscribeMarketData(
    ESunnyQuoteSpecificInstrumentField* pSpecificInstrument,
    ESunnyQuoteErrorInfo* errorInfo, int nRequestID, bool bIsLast) {
  printf("OnRspUnSubscribeMarketData pSpecificInstrument: %d - %s\n",
         pSpecificInstrument->ExchangeID, pSpecificInstrument->InstrumentID);
  if (errorInfo != nullptr && errorInfo->errorcode != 0) {
    printf("OnRspUnSubscribeMarketData errinfo : %d - %s\n",
           errorInfo->errorcode, errorInfo->errormsg);
  } else {
    printf("OnRspUnSubscribeMarketData success\n");
  }
};

//????K?????????
void CTestEsunnyQuoteSpi::OnRspSubscribeKLineData(
    ESunnyQuoteSpecificInstrumentField* pSpecificInstrument,
    ESunnyQuoteErrorInfo* errorInfo, int nRequestID, bool bIsLast) {
  printf("OnRspSubscribeKLineData pSpecificInstrument: %d - %s\n",
         pSpecificInstrument->ExchangeID, pSpecificInstrument->InstrumentID);
  if (errorInfo != nullptr && errorInfo->errorcode != 0) {
    printf("OnRspSubscribeKLineData errinfo : %d - %s\n", errorInfo->errorcode,
           errorInfo->errormsg);
  } else {
    printf("OnRspSubscribeKLineData success\n");
  }
}
//???????K?????????
void CTestEsunnyQuoteSpi::OnRspUnSubscribeKLineData(
    ESunnyQuoteSpecificInstrumentField* pSpecificInstrument,
    ESunnyQuoteErrorInfo* errorInfo, int nRequestID, bool bIsLast) {
  printf("OnRspUnSubscribeKLineData pSpecificInstrument: %d - %s\n",
         pSpecificInstrument->ExchangeID, pSpecificInstrument->InstrumentID);
  if (errorInfo != nullptr && errorInfo->errorcode != 0) {
    printf("OnRspUnSubscribeKLineData errinfo : %d - %s\n",
           errorInfo->errorcode, errorInfo->errormsg);
  } else {
    printf("OnRspUnSubscribeKLineData success\n");
  }
}

///??????????
//?????????
void CTestEsunnyQuoteSpi::OnRtnDepthMarketData(ESunnyQuoteMarketField* pData) {
  if (pData != NULL) {
    std::uint64_t timestamp = getTimeStamp();

    char content[2048] = {'\0'};

#ifdef _WIN32
    sprintf(content,
            "%lu, %d"
            ", %s, %s"
            ", %llu, %s"
            ", %.4f, %d, %d, %.4f"
            ", %.4f-%d, %.4f-%d"
            ", %.4f-%d, %.4f-%d"
            ", %.4f-%d, %.4f-%d"
            ", %.4f-%d, %.4f-%d"
            ", %.4f-%d, %.4f-%d"
            ", %.4f-%d, %.4f-%d"
            ", %.4f-%d, %.4f-%d"
            ", %.4f-%d, %.4f-%d"
            ", %.4f-%d, %.4f-%d"
            ", %.4f-%d, %.4f-%d"
            ", %.4f-%d, %.4f-%d\n",
            pData->msgseqnum, pData->rptseq, pData->exchangeID,
            pData->instrumentID, timestamp, pData->exchangeupdateTime,
            pData->lastPrice, pData->volume, pData->newvolume,
            pData->settlementPrice, pData->bidprice[0], pData->bidvolume[0],
            pData->bidprice[1], pData->bidvolume[1], pData->bidprice[2],
            pData->bidvolume[2], pData->bidprice[3], pData->bidvolume[3],
            pData->bidprice[4], pData->bidvolume[4], pData->bidprice[5],
            pData->bidvolume[5], pData->bidprice[6], pData->bidvolume[6],
            pData->bidprice[7], pData->bidvolume[7], pData->bidprice[8],
            pData->bidvolume[8], pData->bidprice[9], pData->bidvolume[9],
            pData->askprice[0], pData->askvolume[0], pData->askprice[1],
            pData->askvolume[1], pData->askprice[2], pData->askvolume[2],
            pData->askprice[3], pData->askvolume[3], pData->askprice[4],
            pData->askvolume[4], pData->askprice[5], pData->askvolume[5],
            pData->askprice[6], pData->askvolume[6], pData->askprice[7],
            pData->askvolume[7], pData->askprice[8], pData->askvolume[8],
            pData->askprice[9], pData->askvolume[9], pData->impliedbidprice[0],
            pData->impliedbidvolume[0], pData->impliedaskprice[0],
            pData->impliedaskvolume[0]);
#else
    sprintf(content,
            "%lu, %d"
            ", %s, %s"
            ", %lu, %s"
            ", %.4f, %d, %d, %.4f"
            ", %.4f-%d, %.4f-%d"
            ", %.4f-%d, %.4f-%d"
            ", %.4f-%d, %.4f-%d"
            ", %.4f-%d, %.4f-%d"
            ", %.4f-%d, %.4f-%d"
            ", %.4f-%d, %.4f-%d"
            ", %.4f-%d, %.4f-%d"
            ", %.4f-%d, %.4f-%d"
            ", %.4f-%d, %.4f-%d"
            ", %.4f-%d, %.4f-%d"
            ", %.4f-%d, %.4f-%d\n",
            pData->msgseqnum, pData->rptseq, pData->exchangeID,
            pData->instrumentID, timestamp, pData->exchangeupdateTime,
            pData->lastPrice, pData->volume, pData->newvolume,
            pData->settlementPrice, pData->bidprice[0], pData->bidvolume[0],
            pData->bidprice[1], pData->bidvolume[1], pData->bidprice[2],
            pData->bidvolume[2], pData->bidprice[3], pData->bidvolume[3],
            pData->bidprice[4], pData->bidvolume[4], pData->bidprice[5],
            pData->bidvolume[5], pData->bidprice[6], pData->bidvolume[6],
            pData->bidprice[7], pData->bidvolume[7], pData->bidprice[8],
            pData->bidvolume[8], pData->bidprice[9], pData->bidvolume[9],
            pData->askprice[0], pData->askvolume[0], pData->askprice[1],
            pData->askvolume[1], pData->askprice[2], pData->askvolume[2],
            pData->askprice[3], pData->askvolume[3], pData->askprice[4],
            pData->askvolume[4], pData->askprice[5], pData->askvolume[5],
            pData->askprice[6], pData->askvolume[6], pData->askprice[7],
            pData->askvolume[7], pData->askprice[8], pData->askvolume[8],
            pData->askprice[9], pData->askvolume[9], pData->impliedbidprice[0],
            pData->impliedbidvolume[0], pData->impliedaskprice[0],
            pData->impliedaskvolume[0]);
#endif

    printf("%s", content);
    outFile_ << content;

    if (pData->bidprice[0] >= pData->askprice[0]) {
      errorFile_ << content;
    }

    ++rtn_record_count_;
    if (rtn_record_count_ == 1 || rtn_record_count_ > 1000) {
      rtn_record_count_ = 0;
      outFile_.flush();
    }
  }
}

//// ??????
// void CTestEsunnyQuoteSpi::OnRtnDepthMarketData(ESunnyQuoteMarketField* pData)
//{
//	if (pData != NULL)
//	{
//		std::string timestamp = getCurrentTime();
//
//		// 20190521-16:06:00.058611
//		if (timestamp.compare(0, 8, pData->exchangeupdateTime) > 0)
//			return;
//
//		std::int64_t diff = getMicroByDateTime(timestamp) -
// getMicroByDateTime(pData->exchangeupdateTime); 		int sec = diff /
// 1000000;
//
//		if (sec > 36000)
//			return;
//
//		char content[2048] = { '\0' };
//
//#ifdef _WIN32
//		sprintf(content,
//			"%06d, %s, %s, "
//			"%s, %s, "
//			"%.4f, %d, %d, %.4f"
//			"\n",
//			sec, timestamp.c_str(), pData->updateTime,
//			pData->exchangeID, pData->instrumentID,
//			pData->lastPrice, pData->volume, pData->newvolume,
// pData->settlementPrice); #else 		sprintf(content,
//			"%06d, %s, %s, "
//			"%s, %s, "
//			"%.4f, %d, %d, %.4f"
//			"\n",
//			sec, timestamp.c_str(), pData->updateTime,
//			pData->exchangeID, pData->instrumentID,
//			pData->lastPrice, pData->volume, pData->newvolume,
// pData->settlementPrice); #endif
//
//		printf("%s", content);
//		outFile_ << content;
//
//		if (pData->bidprice[0] >= pData->askprice[0])
//		{
//			errorFile_ << content;
//		}
//
//		++rtn_record_count_;
//		if (rtn_record_count_ == 1 || rtn_record_count_ > 1000)
//		{
//			rtn_record_count_ = 0;
//			outFile_.flush();
//		}
//	}
//}

//????K??(????)
void CTestEsunnyQuoteSpi::OnRtnKLineQuoteData(ESunnyQuoteKLine* pData) {
  if (pData != NULL) {
    printf(
        "OnRtnKLineMin [%d] %s, %s, %s, %s, %s, %f, %f, %f, %f, %f, %d, %d, "
        "%f, %f\n",
        pData->klineType, pData->tradingday, pData->quoteDay, pData->quoteTime,
        pData->exchangeID, pData->instrumentID, pData->openPrice,
        pData->closePrice, pData->highestPrice, pData->lowestPrice,
        pData->turnover, pData->volume, pData->openinterest,
        pData->averageprice, pData->averageprice_min);
  }
}

//????UDP????????init?????servertype=QST_UDPTICK??????????????????????
//@param  data UDP?????SubscribeUdpInfo??????????
//@param  bIsLast ??????????????
void CTestEsunnyQuoteSpi::OnRtnUdpInfoData(const ESunnyUdpInfoField& data,
                                           bool isLast) {
  printf("OnRtnUdpInfoData channelno = %s, exchange = %s, products = %s\n",
         data.channelno, m_pEQapi_->GetExchangeString(data.exchange),
         data.products);

  // std::set<std::string> setProduct;
  // std::vector<std::string> vecProduct;
  // if (stringsplit(data.products, sDivideSymbol, vecProduct) > 0)
  //{
  //	setProduct.insert(vecProduct.begin(), vecProduct.end());
  //}

  //// ????udp???
  // if (data.exchange == EXCHANGE_TYPE_ID::ETI_NYMEX &&
  //	setProduct.find("CL") != setProduct.end())
  //{
  // udp?????????
  m_pEQapi_->SubscribeUdpInfo(data);
  //}
}

//??????????????????????????????????
//@param  errorInfo ???????????
void CTestEsunnyQuoteSpi::OnRtnClientExit(ESunnyQuoteErrorInfo* errorInfo) {
  printf("OnRtnClientExit errinfo : %d - %s\n", errorInfo->errorcode,
         errorInfo->errormsg);
}

//??????????��???????????????
//@param  data ?????????????????????????
//@param  bIsLast ??????????????
void CTestEsunnyQuoteSpi::OnRtnExchangeList(ESunnyExchangeItemField* pData,
                                            bool isLast) {
  printf("OnRtnExchangeList %d - %s\n", pData->id, pData->exchangeid);
}

///????????
//?????????
void CTestEsunnyQuoteSpi::OnRspQryInstrument(ESunnyInstrumentField* pData,
                                             ESunnyQuoteErrorInfo* errorInfo,
                                             int requestID, bool isLast) {
  if (errorInfo != nullptr && errorInfo->errorcode != 0) {
    printf("OnRspQryInstrument errinfo : %d - %s\n", errorInfo->errorcode,
           errorInfo->errormsg);
  } else {
    if (pData != NULL) {
      ++instrument_record_count_;
      char content[2048] = {'\0'};
      sprintf(content,
              "%s, %s, %s, %s, %s, %s, %s, %s, %s, %c, %c, %c, %f, %f, %d, %f, "
              "%f\n",
              pData->instrumentid, pData->exchangeid, pData->productid,
              pData->underlyinginstrid, pData->exchangeinstid,
              pData->instrumentname, pData->createdate, pData->opendate,
              pData->expiredate, pData->productclass, pData->optionstype,
              pData->positiontype, pData->displayfactor, pData->pricetick,
              pData->volumemultiple, pData->upperlimitprice,
              pData->lowerlimitprice);

      printf("%s", content);

      instrumentFile_ << content;
      instrumentFile_.flush();

      //// ??????
      ESunnyQuoteSpecificInstrumentField* Instruments[1];
      ESunnyQuoteSpecificInstrumentField filed[1];
      filed[0].ExchangeID = m_pEQapi_->GetExchangeEnum(pData->exchangeid);
      strcpy(filed[0].InstrumentID, pData->instrumentid);
      Instruments[0] = &filed[0];
      m_pEQapi_->SubscribeMarketData(&Instruments[0], 1);
    }
  }

  if (isLast) {
    printCurrentTime();
    printf("OnRspQryInstrument : %ld\n", instrument_record_count_);

    if (m_pEQapi_->GetServerType() == QUOTE_SERVER_TYPE::QST_UDPTICK &&
        operationType_ == 0) {
      // ???????udp????????
      m_pEQapi_->StartUdpWork(interface_addr_.c_str());
    }
  }
}

//?????????????(????)
void CTestEsunnyQuoteSpi::OnRspQryHisSnapshotQuote(
    ESunnyQuoteMarketField* pData, ESunnyQuoteErrorInfo* errorInfo,
    int requestID, bool isLast) {
  if (errorInfo != nullptr && errorInfo->errorcode != 0) {
    printf("OnRspQryHisQuote errinfo : %d - %s\n", errorInfo->errorcode,
           errorInfo->errormsg);
  } else {
    if (pData != NULL) {
      ++his_record_count_;
      // printf("OnRspQryHisSnapshotQuote : msgseqnum:%d, rptseq:%d, "
      //	"%s, %s, %s, %s, settlementPrice:%f, averagePrice:%f, "
      //	"newvolume:%d, lastPrice:%f, volume:%d, turnover:%f, "
      //	"bid1:%f-%d, bid2:%f-%d, bid3:%f-%d, bid4:%f-%d, bid5:%f-%d,
      // bid6:%f-%d, bid7:%f-%d, bid8:%f-%d, bid9:%f-%d, bid10:%f-%d, "
      //	"ask1:%f-%d, ask2:%f-%d, ask3:%f-%d, ask4:%f-%d, ask5:%f-%d,
      // ask6:%f-%d, ask7:%f-%d, ask8:%f-%d, ask9:%f-%d, ask10:%f-%d "
      //	"\n",
      //	(int)pData->msgseqnum, pData->rptseq,
      //	pData->exchangeID, pData->instrumentID, pData->updateTime,
      // pData->exchangeupdateTime, 	pData->settlementPrice,
      // pData->averagePrice, 	pData->newvolume, pData->lastPrice,
      // pData->volume, pData->turnover, 	pData->bidprice[0],
      // pData->bidvolume[0],
      //	pData->bidprice[1], pData->bidvolume[1],
      //	pData->bidprice[2], pData->bidvolume[2],
      //	pData->bidprice[3], pData->bidvolume[3],
      //	pData->bidprice[4], pData->bidvolume[4],
      //	pData->bidprice[5], pData->bidvolume[5],
      //	pData->bidprice[6], pData->bidvolume[6],
      //	pData->bidprice[7], pData->bidvolume[7],
      //	pData->bidprice[8], pData->bidvolume[8],
      //	pData->bidprice[9], pData->bidvolume[9],
      //	pData->askprice[0], pData->askvolume[0],
      //	pData->askprice[1], pData->askvolume[1],
      //	pData->askprice[2], pData->askvolume[2],
      //	pData->askprice[3], pData->askvolume[3],
      //	pData->askprice[4], pData->askvolume[4],
      //	pData->askprice[5], pData->askvolume[5],
      //	pData->askprice[6], pData->askvolume[6],
      //	pData->askprice[7], pData->askvolume[7],
      //	pData->askprice[8], pData->askvolume[8],
      //	pData->askprice[9], pData->askvolume[9]);

      char content[2048] = {'\0'};

#ifdef _WIN32
      sprintf(content,
              "%lu, %d"
              ", %s, %s"
              ",  %s"
              ", %.4f, %d, %d"
              ", %.4f-%d, %.4f-%d\n",
              pData->msgseqnum, pData->rptseq, pData->exchangeID,
              pData->instrumentID, pData->exchangeupdateTime, pData->lastPrice,
              pData->volume, pData->newvolume, pData->bidprice[0],
              pData->bidvolume[0], pData->askprice[0], pData->askvolume[0]);
#else
      sprintf(content,
              "%lu, %d"
              ", %s, %s"
              ", %s"
              ", %.4f, %d, %d"
              ", %.4f-%d, %.4f-%d\n",
              pData->msgseqnum, pData->rptseq, pData->exchangeID,
              pData->instrumentID, pData->exchangeupdateTime, pData->lastPrice,
              pData->volume, pData->newvolume, pData->bidprice[0],
              pData->bidvolume[0], pData->askprice[0], pData->askvolume[0]);
#endif
      // printf("%s", content);
      outFile_ << content;
    }
  }

  if (isLast) {
    printCurrentTime();
    printf("OnRspQryHisQuote : %ld\n", his_record_count_);
  }
}

//???????K?????
void CTestEsunnyQuoteSpi::OnRspQryKLineQuote(ESunnyQuoteKLine* pData,
                                             ESunnyQuoteErrorInfo* errorInfo,
                                             int requestID, bool isLast) {
  if (errorInfo != nullptr && errorInfo->errorcode != 0) {
    printf("OnRspQryKLineQuote errinfo : %d - %s\n", errorInfo->errorcode,
           errorInfo->errormsg);
  } else {
    if (pData != NULL) {
      ++min_record_count_;

      printf(
          "OnRtnKLineMin [%d] %s, %s, %s, %s, %s, %f, %f, %f, %f, %f, %d, %d, "
          "%f, %f\n",
          pData->klineType, pData->tradingday, pData->quoteDay,
          pData->quoteTime, pData->exchangeID, pData->instrumentID,
          pData->openPrice, pData->closePrice, pData->highestPrice,
          pData->lowestPrice, pData->turnover, pData->volume,
          pData->openinterest, pData->averageprice, pData->averageprice_min);
    }
  }

  if (isLast) {
    printCurrentTime();
    printf("OnRspQryKLineQuote : %ld\n", min_record_count_);
  }
}

//?????????????
void CTestEsunnyQuoteSpi::OnRspQrySnapshotSection(
    ESunnyQuoteMarketField* pData, ESunnyQuoteErrorInfo* errorInfo,
    int requestID, bool isLast) {
  if (errorInfo != nullptr && errorInfo->errorcode != 0) {
    printf("OnRspQrySnapshotSection errinfo : %d - %s\n", errorInfo->errorcode,
           errorInfo->errormsg);
  } else {
    if (pData != NULL) {
      // if(!(m_pEQapi_->GetExchangeEnum(pData->exchangeID) ==
      // EXCHANGE_TYPE_ID::ETI_SSE ||
      //	m_pEQapi_->GetExchangeEnum(pData->exchangeID) ==
      // EXCHANGE_TYPE_ID::ETI_SZSE)) 	sub_instrument(pData->exchangeID,
      // pData->instrumentID);

      printf(
          "OnRspQrySnapshotSection : msgseqnum:%d, rptseq:%d, preDelta:%f, "
          "lowerLimitPrice:%f, upperLimitPrice:%f, "
          "%s, %s, %s, %s, settlementPrice:%f, averagePrice:%f, "
          "newvolume:%d, lastPrice:%f, volume:%d, turnover:%f, "
          "bid1:%f-%d, bid2:%f-%d, bid3:%f-%d, bid4:%f-%d, bid5:%f-%d, "
          "bid6:%f-%d, bid7:%f-%d, bid8:%f-%d, bid9:%f-%d, bid10:%f-%d, "
          "ask1:%f-%d, ask2:%f-%d, ask3:%f-%d, ask4:%f-%d, ask5:%f-%d, "
          "ask6:%f-%d, ask7:%f-%d, ask8:%f-%d, ask9:%f-%d, ask10:%f-%d "
          "\n",
          (int)pData->msgseqnum, pData->rptseq, pData->preDelta,
          pData->lowerLimitPrice, pData->upperLimitPrice, pData->exchangeID,
          pData->instrumentID, pData->updateTime, pData->exchangeupdateTime,
          pData->settlementPrice, pData->averagePrice, pData->newvolume,
          pData->lastPrice, pData->volume, pData->turnover, pData->bidprice[0],
          pData->bidvolume[0], pData->bidprice[1], pData->bidvolume[1],
          pData->bidprice[2], pData->bidvolume[2], pData->bidprice[3],
          pData->bidvolume[3], pData->bidprice[4], pData->bidvolume[4],
          pData->bidprice[5], pData->bidvolume[5], pData->bidprice[6],
          pData->bidvolume[6], pData->bidprice[7], pData->bidvolume[7],
          pData->bidprice[8], pData->bidvolume[8], pData->bidprice[9],
          pData->bidvolume[9], pData->askprice[0], pData->askvolume[0],
          pData->askprice[1], pData->askvolume[1], pData->askprice[2],
          pData->askvolume[2], pData->askprice[3], pData->askvolume[3],
          pData->askprice[4], pData->askvolume[4], pData->askprice[5],
          pData->askvolume[5], pData->askprice[6], pData->askvolume[6],
          pData->askprice[7], pData->askvolume[7], pData->askprice[8],
          pData->askvolume[8], pData->askprice[9], pData->askvolume[9]);

      // char filePath[100] = { '\0' };
      // sprintf(filePath, "%s_market_data.csv", pData->exchangeID);
      // std::ofstream outFile;
      // outFile.open(filePath, std::ios::app);
      // outFile << pData->msgseqnum << "," <<
      //	pData->rptseq << "," <<
      //	pData->instrumentID << "," <<
      //	pData->exchangeID << "," <<
      //	pData->exchangeupdateTime << "," <<
      //	pData->tradingDay << "," <<
      //	pData->updateTime << "," <<
      //	pData->updateTimeEx << "," <<
      //	pData->lastPrice << "," <<
      //	pData->averagePrice << "," <<
      //	/*pData->impliedBidVolumeTag1 << "," <<
      //	pData->impliedBidVolumeTag2 << "," <<
      //	pData->impliedAskVolumeTag1 << "," <<
      //	pData->impliedAskVolumeTag2 << "," <<
      //	pData->impliedBidPriceTag1 << "," <<
      //	pData->impliedBidPriceTag2 << "," <<
      //	pData->impliedAskPriceTag1 << "," <<
      //	pData->impliedAskPriceTag2 << "," <<*/
      //	pData->volume << "," <<
      //	pData->newvolume << "," <<
      //	pData->turnover << "," <<
      //	pData->closePrice << "," <<
      //	pData->preClosePrice << "," <<
      //	pData->openPrice << "," <<
      //	pData->lowestPrice << "," <<
      //	pData->highestPrice << "," <<
      //	pData->lowerLimitPrice << "," <<
      //	pData->upperLimitPrice << "," <<
      //	pData->preSettlementPrice << "," <<
      //	pData->settlementPrice << "," <<
      //	pData->preOpenInterest << "," <<
      //	pData->openInterest << "," <<
      //	pData->preDelta << "," <<
      //	pData->currDelta << "," <<
      //	pData->bidprice[0] << "," << pData->bidvolume[0] << "," <<
      //	pData->bidprice[1] << "," << pData->bidvolume[1] << "," <<
      //	pData->bidprice[2] << "," << pData->bidvolume[2] << "," <<
      //	pData->bidprice[3] << "," << pData->bidvolume[3] << "," <<
      //	pData->bidprice[4] << "," << pData->bidvolume[4] << "," <<
      //	pData->bidprice[5] << "," << pData->bidvolume[5] << "," <<
      //	pData->bidprice[6] << "," << pData->bidvolume[6] << "," <<
      //	pData->bidprice[7] << "," << pData->bidvolume[7] << "," <<
      //	pData->bidprice[8] << "," << pData->bidvolume[8] << "," <<
      //	pData->bidprice[9] << "," << pData->bidvolume[9] << "," <<
      //	pData->askprice[0] << "," << pData->askvolume[0] << "," <<
      //	pData->askprice[1] << "," << pData->askvolume[1] << "," <<
      //	pData->askprice[2] << "," << pData->askvolume[2] << "," <<
      //	pData->askprice[3] << "," << pData->askvolume[3] << "," <<
      //	pData->askprice[4] << "," << pData->askvolume[4] << "," <<
      //	pData->askprice[5] << "," << pData->askvolume[5] << "," <<
      //	pData->askprice[6] << "," << pData->askvolume[6] << "," <<
      //	pData->askprice[7] << "," << pData->askvolume[7] << "," <<
      //	pData->askprice[8] << "," << pData->askvolume[8] << "," <<
      //	pData->askprice[9] << "," << pData->askvolume[9] << std::endl;
      // outFile.close();
    }
  }
}

//????????????
void CTestEsunnyQuoteSpi::OnRspQryTradingDay(ESunnyTradingDayField* pData,
                                             ESunnyQuoteErrorInfo* errorInfo,
                                             int requestID, bool isLast) {
  if (errorInfo != nullptr && errorInfo->errorcode != 0) {
    printf("OnRspQryTradingDay errinfo : %d - %s\n", errorInfo->errorcode,
           errorInfo->errormsg);
  } else {
    if (pData != NULL) {
      printf("OnRspQryTradingDay : %s, %s\n", pData->exchangeID,
             pData->tradingday);
    }
  }

  if (isLast) {
    printCurrentTime();
    printf("OnRspQryTradingDay finished!\n");
  }
}

//??????????????
void CTestEsunnyQuoteSpi::OnRspQryTradeTime(ESunnyQuoteTradeTimeField* pData,
                                            ESunnyQuoteErrorInfo* errorInfo,
                                            int requestID, bool isLast) {
  if (errorInfo != nullptr && errorInfo->errorcode != 0) {
    printf("OnRspQryHisTick errinfo : %d - %s\n", errorInfo->errorcode,
           errorInfo->errormsg);
  } else {
    if (pData != NULL) {
      printf("OnRspQryTradeTime : %s, %s, %s, %s, %s\n", pData->exchangeid,
             pData->productid, pData->tradeday, pData->starttime,
             pData->stoptime);
    }
  }

  if (isLast) {
    printCurrentTime();
    printf("OnRspQryTradeTime finished!\n");
  }
}

//?????????K?????
void CTestEsunnyQuoteSpi::OnRspQryTradedayKLine(ESunnyQuoteKLine* pData,
                                                ESunnyQuoteErrorInfo* errorInfo,
                                                int requestID, bool isLast) {
  if (errorInfo != nullptr && errorInfo->errorcode != 0) {
    printf("OnRspQryTradedayKLine errinfo : %d - %s\n", errorInfo->errorcode,
           errorInfo->errormsg);
  } else {
    if (pData != NULL) {
      ++min_record_count_;

      printf(
          "OnRtnKLineMin [%d] %s, %s, %s, %s, %s, %f, %f, %f, %f, %f, %d, %d, "
          "%f, %f\n",
          pData->klineType, pData->tradingday, pData->quoteDay,
          pData->quoteTime, pData->exchangeID, pData->instrumentID,
          pData->openPrice, pData->closePrice, pData->highestPrice,
          pData->lowestPrice, pData->turnover, pData->volume,
          pData->openinterest, pData->averageprice, pData->averageprice_min);
    }
  }

  if (isLast) {
    printCurrentTime();
    printf("OnRspQryKLineMin : %ld\n", min_record_count_);
  }
}

//?????????
void CTestEsunnyQuoteSpi::OnRspQryHisTickQuote(ESunnyQuoteTickField* pData,
                                               ESunnyQuoteErrorInfo* errorInfo,
                                               int requestID, bool isLast) {
  if (errorInfo != nullptr && errorInfo->errorcode != 0) {
    printf("OnRspQryHisTickQuote errinfo : %d - %s\n", errorInfo->errorcode,
           errorInfo->errormsg);
  } else {
    if (pData != NULL) {
      ++rtn_tick_count_;

      printf("OnRspQryHisTickQuote : %s, %s, %s, %s, %d, %d, %c, %d, %f, %d\n",
             pData->exchangeID, pData->instrumentID, pData->exchangeupdatetime,
             pData->updateTime, pData->updateTimeEx, pData->mdType,
             pData->mdAction, pData->volume, pData->price, pData->pricelevel);
    }
  }

  if (isLast) {
    printCurrentTime();
    printf("OnRspQryHisTickQuote : %ld\n", rtn_tick_count_);
  }
}
