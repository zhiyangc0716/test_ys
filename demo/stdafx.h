// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#ifndef __TEST_ESUNNY_QUOTE_STDAFX_SECTION__
#define __TEST_ESUNNY_QUOTE_STDAFX_SECTION__

#include "targetver.h"
#include <stdio.h>


// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
#ifdef _WIN32
#include <windows.h>
#include <tchar.h>
#else
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#endif  // _WIND32


// ����64λ����
#if defined(_WIN32) && !defined(CYGWIN)
typedef __int64 int64_t;
#else
typedef long long int64t;
#endif  // _WIN32

#endif