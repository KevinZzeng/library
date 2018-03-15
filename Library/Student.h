#pragma once
#include <vector>
#include "Book.h"
using namespace std;

//每次登陆成功后应该计算用户的欠费信息，更新借阅历史的信息的状态
class Student {
private:
	string numberID;
	string password;
	string name;
	int major;
	string photo;
	//一天一元计算公式
	double money;
	string emil;
	enum { 
		NORMAL,LOCK
	}status;
public:
	//各种setter 、 getter
	//login success 应该填充其他private 值，方便使用
	bool login();
	//修改个人信息，操作数据库
	bool save();
	bool destory();
	vector<Book> getInterestingBooks();
	//获取消息提醒
	vector<string> getMessages();




};