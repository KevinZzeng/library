#pragma once
#include <string>
#include "Dao.h"
using namespace std;
class StudentMajor {
private:
	int id;
	char major[50];
public:
	void setMajor(string major);
	string getMajor();
	void setId(int id);
	int getId();
	//查询不存在返回-1
	static int getIDByMajor(string major);
	bool save();
	bool destory();
};