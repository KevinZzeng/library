#include"Student.h"

//����setter �� getter
//login success Ӧ���������private ֵ������ʹ��
bool Student::login(string numberID, string password)
{
	/*��ȡ�û�������*/
	strcpy(this->numberID, numberID.c_str());
	strcpy(this->password, password.c_str());
	//�ж��Ƿ���ȷ����ѯ���ݿ�
	//�����ѯ����
	MD5 password_md5 = MD5(password);
	strcpy(this->password, (char*)password_md5.getDigest());
	vector<pair<int, char*> > v;
	v.push_back(make_pair(0, this->numberID));
	v.push_back(make_pair(1, this->password));
	Dao dao;
	vector<map<int, char *>> studentInfo = dao.select("users", v);
	//��ѯ����Ӧѧ��
	if (!studentInfo.empty()) {
		map<int, char*> student = studentInfo[0];
		//����Ӧ��Ϣ
		strcpy(this->name, student[2]);
		this->major = reinterpret_cast<int> (student[3]);
		strcpy(this->photo, student[4]);
		this->money = reinterpret_cast<int> (student[5]);
		//��ȡ�鼮������Ϣ������money
		vector<BorrowInfo> vb = BorrowInfo::getInfoByNumberID(numberID, Book_EXCEED);
		//��ȡʱ��Ƚ�
		vector<BorrowInfo>::iterator it;
		for (it = vb.begin(); it < vb.end(); it++) {
			int exceedDays = Utils::compareTime(Utils::getNowTime(), it->getR_date());
			this->money += exceedDays;
		}
		//������Ϣ
		save();
		strcpy(this->email, student[6]);
		this->status = (status_class)reinterpret_cast<int> (student[8]);

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
		v.push_back(make_pair(3, reinterpret_cast<char*>(majors)));
		studentInfo3 = dao.select("users", v);
	}
	vector<map<int, char *>>::iterator it;
	for (it = studentInfo2.begin(); it != studentInfo2.end(); it++) {
		studentInfo1.push_back((*it));
	}
	for (it = studentInfo3.begin(); it != studentInfo3.end(); it++) {
		studentInfo1.push_back((*it));
	}
	vector<Student> studentList;
	for (it = studentInfo1.begin(); it != studentInfo1.end(); it++) {
		Student s;
		s.setId(reinterpret_cast<int>((*it)[-1]));
		s.setNumberID(string((*it)[0]));
		s.setPassword(string((*it)[1]));
		s.setName(string((*it)[2]));
		s.setMajor(reinterpret_cast<int>((*it)[3]));
		s.setPhoto(string((*it)[4]));
		s.setMoney(reinterpret_cast<int>((*it)[5]));
		s.setEmail(string((*it)[6]));
		s.setStatus((status_class)reinterpret_cast<int>((*it)[7]));
		studentList.push_back(s);
	}
	return studentList;
}

bool Student::save()
{
	Dao dao;
	vector<char *> insertInfo;
	//�������
	insertInfo.push_back(numberID);
	insertInfo.push_back(password);
	insertInfo.push_back(name);
	insertInfo.push_back(reinterpret_cast<char*>(major));
	insertInfo.push_back(photo);
	insertInfo.push_back(reinterpret_cast<char*>(money));
	insertInfo.push_back(email);
	insertInfo.push_back(reinterpret_cast<char*>(status));
	//�������ݿ�
	bool ifSuccess = true;
	try {
		//����
		if (id == -1) {
			dao.insert_into("users", insertInfo);
		}
		//����
		else {
			dao.update("users", id, insertInfo);
		}
	}
	catch (exception e) {
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
	//��ȡ���������鼮��ISBN
	vector<BorrowInfo> vb = BorrowInfo::getHistoryInfoByNumberID(string(numberID));
	vector<BorrowInfo>::iterator iter;
	//����ͨ��ISBN��ȡcategory��ͨ��category��ȡͬ���鼮
	vector<Book> interestingBook;
	for (iter = vb.begin(); iter != vb.end(); iter++) 
	{
		//ƴ��vector
		vector<Book> interestingBook_temp = Book::getBooksByCategory((Book::getBookByISBN((*iter).getISBN_ID())).getCategory());
		interestingBook.insert(interestingBook.end(), interestingBook_temp.begin(), interestingBook_temp.end());
	}
	return interestingBook;
}

vector<string> Student::getMessages()
{
	//��ѯͼ�����
	vector<BorrowInfo> vb = BorrowInfo::getInfoByNumberID(numberID, Book_EXCEED);
	vector<string> result;
	//���ص���ͼ��
	if (!vb.empty()) 
	{
		string bookInfo = "��" + to_string(vb.size()) + "��ͼ���ѵ��ڣ�";
		result.push_back(bookInfo);
	}
	return result;
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
