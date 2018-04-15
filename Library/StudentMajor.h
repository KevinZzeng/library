#pragma once
#include <string>
#include "Dao.h"
using namespace std;
class StudentMajor {
private:
	int id;
	char major[50];
	void init() {
		memset(major, '\0', sizeof(major));
	}
public:
	StudentMajor();
	void setMajor(string major);
	string getMajor();
	void setId(int id);
	int getId();
	//��ѯ�����ڷ���-1
	static int getIDByMajor(string major);
	static string getMajorByID(int id);
	static map<int, string> getAllMajor();
	bool save();
	bool destory();
};