#include "Utils.h"
#include <ctime>
string Utils::getNowTime()
{
	struct tm t;   //tmΩ·ππ÷∏’Î
	time_t timep;
	time(&timep);
	localtime_s(&t, &timep);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", &t);
	return tmp;
}

void Utils::setIntersection(set<int>& a, const set<int>& b)
{
	set<int> res;
	set<int>::iterator it = a.begin();
	while (it != a.end()) {
		if (b.find(*it) != b.end()) res.insert(*it);
		it++;
	}
	a = res;
}


