#include"Student.h"

//����setter �� getter
//login success Ӧ���������private ֵ������ʹ��
bool Student::login(string numberID, string password)
{
	/*��ȡ�û�������*/
	strcpy(this->numberID, numberID.c_str());
	strcpy(this->password, password.c_str());
	//�ж��Ƿ���ȷ����ѯ���ݿ�
	bool signin = false;


	if (signin) {
		setName
			return true;
	}
	else {
		return false;
	}
}

bool Student::save()
{
	return false;
}

bool Student::destory()
{
	return false;
}

vector<Book> Student::getInterestingBooks()
{
	return vector<Book>();
}

vector<string> Student::getMessages()
{
	return vector<string>();
}

void Student::setId(int id)
{
	this->id = id;
}

int Student::getId()
{
	return 0;
}

void Student::setNumberID(string numberID)
{
	strcpy(this->numberID, numberID.c_str());
}

string Student::getNumberID()
{
	return string(numberID);
}

void Student::setPassword(string password)
{
	strcpy(this->password, password.c_str());
}

string Student::getPassword()
{
	return string(password);
}

void Student::setName(string name)
{
	strcpy(this->name, name.c_str());
}

string Student::getName()
{
	return string(name);
}

void Student::setMajor(int major)
{
	this->major = major;
}

int Student::getMajor()
{
	return 0;
}

void Student::setPhoto(string photo)
{
	strcpy(this->photo, photo.c_str());
}

string Student::getPhoto()
{
	return string(photo);
}

void Student::setMoney(double money)
{
	this->money = money;
}

double Student::getMoney()
{
	return money;
}

void Student::setEmail(string email)
{
	strcpy(this->email, email.c_str());
}

string Student::getEmail()
{
	return string(email);
}

void Student::setStatus(status_class status)
{
	this->status = status;
}

status_class Student::getStatus()
{
	return status;
}
