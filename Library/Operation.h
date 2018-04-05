#pragma once
#include <string>
#include <vector>
#include "Admin.h"
using namespace std;
class Operation {

private:
	int id;
	char numberID[13];
	char operation[200];
	char date[20];
public:
	Operation();
	Operation(int id, string numberID, string operation, string date);
	//设置操作者id
	void setNumberID(string numberID);
	string getNumberID();
	//设置操作名称
	void setOperation(string operation);
	string getOperation();
	//设置日期
	void setDate(string date);
	string getDate();
	bool save();
	//获取所有操作，返回对象地址（记得delete）
	static vector<Operation*> getAllOperaions();
};