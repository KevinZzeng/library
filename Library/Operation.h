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
	//���ò�����id
	void setNumberID(string numberID);
	string getNumberID();
	//���ò�������
	void setOperation(string operation);
	string getOperation();
	//��������
	void setDate(string date);
	string getDate();
	bool save(Admin &ad);
	//��ȡ���в��������ض����ַ���ǵ�delete��
	static vector<Operation*> getAllOperaions();
};