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
	return 0;
}

bool StudentMajor::save()
{
	return false;
}

bool StudentMajor::destory()
{
	return false;
}
