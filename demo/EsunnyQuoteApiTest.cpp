// EsunnyQuoteApiTest.cpp : 定义控制台应用程序的入口点。
//

#include <cstring>
#include <iostream>
#include "EsunnyQuoteApi.h"
#include "TestEsunnyQuoteSpi.h"
#include "stdafx.h"
#include "utility.h"

int main(int argc, char* argv[]) {
  printf("start...\n");

  std::string curr_path = argv[0];
  int pos = curr_path.rfind(PATH_SEPARATOR.c_str());
  curr_path = curr_path.substr(0, pos);

  // 1.创建API实例
  CEsunnyQuoteApi* pEQapi = CEsunnyQuoteApi::CreateEsunnyQuoteApi();

  // 2.注册回调
  CTestEsunnyQuoteSpi spi;
  spi.init(pEQapi);
  pEQapi->RegisterSpi(&spi);

  spi.setCurrPath(curr_path);
  spi.readIni();

  string sip;
  int nport = 6100;
  string userid;
  string password;
  QUOTE_SERVER_TYPE serverType = QUOTE_SERVER_TYPE::QST_UDPTICK;
  std::string interface_addr = "172.26.255.107";

  if (argc >= 2) {
    sip = argv[1];
    spi.setIp(sip);
  }
  if (argc >= 3) {
    nport = atoi(argv[2]);
    spi.setPort(nport);
  }
  if (argc >= 4) {
    userid = argv[3];
    spi.setUserId(userid);
  }
  if (argc >= 5) {
    password = argv[4];
    spi.setPassword(password);
  }
  if (argc >= 6) {
    serverType = (QUOTE_SERVER_TYPE)atoi(argv[5]);
    spi.setServerType(serverType);
  }
  if (argc >= 7) {
    // 本地接收udp网卡信息（网卡ip或网卡设备名，根据本地ip设置）
    interface_addr = argv[6];
    spi.setInterface_addr(interface_addr);
  }
  if (argc >= 8) {
    spi.setExchangeID(argv[7]);
  }
  if (argc >= 9) {
    spi.setInstrumetID(argv[8]);
  }

  //获取当前Api版本信息
  const char* sversion = pEQapi->GetVersion();
  printf("connect to server ip:%s, port:%d %s\n", spi.getIp().c_str(),
         spi.getPort(), sversion);

  // 3.根据易盛提供的前置机地址类型进行注册
  bool bFens = false;
  if (bFens) {
    //注册Fens前置地址（可注册多个），通过Fens获取可用行情服务器集合，Fens自动选择最优行情服务器
    pEQapi->RegisterFens("58.246.206.146", 16400);
  } else {
    //注册Front前置地址（可注册多个），通过Front直接接入行情服务器
    pEQapi->RegisterFront(spi.getIp().c_str(), spi.getPort());
  }

  std::cout << "#####################"
            << " : " << spi.getIp() << " : " << spi.getServerType()
            << std::endl;
  // 4.启动连接
  pEQapi->Init(spi.getServerType());

  std::cout << "&&" << std::endl;

  // 5.连接成功
  // 在OnFrontConnected中进行登录

  // 6.登录成功
  // 在 OnRspQuoteLogin 中进行查询和订阅请求

  printCurrentTime();

  // 等待应答和推送
  while (true) {
#ifdef _WIN32
    Sleep(3000);
#else
    sleep(3);
#endif
  };
  printf("end...\n");

  // 5.结束释放
  pEQapi->Release();

  return 0;
}
