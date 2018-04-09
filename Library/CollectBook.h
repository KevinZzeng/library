#pragma once
#include <string>
#include <vector>
#include "Dao.h"
using namespace std;
class CollectBook {

private:
	int ID;
	char numberID[13];
	char ISBN[35];
	void init() {
		memset(numberID, '\0', sizeof(numberID));
		memset(ISBN, '\0', sizeof(ISBN));
	}
public:
	//���캯��
	CollectBook(int ID=-1, string numberID="", string ISBN="");
	//get set
	int getID();
	string getNumberID();
	string getISBN();
	void setID(int ID);
	void setNumberID(string numberID);
	void setISBN(string ISBN);
	//insert����update�ղؼ�¼
	bool save();
	//ɾ��������¼
	bool destory();
	//ͨ��ѧ�Ż�ȡ��ѧ��ԤԼ���鼮
	static vector<CollectBook> getCollectionByNumberID(string numberID);


};