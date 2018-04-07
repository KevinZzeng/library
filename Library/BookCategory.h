#pragma once
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include "Dao.h"
using namespace std;
class BookCategory {
private:
	int ID;
	char category[40];
public:
	//����
	BookCategory(int ID=-1, string category="");
	//get set
	int getID();
	string getCategory();
	void setCategory(string category);
	void setID(int ID);
	//���������޸�һ������
	bool save();
	//ɾ��һ������
	bool destory();
	//�������е� <id,category> ǰ̨��
	static map<int, string> getAllCategory();
	//���ݷ������ֲ��ҷ���ID��û�ҵ�����-1
	static int getCategoryIdByName(string categoryName);
	//���ݷ���ID���ҷ������֣�û�ҵ�����""
	static string getCategoryNameByID(int ID);
};