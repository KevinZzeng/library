#include<iostream>
#include"Admin.h"
#include"StudentMajor.h"
#include"Operation.h"
#include"Order.h"
#include"Student.h"
int main() {
	bool flag;
	string date = Utils::getNowTime();
	string deadline = Utils::addTime(date, 30);
	Order op(-1, "admin", "test", date, deadline, BEING);
	flag = op.save();
	if (!flag) {
		cout << "插入失败" << endl;
	}
	else {
		cout << "插入成功！" << endl;
	}
	vector<Order*> vp = Order::getOrdersByNumberID("test");
	vector<Order*>::iterator it;
	for (it = vp.begin(); it != vp.end(); it++) {
		cout << (*it)->getNumberID() << endl;
	}
	return 0;
}