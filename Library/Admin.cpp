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
	vector<map<int, char *>> adminInfo = dao.select("administrator", v);
	//查询到对应管理员
	if (!adminInfo.empty()) {
		map<int, char*> admin = adminInfo[0];
		//填充对应信息
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
	//构造参数
	insertInfo.push_back(numberID);
	insertInfo.push_back(password);
	insertInfo.push_back(email);

	//存入数据库
	bool ifSuccess = true;
	try {
		dao.inster_into("administrator", insertInfo);
	}
	catch (exception e) {
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
	char numberID[13];
	strcpy(numberID, numebrID.c_str());
	//构造查询参数
	vector<pair<int, char*> > v;
	v.push_back(make_pair(0, numberID));
	Dao dao;
	vector<map<int, char *>> adminInfo = dao.select("users", v);
	map<int, char *> studentInfo = adminInfo[0];
	Student student = Student();
	student.setId(reinterpret_cast<int>(studentInfo[-1]));
	student.setNumberID(string(studentInfo[0]));
	student.setPassword(string(studentInfo[1]));
	student.setName(string(studentInfo[2]));
	student.setMajor(reinterpret_cast<int>(studentInfo[3]));
	student.setPhoto(string(studentInfo[4]));
	student.setMoney(reinterpret_cast<int>(studentInfo[5]));
	student.setEmail(string(studentInfo[6]));
	student.setStatus((status_class)reinterpret_cast<int>(studentInfo[7]));
	return student;
}

vector<Student> Admin::getStudentsByName(string name, int major)
{
	char t_name[50];
	strcpy(t_name, name.c_str());
	//构造查询参数
	vector<pair<int, char*> > v;
	v.push_back(make_pair(0, t_name));
	v.push_back(make_pair(3, reinterpret_cast<char*>(major)));
	Dao dao;
	vector<map<int, char *>> adminInfo = dao.select("users", v);
	int i = 0;
	vector<Student> stuList;
	vector<map<int, char *>>::iterator iter;
	//遍历vector
	for (iter = adminInfo.begin(); iter != adminInfo.end();iter++) {
		Student student = Student();
		student.setId(reinterpret_cast<int>((*iter)[-1]));
		student.setNumberID(string((*iter)[0]));
		student.setPassword(string((*iter)[1]));
		student.setName(string((*iter)[2]));
		student.setMajor(reinterpret_cast<int>((*iter)[3]));
		student.setPhoto(string((*iter)[4]));
		student.setMoney(reinterpret_cast<int>((*iter)[5]));
		student.setEmail(string((*iter)[6]));
		student.setStatus((status_class)reinterpret_cast<int>((*iter)[7]));
		stuList.push_back(student);
	}
	return stuList;
}
