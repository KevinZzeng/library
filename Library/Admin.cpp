#include "Admin.h"

Admin::Admin(string numberID, string password, string email)
{
	setId(-1);
	setNumberID(numberID);
	setPassword(password);
	setEmail(email);
}

Admin::Admin()
{
}

bool Admin::login(string numberID, string password)
{
	/*��ȡ�û�������*/
	strcpy(this->numberID, numberID.c_str());
	strcpy(this->password, password.c_str());
	//�ж��Ƿ���ȷ����ѯ���ݿ�
	//�����ѯ����
	MD5 password_md5 = MD5(password);
	strcpy(this->password, password_md5.toStr32().c_str());
	vector<pair<int, char*> > v;
	v.push_back(make_pair(0, this->numberID));
	v.push_back(make_pair(1, this->password));
	Dao dao;
	vector<map<int, char *>> adminInfo = dao.select("administrator", v);
	//��ѯ����Ӧ����Ա
	if (!adminInfo.empty()) {
		map<int, char*> admin = adminInfo[0];
		//����Ӧ��Ϣ
		strcpy(this->email, admin[2]);
		return true;
	}
	else {
		return false;
	}
}

bool Admin::save()
{
	Dao dao;
	vector<char *> insertInfo;
	//�������
	insertInfo.push_back(numberID);
	insertInfo.push_back(password);
	insertInfo.push_back(email);

	//�������ݿ�
	bool ifSuccess = true;
	//��ѯ�Ƿ����numberID����Ա
	vector<pair<int, char*> > v;
	v.push_back(make_pair(0, numberID));
	vector<map<int, char *>> adminInfo = dao.select("administrator", v);
	if (adminInfo.empty()) {
		try {
			if (id == -1) {
				dao.insert_into("administrator", insertInfo);
			}
			else {
				dao.update("administrator", id, insertInfo);
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

void Admin::setId(int id)
{
	this->id = id;
}

int Admin::getId()
{
	return id;
}

void Admin::setNumberID(string numberID)
{
	strcpy(this->numberID, numberID.c_str());
}

string Admin::getNumberID()
{
	return string(numberID);
}

void Admin::setPassword(string password)
{
	MD5 password_md5 = MD5(password);
	strcpy(this->password, password_md5.toStr32().c_str());
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
	return stu.save();
}

bool Admin::addAdmin(Admin & admin)
{
	return admin.save();
}

Student Admin::getStudentByID(string numebrID)
{
	vector<Student> studentList = Student::getStudent("", numebrID, -1);
	return studentList[0];
}

vector<Student> Admin::getStudentsByName(string name, int major)
{
	vector<Student> studentList = Student::getStudent(name, "", major);
	return studentList;
}
