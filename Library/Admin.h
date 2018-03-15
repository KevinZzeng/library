#pragma once
#include <string>
#include "Student.h"
using namespace std;
class Admin {
private:
	string numberID;
	string password;
	string email;
public:
	bool login();
	bool save();
	
	bool addStudent(Student &stu);
	bool addAdmin(Admin &admin);
	static Student getStudentByID(string numebrID);
	static vector<Student> getStudentsByName(string name,int major);
	



};