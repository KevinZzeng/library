#include "Operation.h"

Operation::Operation()
{
}

Operation::Operation(int id, string numberID, string operation, string date)
{
	this->id = id;
	strcpy(this->numberID, numberID.c_str());
	strcpy(this->operation, operation.c_str());
	strcpy(this->date, date.c_str());
}

void Operation::setNumberID(string numberID)
{
	strcpy(this->numberID, numberID.c_str());
}

string Operation::getNumberID()
{
	return string(numberID);
}

void Operation::setOperation(string operation)
{
	strcpy(this->operation, operation.c_str());
}

string Operation::getOperation()
{
	return string(operation);
}

void Operation::setDate(string date)
{
	strcpy(this->date, date.c_str());
}

string Operation::getDate()
{
	return string(date);
}

bool Operation::save(Admin & ad)
{
	Dao dao;
	vector<char*> v;
	//构造插入数据
	v.push_back(numberID);
	v.push_back(operation);
	bool ifSuccess = true;
	try {
		if (id == -1) {
			dao.inster_into("operation", v);
		}
		else {
			dao.update("operation", id, v);
		}
	}
	catch (exception e) {
		ifSuccess = false;
	}
	return 	ifSuccess;
}

vector<Operation*> Operation::getAllOperaions()
{
	Dao dao;
	//构造查询参数
	vector<pair<int, char*>> v;
	//返回结果
	vector<map<int, char*>> v_result = dao.select("operation", v);
	//构造返回对象
	vector<Operation*> v_operation;
	vector<map<int, char*>>::iterator iter;
	for (iter = v_result.begin(); iter != v_result.end(); iter++) {
		v_operation.push_back(new Operation(reinterpret_cast<int>((*iter)[-1]), (*iter)[0], (*iter)[1], (*iter)[2]));	
	}

	return v_operation;
}
