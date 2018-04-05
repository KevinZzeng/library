#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include "Book.h"
#include "Dao.h"
#include "md5.h"
#include "BorrowInfo.h"
#include "Utils.h"
using namespace std;
enum status_class {
	Student_NORMAL, Student_LOCK
};
//每次登陆成功后应该计算用户的欠费信息，更新借阅历史的信息的状态
class Student {
private:
	int id;
	char numberID[13];
	char password[33];
	char name[50];
	int major;
	char photo[200];
	//一天一元计算公式
	int money;
	char email[30];
	status_class status;
public:
	//各种setter 、 getter
	Student();
	Student(int id, string numberID, string password, string name, int major, string photo, int money, string email, status_class status);
	void setId(int id);
	int getId();
	void setNumberID(string numberID);
	string getNumberID();
	void setPassword(string password);
	void setName(string name);
	string getName();
	void setMajor(int major);
	int getMajor();
	void setPhoto(string photo);
	string getPhoto();
	void setMoney(int money);
	int getMoney();
	void setEmail(string email);
	string getEmail();
	void setStatus(status_class status);
	status_class getStatus();
	//login success 应该填充其他private 值，方便使用
	bool login(string numberID, string password);
	//获取学生信息，不需要参数则填入""或者-1
	static vector<Student> getStudent(string name, string numberID, int major);
	//修改个人信息，操作数据库，已存在用户save返回false
	bool save();
	bool destory();
	vector<Book> getInterestingBooks();
	//获取消息提醒
	vector<string> getMessages();



};