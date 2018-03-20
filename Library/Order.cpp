#include "Order.h"

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
	return false;
}

bool Order::destory()
{
	return false;
}

vector<Order> Order::getOrdersByNumberID(string number)
{
	return vector<Order>();
}
