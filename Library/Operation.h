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
	void init() {
		memset(numberID, '\0', sizeof(numberID));
		memset(operation, '\0', sizeof(operation));
		memset(date, '\0', sizeof(date));
	}
public:
	Operation();
	Operation(int id, string numberID, string operation, string date);
	//���ò�����id
	void setNumberID(string numberID);
	string getNumberID();
	//���ò�������
	void setOperation(string operation);
	string getOperation();
	//��������
	void setDate(string date);
	string getDate();
	bool save();
	//��ȡ���в��������ض����ַ���ǵ�delete��
	static vector<Operation*> getAllOperaions();
};