#include "Admin.h"

Admin::Admin(string numberID, string password, string email)
{
	strcpy(this->numberID, numberID.c_str());
	strcpy(this->password, password.c_str());
	strcpy(this->email, email.c_str());
}

Admin::Admin()
{
}

bool Admin::login(string numberID, string password)
{
	return false;
}

bool Admin::save()
{
	return false;
}

void Admin::setEmail(string email)
{
	strcpy(this->email, email.c_str());
}

string Admin::getEmail()
{
	return string(email);
}

bool Admin::addStudent(Student & stu)
{
	return false;
}

bool Admin::addAdmin(Admin & admin)
{
	return false;
}

Student Admin::getStudentByID(string numebrID)
{
	return Student();
}

vector<Student> Admin::getStudentsByName(string name, int major)
{
	return vector<Student>();
}
