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
	//ɾ��������¼
	bool destory();
	static vector<CollectBook> getCollectionByNumberID(string numberID);


};