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
	//预约中： BEGIN  可预约： CAN  已完成:DONE
	enum {BEING, CAN, DONE}status;
public:
	bool save();
	bool destory();
	static vector<Order> getOrdersByNumberID(string number);

};