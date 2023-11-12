// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#ifndef __TEST_ESUNNY_QUOTE_STDAFX_SECTION__
#define __TEST_ESUNNY_QUOTE_STDAFX_SECTION__

#include "targetver.h"
#include <stdio.h>


// TODO:  在此处引用程序需要的其他头文件
#ifdef _WIN32
#include <windows.h>
#include <tchar.h>
#else
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#endif  // _WIND32


// 定义64位整形
#if defined(_WIN32) && !defined(CYGWIN)
typedef __int64 int64_t;
#else
typedef long long int64t;
#endif  // _WIN32

#endif