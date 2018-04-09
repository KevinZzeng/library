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
	//构造函数
	CollectBook(int ID=-1, string numberID="", string ISBN="");
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