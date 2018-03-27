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
		vector<BorrowInfo> vb = BorrowInfo::getInfoByNumberID(numberID, EXCEED);
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
			dao.inster_into("users", insertInfo);
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
		vector<Book> interestingBook_temp = Book::getBooksByCategory(Book((*iter).getISBN_ID()).getCategory());
		interestingBook.insert(interestingBook.end(), interestingBook_temp.begin(), interestingBook_temp.end());
	}
	return interestingBook;
}

vector<string> Student::getMessages()
{
	//��ѯͼ�����
	vector<BorrowInfo> vb = BorrowInfo::getInfoByNumberID(numberID, EXCEED);
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
