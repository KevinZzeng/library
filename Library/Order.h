#pragma once
#include <string>
#include <vector>
using namespace std;
class Order {
private:
	int id;
	string ISBN;
	string numberID;
	string oder_date;
	string deadline;
	//ԤԼ�У� BEGIN  ��ԤԼ�� CAN  �����:DONE
	enum {BEING, CAN, DONE}status;
public:
	bool save();
	bool destory();
	static vector<Order> getOrdersByNumberID(string number);

};