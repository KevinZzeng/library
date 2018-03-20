#pragma once
#include <string>
using namespace std;
class StudentMajor {
private:
	int id;
	char major[50];
public:
	void setMajor(string major);
	string getMajor();
	int getId();
	int getIDByMajor(string major);
	bool save();
	bool destory();
};