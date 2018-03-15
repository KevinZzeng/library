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
