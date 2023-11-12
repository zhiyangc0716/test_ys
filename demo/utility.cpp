#include "stdafx.h"
#include "utility.h"
#include <ctime>

#ifdef WIN32
#include <io.h>
#include <direct.h>
#define ACCESS _access
#define MKDIR _mkdir
#else
#include <unistd.h> 
#include <sys/types.h>  
#include <sys/stat.h>
#define ACCESS access
#define MKDIR mkdir
#endif

void printCurrentTime()
{
#ifdef _WIN32
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	printf("%4d/%02d/%02d %02d:%02d:%02d.%03d\n", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);
#else
	struct timeval tvnow;
	gettimeofday(&tvnow, NULL);
	auto mTime = std::chrono::milliseconds(tvnow.tv_sec * 1000);
	auto tp = std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>(mTime);
	auto tt = std::chrono::system_clock::to_time_t(tp);
	std::tm* now = std::localtime(&tt);
	printf("%4d-%02d-%02d %02d:%02d:%02d\n", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec);
#endif
}

// 20190521-16:06:00.058611
std::string getCurrentTime()
{
	char sRet[128] = {0};

#ifdef _WIN32
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	sprintf(sRet, "%4d%02d%02d-%02d:%02d:%02d.%06d", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds*1000);
#else
	struct timeval tvnow;
	gettimeofday(&tvnow, NULL);
	auto mTime = std::chrono::milliseconds(tvnow.tv_sec * 1000);
	auto tp = std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>(mTime);
	auto tt = std::chrono::system_clock::to_time_t(tp);
	std::tm* now = std::localtime(&tt);
	sprintf(sRet, "%4d%02d%02d-%02d:%02d:%02d.%06d", 
		now->tm_year + 1900, now->tm_mon + 1, now->tm_mday, 
		now->tm_hour, now->tm_min, now->tm_sec, 
		(int)tvnow.tv_usec);
#endif

	return sRet;
}

std::uint64_t getTimeStamp()
{
	std::uint64_t nRet = 0;

#ifdef _WIN32
	std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
	auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
	std::time_t timestamp = std::chrono::system_clock::to_time_t(tp);
	nRet = tmp.count()*1000;
#else
	struct timeval tvnow;
	gettimeofday(&tvnow, NULL);
	nRet = tvnow.tv_sec * 1000000 + (int)tvnow.tv_usec;
#endif

	return nRet;
}

// 取得日期时间的微秒数（从19000101-00:00:00开始）
// 20180719-00:00:00.000000
std::uint64_t getMicroByDateTime(const std::string& sDatetime)
{
	struct tm tm;
	memset(&tm, 0, sizeof(tm));
	int nMillc = 0;
	int nMicr = 0;
	sscanf(sDatetime.c_str(), "%4d%2d%2d-%d:%d:%d.%3d%3d",
		&tm.tm_year, &tm.tm_mon, &tm.tm_mday,
		&tm.tm_hour, &tm.tm_min, &tm.tm_sec,
		&nMillc, &nMicr);

	tm.tm_year -= 1900;
	tm.tm_mon--;
	return mktime(&tm) * 1000000 + nMillc * 1000 + nMicr;
}

bool createDir(const std::string& dir)
{
	bool bRet = false;

	if (ACCESS(dir.c_str(), 0) == -1)
	{
#ifdef WIN32  
		int flag = MKDIR(dir.c_str());
#else
		int flag = MKDIR(dir.c_str(), 0777);
#endif 
		if (flag == 0)
		{
			bRet = true;
		}
	}

	return bRet;
}

// trim from start 
std::string &ltrim(std::string &s) {
	string::size_type n = s.find_first_not_of(" \r\n\t");
	if (n != string::npos)
	{
		s.erase(0, n);
	}
	else
	{
		s = "";
	}
	return s;
}

// trim from end 
std::string &rtrim(std::string &s) {
	string::size_type n = s.find_last_not_of(" \r\n\t");
	if (n != string::npos)
	{
		s.erase(n + 1, s.size() - n);
	}
	else
	{
		s = "";
	}
	return s;
}

std::string &trim(std::string &s) {
	return ltrim(rtrim(s));
}

int stringsplit(const std::string& src, const std::string& separator,
	std::vector<std::string>& dest, bool btrim_all)
{
	dest.clear();

	string str = src;
	if (trim(str).size() <= 0)
		return 0;

	// 首先找到第一个非分隔符的位置
	auto it = str.find_first_not_of(separator, 0);
	if (it == string::npos)
	{
		return 0;
	}
	// 去除左边所有的分隔符
	str = str.substr(it);

	string substring;
	string::size_type start = 0, index = 0;

	do
	{
		index = str.find_first_of(separator, start);
		if (index != string::npos)
		{
			substring = str.substr(start, index - start);
			if (btrim_all) trim(substring);
			if (substring.size() > 0) dest.push_back(substring);
			start = str.find_first_not_of(separator, index);
		}
		else
		{
			//the last token
			substring = str.substr(start);
			if (btrim_all) trim(substring);
			if (substring.size() > 0) dest.push_back(substring);
			break;
		}
	} while (start != string::npos);

	return dest.size();
}