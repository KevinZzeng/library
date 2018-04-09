#include "StudentMajor.h"

StudentMajor::StudentMajor()
{
	init();
}

void StudentMajor::setMajor(string major)
{
	strcpy(this->major, major.c_str());
}

string StudentMajor::getMajor()
{
	return string(major);
}

void StudentMajor::setId(int id)
{
	this->id = id;
}

int StudentMajor::getId()
{
	return id;
}

int StudentMajor::getIDByMajor(string major)
{
	char majors[50];
	strcpy(majors, major.c_str());
	Dao dao;
	vector<pair<int, char*> > v;
	v.push_back(make_pair(0, majors));
	//查询major对应的id
	vector<map<int, char *>> result = dao.select("studentMajor", v);
	int id = -1;
	if (!result.empty()) {
		id = *(reinterpret_cast<int*>(result[0][-1]));
	}
	return id;
}

bool StudentMajor::save()
{
	Dao dao;
	vector<char*> v;
	//构造插入数据
	v.push_back(major);
	//-1表示不存在
	int ifExist = StudentMajor::getIDByMajor(major);
	bool ifSuccess = false;
	if (ifExist == -1) {
		try {
			if (id == -1) {
				dao.insert_into("studentMajor", v);
				ifSuccess = true;
			}
			else {
				dao.update("studentMajor", id, v);
				ifSuccess = true;
			}
		}
		catch (exception e) {
			ifSuccess = false;
		}
	}
	
	return 	ifSuccess;
}

bool StudentMajor::destory()
{
	Dao dao;
	return dao.delete_from("studentMajor", id);
}
