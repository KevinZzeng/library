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
		cout << "����ʧ��" << endl;
	}
	else {
		cout << "����ɹ���" << endl;
	}
	Student stu;
	flag = stu.login("test", "stdsf");
	if (!flag) {
		cout << "����ʧ��" << endl;
	}
	else {
		cout << "�����ɹ���" << endl;
	}
	return 0;
}