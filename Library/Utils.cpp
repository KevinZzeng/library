#include "Utils.h"
#include <ctime>
bool isLeap(int y)//判断是否是闰年  
{
	return y % 4 == 0 && y % 100 != 0 || y % 400 == 0;//真返回为1，假为0  
}
int daysOfMonth(int y, int m)
{
	int day[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (m != 2)
		return day[m - 1];
	else
		return 28 + isLeap(y);
}
int daysOfDate(int y,int m,int d)//计算一共的天数  
{
	int days = d;
	for (int y1 = 2018; y1<y; y++)//计算年  
		days += 365 + isLeap(y);
	for (int m1 = 1; m1<m; m++)//计算月  
		days += daysOfMonth(y, m);
	//days+=d.d;  
	return days;
}
bool correctTime(int y, int m, int d) {
	if (d > 31 || m > 12) {
		return false;
	}
	else if(d == 31 && (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)) {
		return true;
	}
	else if (d == 30 && (m == 4 || m == 6 || m == 9 || m == 11)) {
		return true;
	}
	else if (d == 28 && m == 2 && !isLeap(y)) {
		return true;
	}
	else if (d == 29 && m == 2 && isLeap(y)) {
		return true;
	}
	else {
		return false;
	}
}
string Utils::getNowTime()
{
	struct tm t;   //tm结构指针
	time_t timep;
	time(&timep);
	localtime_s(&t, &timep);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d", &t);
	return string(tmp);
}

string Utils::addTime(string time, int day)
{
	int n_y, n_m, n_d;
	n_y = Utils::fromString<int>(time.substr(0, 4));
	n_m = Utils::fromString<int>(time.substr(4, 6));
	n_d = Utils::fromString<int>(time.substr(6, 8));
	n_d += day;
	while (!correctTime(n_y, n_m, n_d)) {
		if (n_m > 12) {
			n_m -= 12;
			n_y += 1;
			continue;
		}
		if (n_m == 1 || n_m == 3 || n_m == 5 || n_m == 7 || n_m == 8 || n_m == 10 || n_m == 12) {
				n_d -= 31;
				n_m += 1;
		}
		else if (n_m == 4 || n_m == 6 || n_m == 9 || n_m == 11) {
			n_d -= 30;
			n_m += 1;
		}
		else if (n_m == 2 && isLeap(n_y)) {
			n_d -= 29;
			n_m += 1;
		}
		else {
			n_d -= 28;
			n_m += 1;
		}
	}
	string t_y, t_m, t_d;
	t_y = Utils::toString(n_y);
	t_m = Utils::toString(n_m);
	t_d = Utils::toString(n_d);
	if (n_m < 10) {
		t_m = "0" + t_m;
	}
	if (n_d < 10) {
		t_d = "0" + t_d;
	}
	string t_time = t_y + "-" + t_m + "-" + t_d;
	return t_time;
}

int Utils::compareTime(string nowtime, string targetTime)
{
	int n_y, n_m, n_d, t_y, t_m, t_d;
	n_y = Utils::fromString<int>(nowtime.substr(0, 4));
	n_m = Utils::fromString<int>(nowtime.substr(4, 6));
	n_d = Utils::fromString<int>(nowtime.substr(6, 8));
	t_y = Utils::fromString<int>(nowtime.substr(0, 4));
	t_m = Utils::fromString<int>(nowtime.substr(4, 6));
	t_d = Utils::fromString<int>(nowtime.substr(6, 8));
	int day1 = daysOfDate(n_y, n_m, n_d);
	int day2 = daysOfDate(t_y, t_m, t_d);
	return day1 - day2;
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


