#include "StudentMajor.h"

void StudentMajor::setMajor(string major)
{
	strcpy(this->major, major.c_str());
}

string StudentMajor::getMajor()
{
	return string(major);
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
	//��ѯmajor��Ӧ��id
	vector<map<int, char *>> result = dao.select("studentMajor", v);
	return reinterpret_cast<int>(result[0][-1]);
}

bool StudentMajor::save()
{
	Dao dao;
	vector<pair<int, char*> > v;
	//�����������
	v.push_back(make_pair(0, major));
	bool ifSuccess = true;
	try {
		dao.inster_into("studentMajor", v);
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
