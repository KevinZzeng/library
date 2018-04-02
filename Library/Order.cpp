#include "Order.h"

Order::Order()
{
}

Order::Order(string ISBN, string numberID, string order_date, string deadline)
{
	strcpy(this->ISBN, ISBN.c_str());
	strcpy(this->numberID, numberID.c_str());
	strcpy(this->oder_date, order_date.c_str());
	strcpy(this->deadline, deadline.c_str());
}

void Order::setISBN(string ISBN)
{
	strcpy(this->ISBN, ISBN.c_str());
}

string Order::getISBN()
{
	return string(ISBN);
}

void Order::setNumberID(string numberID)
{
	strcpy(this->numberID, numberID.c_str());
}

string Order::getNumberID()
{
	return string(numberID);
}

void Order::setorder_date(string order_date)
{
	strcpy(this->oder_date, order_date.c_str());
}

string Order::getOrder_date()
{
	return string(oder_date);
}

void Order::setDeadline(string deadline)
{
	strcpy(this->deadline, deadline.c_str());
}

string Order::getDeadline()
{
	return string(deadline);
}

void Order::setStatus(status_order status)
{
	this->status = status;
}

status_order Order::getStatus()
{
	return status;
}

bool Order::save()
{
	Dao dao;
	vector<char*> v;
	//�����������
	v.push_back(ISBN);
	v.push_back(numberID);
	v.push_back(oder_date);
	v.push_back(deadline);
	bool ifSuccess = true;
	try {
		if (id == -1) {
			dao.insert_into("order", v);
		}
		else {
			dao.update("order", id, v);
		}
	}
	catch (exception e) {
		ifSuccess = false;
	}
	return 	ifSuccess;
}

bool Order::destory()
{
	Dao dao;
	return dao.delete_from("order", id);
}

vector<Order*> Order::getOrdersByNumberID(string number)
{
	Dao dao;
	//�����ѯ����
	vector<pair<int, char*>> v;
	//���ؽ��
	vector<map<int, char*>> v_result = dao.select("operation", v);
	//���췵�ض���
	vector<Order*> v_order;
	vector<map<int, char*>>::iterator iter;
	for (iter = v_result.begin(); iter != v_result.end(); iter++) {
		v_order.push_back(new Order((*iter)[-1], (*iter)[-1], (*iter)[-1], (*iter)[-1]));
	}

	return v_order;
}
