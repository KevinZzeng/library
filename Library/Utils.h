#pragma once
#include <string>
#include <sstream>
#include <set>
using namespace std;
class Utils {

public:
	//类型转字符串
	template<typename T>
	static string toString(const T &v);

	//字符串转类型
	template<typename T>
	static T fromString(const string &str);


	//时间操作 yyyy-MM-dd xx:xx:xx
	static string getNowTime();


	//集合求交集,结果放在A中
	static void setIntersection(set<int> &a, const set<int> &b);

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
