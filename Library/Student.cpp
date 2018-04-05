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
	strcpy(this->password, password_md5.toStr32().c_str());
	vector<pair<int, char*> > v;
	v.push_back(make_pair(0, this->numberID));
	v.push_back(make_pair(1, this->password));
	Dao dao;
	vector<map<int, char *>> studentInfo = dao.select("users", v);
	//查询到对应学生
	if (!studentInfo.empty()) {
		map<int, char*> student = studentInfo[0];
		//填充对应信息
		this->id = *(reinterpret_cast<int*>(student[-1]));
		strcpy(this->name, student[2]);
		this->major = *(reinterpret_cast<int*> (student[3]));
		strcpy(this->photo, student[4]);
		this->money = *(reinterpret_cast<int*> (student[5]));
		//获取书籍过期信息，重置money
		vector<BorrowInfo> vb = BorrowInfo::getInfoByNumberID(numberID, Book_EXCEED);
		//获取时间比较
		vector<BorrowInfo>::iterator it;
		for (it = vb.begin(); it < vb.end(); it++) {
			int exceedDays = Utils::compareTime(Utils::getNowTime(), it->getR_date());
			this->money += exceedDays;
		}
		//更新信息
		save();
		strcpy(this->email, student[6]);
		this->status = (status_class)*(reinterpret_cast<int*> (student[8]));

		return true;
	}
	else {
		return false;
	}
}

vector<Student> Student::getStudent(string name, string numberID, int major)
{
	Dao dao;
	char names[50];
	int majors;
	char numberIDs[13];
	vector<pair<int, char*> > v;
	vector<map<int, char *>> studentInfo1, studentInfo2, studentInfo3;
	//根据参数不同获取
	if (name != "") {
		strcpy(names, name.c_str());
		v.push_back(make_pair(2, names));
		studentInfo1 = dao.select("users", v);
	}
	if (numberID != "") {
		strcpy(numberIDs, numberID.c_str());
		v.push_back(make_pair(0, numberIDs));
		studentInfo2 = dao.select("users", v);
	}
	if (major != -1) {
		v.push_back(make_pair(3, reinterpret_cast<char*>(&majors)));
		studentInfo3 = dao.select("users", v);
	}
	//合并各参数查询结果
	vector<map<int, char *>>::iterator it;
	for (it = studentInfo2.begin(); it != studentInfo2.end(); it++) {
		studentInfo1.push_back((*it));
	}
	for (it = studentInfo3.begin(); it != studentInfo3.end(); it++) {
		studentInfo1.push_back((*it));
	}
	//生成studentList返回
	vector<Student> studentList;
	for (it = studentInfo1.begin(); it != studentInfo1.end(); it++) {
		Student s;
		s.setId(*(reinterpret_cast<int*>((*it)[-1])));
		s.setNumberID(string((*it)[0]));
		s.setPassword(string((*it)[1]));
		s.setName(string((*it)[2]));
		s.setMajor(*(reinterpret_cast<int*>((*it)[3])));
		s.setPhoto(string((*it)[4]));
		s.setMoney(*(reinterpret_cast<int*>((*it)[5])));
		s.setEmail(string((*it)[6]));
		s.setStatus((status_class)*(reinterpret_cast<int*>((*it)[7])));
		studentList.push_back(s);
	}
	return studentList;
}

bool Student::save()
{
	Dao dao;
	vector<char *> insertInfo;
	//构造参数
	insertInfo.push_back(numberID);
	insertInfo.push_back(password);
	insertInfo.push_back(name);
	insertInfo.push_back(reinterpret_cast<char*>(&major));
	insertInfo.push_back(photo);
	insertInfo.push_back(reinterpret_cast<char*>(&money));
	insertInfo.push_back(email);
	insertInfo.push_back(reinterpret_cast<char*>(&status));
	//存入数据库
	bool ifSuccess = true;
	vector<Student> stuList = Student::getStudent("", "test", -1);
	if (stuList.empty()) {
		try {
			//增加
			if (id == -1) {
				dao.insert_into("users", insertInfo);
			}
			//更新
			else {
				dao.update("users", id, insertInfo);
			}
		}
		catch (exception e) {
			ifSuccess = false;
		}
	}
	else {
		ifSuccess = false;
	}

	return ifSuccess;
}

bool Student::destory()
{
	if (id == -1)
		return false;
	else {
		Dao dao;
		dao.delete_from("users", id);
		return true;
	}
}

vector<Book> Student::getInterestingBooks()
{
	//获取以往借阅书籍的ISBN
	vector<BorrowInfo> vb = BorrowInfo::getHistoryInfoByNumberID(string(numberID));
	vector<BorrowInfo>::iterator iter;
	//遍历通过ISBN获取category，通过category获取同类书籍
	vector<Book> interestingBook;
	for (iter = vb.begin(); iter != vb.end(); iter++) 
	{
		//拼接vector
		vector<Book> interestingBook_temp = Book::getBooksByCategory((Book::getBookByISBN((*iter).getISBN_ID())).getCategory());
		interestingBook.insert(interestingBook.end(), interestingBook_temp.begin(), interestingBook_temp.end());
	}
	return interestingBook;
}

vector<string> Student::getMessages()
{
	//查询图书情况
	vector<BorrowInfo> vb = BorrowInfo::getInfoByNumberID(numberID, Book_EXCEED);
	vector<string> result;
	//返回到期图书
	if (!vb.empty()) 
	{
		string bookInfo = "有" + to_string(vb.size()) + "本图书已到期！";
		result.push_back(bookInfo);
	}
	return result;
}

Student::Student()
{
}

Student::Student(int id, string numberID, string password, string name, int major, string photo, int money, string email, status_class status)
{
	setId(id);
	setNumberID(numberID);
	setPassword(password);
	setName(name);
	setMajor(major);
	setPhoto(photo);
	setMoney(money);
	setEmail(email);
	setStatus(status);
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
	MD5 password_md5 = MD5(password);
	strcpy(this->password, password_md5.toStr32().c_str());
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
	return major;
}

void Student::setPhoto(string photo)
{
	strcpy(this->photo, photo.c_str());
}

string Student::getPhoto()
{
	return string(photo);
}

void Student::setMoney(int money)
{
	this->money = money;
}

int Student::getMoney()
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
