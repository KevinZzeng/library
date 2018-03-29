#include "Utils.h"
#include <ctime>
#include <algorithm>
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

void Utils::getIntersection(vector <int>& a, vector<int>& b)
{
	vector<int> res;
	sort(b.begin(), b.end());
	vector<int>::iterator it = a.begin();
	while (it != a.end()) {
		if (binary_search(b.begin(), b.end(), *it)) res.push_back(*it);
		it++;
	}
	a = res;
}


