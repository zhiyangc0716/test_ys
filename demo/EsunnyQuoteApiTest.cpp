// EsunnyQuoteApiTest.cpp : �������̨Ӧ�ó������ڵ㡣
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

  // 1.����APIʵ��
  CEsunnyQuoteApi* pEQapi = CEsunnyQuoteApi::CreateEsunnyQuoteApi();

  // 2.ע��ص�
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
    // ���ؽ���udp������Ϣ������ip�������豸�������ݱ���ip���ã�
    interface_addr = argv[6];
    spi.setInterface_addr(interface_addr);
  }
  if (argc >= 8) {
    spi.setExchangeID(argv[7]);
  }
  if (argc >= 9) {
    spi.setInstrumetID(argv[8]);
  }

  //��ȡ��ǰApi�汾��Ϣ
  const char* sversion = pEQapi->GetVersion();
  printf("connect to server ip:%s, port:%d %s\n", spi.getIp().c_str(),
         spi.getPort(), sversion);

  // 3.������ʢ�ṩ��ǰ�û���ַ���ͽ���ע��
  bool bFens = false;
  if (bFens) {
    //ע��Fensǰ�õ�ַ����ע��������ͨ��Fens��ȡ����������������ϣ�Fens�Զ�ѡ���������������
    pEQapi->RegisterFens("58.246.206.146", 16400);
  } else {
    //ע��Frontǰ�õ�ַ����ע��������ͨ��Frontֱ�ӽ������������
    pEQapi->RegisterFront(spi.getIp().c_str(), spi.getPort());
  }

  std::cout << "#####################"
            << " : " << spi.getIp() << " : " << spi.getServerType()
            << std::endl;
  // 4.��������
  pEQapi->Init(spi.getServerType());

  std::cout << "&&" << std::endl;

  // 5.���ӳɹ�
  // ��OnFrontConnected�н��е�¼

  // 6.��¼�ɹ�
  // �� OnRspQuoteLogin �н��в�ѯ�Ͷ�������

  printCurrentTime();

  // �ȴ�Ӧ�������
  while (true) {
#ifdef _WIN32
    Sleep(3000);
#else
    sleep(3);
#endif
  };
  printf("end...\n");

  // 5.�����ͷ�
  pEQapi->Release();

  return 0;
}
