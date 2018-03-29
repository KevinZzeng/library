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

public:
	//构造函数
	CollectBook();
	CollectBook(int ID, string numberID, string ISBN);
	//get set
	int getID();
	string getNumberID();
	string getISBN();
	void setID(int ID);
	void setNumberID(string numberID);
	void setISBN(string ISBN);
	//insert或者update收藏记录
	bool save();
	//删除本条记录
	bool destory();
	//通过学号获取该学号预约的书籍
	static vector<CollectBook> getCollectionByNumberID(string numberID);


};