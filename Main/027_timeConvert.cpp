
#include <iostream>
#include <ctime>
#include <cstring>
#include <cstdio>

using namespace std;

int main()
{
	const char * timeChar = "2018-01-31T23:00:00+0800";

	cout<<timeChar<<endl;

	tm tm_struct;
	int year, month, day, hour, minute, second;
	sscanf(timeChar, "%d-%d-%dT%d:%d:%d+0800", &year, &month, &day, &hour, &minute, &second);

	tm_struct.tm_year = year - 1900;
	tm_struct.tm_mon = month - 1;
	tm_struct.tm_mday = day;
	tm_struct.tm_hour = hour;
	tm_struct.tm_min = minute;
	tm_struct.tm_sec = second;
	tm_struct.tm_isdst = 0;
	time_t time_normal = mktime(&tm_struct);

	cout<<time_normal<<endl;

	return 0;
}

time_t ConvertToDatetime(const char* str)
{
	const char *timeChar = str;
	tm tm_struct;																			// 定义tm结构体
	int year, month, day, hour, minute, second;												// 定义时间的临时变量
	sscanf(timeChar, "%d-%d-%dT%d:%d:%d+0800", &year, &month, &day, &hour, &minute, &second);	// 将NCString存储的日期时间，转换int临时变量

	tm_struct.tm_year = year -1900;				// 年, 由于tm时间结构体的年份存储的是从1900年开始的时间，所以tm_year为int临时变量减去1900
	tm_struct.tm_mon = month - 1;				// 月, 由于tm时间结构体的月份存储范围为0-11, 所以tm_mon为int临时变量减去1
	tm_struct.tm_mday = day;					// 日
	tm_struct.tm_hour = hour;					// 时
	tm_struct.tm_min = minute;					// 分
	tm_struct.tm_sec = second;					// 秒
	tm_struct.tm_isdst = 0;						// 非夏令时
	time_t time_Normal = mktime(&tm_struct);	// 将tm结构体转换为time_t格式
	return time_Normal;
}
