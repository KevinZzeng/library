#pragma once
#include <string>
#include <sstream>
#include <set>
using namespace std;
class Utils {

public:
	//����ת�ַ���
	template<typename T>
	static string toString(const T &v);

	//�ַ���ת����
	template<typename T>
	static T fromString(const string &str);


	//ʱ����� yyyy-MM-dd xx:xx:xx
	static string getNowTime();


	//�����󽻼�,�������A��
	static void setIntersection(set<int> &a, const set<int> &b);

	//�ͷ�new�ռ�
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
		delete ptr;
		ptr = NULL;
	}
}
