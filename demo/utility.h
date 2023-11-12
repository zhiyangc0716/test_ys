#ifndef __TEST_ESUNNY_QUOTE_UTILITY_SECTION__
#define __TEST_ESUNNY_QUOTE_UTILITY_SECTION__

#include <vector>
#include <chrono>
#include <time.h>
#include <string>
#include "EsunnyQuoteApiDataType.h"

using namespace esunny_quote_api;
using namespace std;

#ifdef _WIN32
const std::string PATH_SEPARATOR = "\\";
#define ESSTRCMP _stricmp
#else
const std::string PATH_SEPARATOR = "/";
#define ESSTRCMP strcasecmp
#endif  

// 通用分隔符
const std::string sDivideSymbol = "|";

void printCurrentTime();
std::string getCurrentTime();
std::uint64_t getTimeStamp();
// 取得日期时间的微秒数（从19000101-00:00:00开始）
// 20180719-00:00:00.000000
std::uint64_t getMicroByDateTime(const std::string& sDatetime);

bool createDir(const std::string& dir);

std::string &ltrim(std::string &s);
std::string &rtrim(std::string &s);
std::string &trim(std::string &s);

int stringsplit(const std::string& src, const std::string& separator,
	std::vector<std::string>& dest, bool btrim_all = true);

#endif