#include"Student.h"

//各种setter 、 getter
//login success 应该填充其他private 值，方便使用
bool Student::login(string numberID, string password)
{
	/*获取用户名密码*/
	strcpy(this->numberID, numberID.c_str());
	strcpy(this->password, password.c_str());
	//判断是否正确，查询数据库
	//构造查询参数
	MD5 password_md5 = MD5(password);
	strcpy(this->password, (char*)password_md5.getDigest());
	vector<pair<int, char*> > v;
	v.push_back(make_pair(0, this->numberID));
	v.push_back(make_pair(1, this->password));
	Dao dao;
	vector<map<int, char *>> studentInfo = dao.select("Student", v);
	//查询到对应学生
	if (!studentInfo.empty()) {
		map<int, char*> student = studentInfo[0];
		//填充对应信息
		strcpy(this->name, student[2]);
		this->major = reinterpret_cast<int> (student[3]);
		strcpy(this->photo, student[4]);
		this->money = reinterpret_cast<int> (student[5]);
		strcpy(this->email, student[6]);
		this->status = (status_class)reinterpret_cast<int> (student[8]);
		//查询图书情况
		BorrowInfo borrowInfo;
		borrowInfo.getInfoByNumberID(numberID, );
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
