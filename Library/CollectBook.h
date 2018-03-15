#pragma once
#include <string>
#include <vector>
using namespace std;
class CollectBook {

private:
	int id;
	string numebrID;
	string ISBN;

public:
	bool save();
	//É¾³ý±¾Ìõ¼ÇÂ¼
	bool destory();
	static vector<CollectBook> getCollectionByNumberID(string numberID);


};