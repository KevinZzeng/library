#pragma once
#include <string>
#include <vector>
#include "Dao.h"
using namespace std;
enum status_order { BEING, CAN, DONE };
class Order {
private:
	int id;
	char ISBN[20];
	char numberID[13];
	char oder_date[20];
	char deadline[20];
	//预约中： BEGIN  可预约： CAN  已完成:DONE
	status_order status;
public:
	Order();
	Order(string ISBN, string numberID, string order_date, string deadline);
	void setISBN(string ISBN);
	string getISBN();
	void setNumberID(string numberID);
	string getNumberID();
	void setorder_date(string order_date);
	string getOrder_date();
	void setDeadline(string deadline);
	string getDeadline();
	void setStatus(status_order status);
	status_order getStatus();
	bool save();
	bool destory();
	static vector<Order*> getOrdersByNumberID(string number);

};