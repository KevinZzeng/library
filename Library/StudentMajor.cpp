#include "StudentMajor.h"

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
	strcpy(this->major, major.c_str());
	Dao dao;
	vector<pair<int, char*> > v;
	v.push_back(make_pair(0, this->major));
	//查询major对应的id
	vector<map<int, char *>> result = dao.select("studentMajor", v);
	id = reinterpret_cast<int>(result[0][-1]);
	return id;
}

bool StudentMajor::save()
{
	Dao dao;
	vector<char*> v;
	//构造插入数据
	v.push_back(major);
	bool ifSuccess = true;
	try {
		if (id == -1) {
			dao.insert_into("studentMajor", v);
		}
		else {
			dao.update("studentMajor", id, v);
		}
	}
	catch(exception e){
		ifSuccess = false;
	}
	return 	ifSuccess;
}

bool StudentMajor::destory()
{
	Dao dao;
	return dao.delete_from("studentMajor", id);
}
