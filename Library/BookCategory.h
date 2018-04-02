#pragma once
#include <string>
#include <map>
#include <vector>
#include "Dao.h"
using namespace std;
class BookCategory {
private:
	int ID;
	char category[40];
public:
	//����
	BookCategory();
	BookCategory(int ID, string category);
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

};