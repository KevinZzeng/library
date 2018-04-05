#include<iostream>
#include"Admin.h"
#include"StudentMajor.h"
#include"Operation.h"
#include"Order.h"
#include"Student.h"
int main() {
	bool flag;	
	vector<Student> stuList = Student::getStudent("", "test", -1);
	stuList[0].destory();
	Student newstu(-1, "test", "stdsf", "666", 1, "55", 1, "qqcom", Student_NORMAL);
	flag = newstu.save();
	if (!flag) {
		cout << "插入失败" << endl;
	}
	else {
		cout << "插入成功！" << endl;
	}
	Student stu;
	flag = stu.login("test", "stdsf");
	if (!flag) {
		cout << "操作失败" << endl;
	}
	else {
		cout << "操作成功！" << endl;
	}
	return 0;
}