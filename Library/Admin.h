#pragma once
#include <string>
#include "Student.h"
using namespace std;
class Admin {
private:
	char numberID[13];
	char password[33];
	char email[30];
public:
	Admin(string numberID, string password, string email);
	Admin();
	bool login(string numberID, string password);
	bool save();
	void setEmail(string email);
	string getEmail();
	bool addStudent(Student &stu);
	bool addAdmin(Admin &admin);
	static Student getStudentByID(string numebrID);
	static vector<Student> getStudentsByName(string name, int major);




};