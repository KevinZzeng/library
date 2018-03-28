#include "Dao.h"
#include "Utils.h"
#include <set>
#include <exception>
#include <iostream>
void Dao::init(string tableName)
{
	if (!_tableName.compare(tableName))
		return;
	this->_tableName = tableName;
	this->_table = Data::get_table(tableName);
}

map<int, char*> Dao::transCharPtr2Map(string tableName, int id, char * row)
{
	map<int, char *> res;
	//从数据库底层根据表名拿到 length[] 
	vector<int> t_info;
	int colums;
	try {

		t_info = _table.get_column_length();
		colums = t_info.size();
	}
	catch (exception &e) {
		cout << "DataBase Operate Error:" << e.what() << endl;
		return res;
	}

	//构造 char *
	int step = 0;
	for (int i = 0; i < colums; i++) {
		char *t = new char[t_info[i]];
		memcpy(t, row + step, t_info[i]);
		res.insert(pair<int, char*>(i, t));
		step += t_info[i];
	}

	//插入ID key：-1  value：ID值
	char *t = new char[4];
	res.insert(pair<int, char *>(-1, reinterpret_cast<char *>(&id)));

	return res;
}

Dao::Dao()
{
	this->_tableName = "";
}

bool Dao::inster_into(const string tableName, vector<char*> &v)
{
	init(tableName);
	//从数据库底层拿到 length[] & colums 也可以 
	//计算宽度，用于拼接 char* 字符串

	int rowLen = 0;
	vector<int> t_info = _table.get_column_length();
	

	for (vector<int>::iterator it = t_info.begin(); it != t_info.end(); ++it) {
		rowLen += *it;
	}

	char *res = new char[rowLen];
	int step = 0, i = 0;
	for (vector<char *>::iterator it = v.begin(); it != v.end(); ++it) {
		memcpy(res + step, *it, t_info[i]);
		step += t_info[i++];
	}

	//存入数据库
	try {
		_table.add(res);
		Utils::freeSpace(res);
		return true;
	}
	catch (exception &e) {
		cout << "DataBase Operate Error:" << e.what() << endl;
		Utils::freeSpace(res);
		return false;
	}

}

bool Dao::update(const string tableName, int id, vector<char*> &v)
{
	init(tableName);
	if (id == -1)
		return false;

	//获取原来对象属性，确定哪个属性发生了变化，然后进行update
	vector<int> submitColumn;
	try {
		map<int, char *> obj = this->getById(tableName, id);
		for (map<int, char *>::iterator it = obj.begin(); it != obj.end(); ++it) {
			if (strcmp(it->second, v[it->first]) != 0) {
				submitColumn.push_back(it->first);
			}
		}

		//逐项提交到数据库
		for (vector<int>::iterator it = submitColumn.begin(); it != submitColumn.end(); ++it) {
			_table.change(id, *it, v[*it]);
		}
		return true;
	}
	catch (exception &e) {
		cout << "DataBase Operate Error:" << e.what() << endl;
		return false;
	}
}


bool Dao::delete_from(const string tableName, int id)
{
	init(tableName);
	if (id == -1)
		return false;

	try {
		return _table.del(id);
	}
	catch (exception &e) {
		cout << "DataBase Operate Error:" << e.what() << endl;
		return false;
	}
}

map<int, char *> Dao::getById(const string tableName, int id)
{
	map<int, char *> res;
	if (id == -1)
		return res;

	char *ret = NULL;
	try {
		ret = _table.get(id);
	}
	catch (exception &e) {
		cout << "DataBase Operate Error:" << e.what() << endl;
		return res;
	}
	res = this->transCharPtr2Map(tableName, id, ret);
	
	Utils::freeSpace(ret);
	
	return res;
}

vector<map<int, char*>> Dao::select(const string tableName, vector<pair<int, char*>>& v)
{
	init(tableName);
	//获取符合查询条件的 ID
	vector<map<int, char*>> res;
	try {
		//如果查询条件是空，那么就是获取一整张表信息
		if (v.size() == 0) {
			vector<pair<int, char*> > tableAll=_table.get_all();
			for (vector<pair<int, char*> >::iterator it = tableAll.begin(); it != tableAll.end(); ++it) {
				res.push_back(this->transCharPtr2Map(tableName, it->first, it->second));
				//释放数据库 new 的字符串
				Utils::freeSpace(it->second);
			}
		}
		else {
			set<int> t1 = _table.find(v[0].first, v[0].second);
			for (int i = 1; i < v.size(); i++) {
				Utils::setIntersection(t1, _table.find(v[i].first, v[i].second));
			}


			for (set<int>::iterator it = t1.begin(); it != t1.end(); ++it) {
				res.push_back(this->getById(tableName, *it));
			}
		}

		return res;
	}
	catch (exception &e) {
		cout << "DataBase Operate Error:" << e.what() << endl;
		return res;
	}

}
