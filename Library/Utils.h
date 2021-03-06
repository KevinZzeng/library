#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;
class Utils {

public:
	//类型转字符串
	template<typename T>
	static string toString(const T &v);

	//字符串转类型
	template<typename T>
	static T fromString(const string &str);

	//时间操作 yyyy-MM-dd
	static string getNowTime();
	static string addTime(string time, int day);
	static int compareTime(string nowtime, string targetTime);
	static string getSpecificTime();
	
	//集合求交集,结果放在A中
	static void getIntersection(vector<int> &a, vector<int> &b);

	//释放new空间
	template<typename T>
	static void freeSpace(T * ptr);

};

template<typename T>
inline string Utils::toString(const T & v)
{
	ostringstream os;
	os << v;
	return os.str();
}

template<typename T>
inline T Utils::fromString(const string & str)
{
	istringstream is(str);
	T v;
	is >> v;	
	return v;
}

template<typename T>
inline void Utils::freeSpace(T * ptr)
{
	if (ptr) {
		delete[] ptr;
		ptr = NULL;
	}
}
