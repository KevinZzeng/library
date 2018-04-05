#pragma once
#include <string>
#include "Student.h"
using namespace std;
class Admin {
private:
	int id;
	char numberID[13];
	char password[33];
	char email[30];
public:
	Admin(string numberID, string password, string email);
	Admin();
	bool login(string numberID, string password);
	//已存在用户返回false
	bool save();
	void setId(int id);
	int getId();
	void setNumberID(string numberID);
	string getNumberID();
	void setPassword(string password);
	void setEmail(string email);
	string getEmail();
	bool addStudent(Student &stu);
	bool addAdmin(Admin &admin);
	static Student getStudentByID(string numebrID);
	//不要其中一个参数请置为""或-1
	static vector<Student> getStudentsByName(string name, int major);




};