#include "Dao.h"
#include "Utils.h"
#include <set>
void Dao::init(string tableName)
{
	if (_tableName.compare(tableName))
		return;
	this->_tableName = tableName;
	this->_table = Data::get_table(this->_tableName);
}

Dao::Dao()
{
	this->_tableName = "";
}

void Dao::inster_into(const string tableName, vector<pair<int, char*>> &v)
{
	init(tableName);
	//从数据库底层拿到 length[] & colums 也可以 
	//计算宽度，用于拼接 char* 字符串

	int rowLen = 0;
	/*	for (vector<pair<int, char*>>::iterator it = v.begin(); it != v.end(); ++it)
		rowLen += it->first;
*/
	vector<int> t_info = _table.get_column_length();
	for (vector<int>::iterator it = t_info.begin(); it != t_info.end(); ++it)
		rowLen += *it;

	char *res = new char[rowLen];
	int step = 0;
	for (vector<pair<int, char *> >::iterator it = v.begin(); it != v.end(); ++it) {
		memcpy(res + step, it->second, it->first);
		step += it->first;
	}

	//存入数据库
	_table.add(res);
	
}

bool Dao::update(const string tableName, int id, vector<pair<int, char*>> &v)
{
	init(tableName);
	if (id == -1)
		return false;

	//逐项提交到数据库
	for (vector<pair<int, char*>>::iterator it = v.begin(); it != v.end(); ++it) {
		_table.change(id, it->first, it->second);
	}
	return true;

}

bool Dao::delete_from(const string tableName, int id)
{
	init(tableName);
	if (id == -1)
		return false;

	_table.del(id);
	return true;
}

map<int, char *> Dao::getById(const string tableName, int id)
{
	if (id == -1)
		return map<int, char *>();

	map<int, char *> res;
	//从数据库底层根据表名拿到 length[] 
	
	vector<int> t_info = _table.get_column_length();
	int colums = t_info.size();
	

	//数据不存在会返回什么?
	char *ret = _table.get(id);

	//构造 char *
	int step = 0;
	for (int i = 0; i < colums; i++) {
		char *t = new char[t_info[i]];
		memcpy(t, ret + step, t_info[i]);
		res.insert(pair<int, char*>(i, t));
		step += t_info[i];
	}

	//插入ID key：-1  value：ID值
	char *t = new char[4];
	res.insert(pair<int, char *>(-1, reinterpret_cast<char *>(&id)));
	
	return res;
}

vector<map<int, char*>> Dao::select(const string tableName, vector<pair<int, char*>>& v)
{
	init(tableName);
	//获取符合查询条件的 ID
	set<int> t1 = _table.find(v[0].first, v[0].second);
	for (int i = 1; i < v.size(); i++ ) {
		Utils::setIntersection(t1, _table.find(v[i].first, v[i].second));
	}

	vector<map<int, char*>> res;
	for (set<int>::iterator it = t1.begin(); it != t1.end(); ++it) {
		res.push_back(this->getById(tableName, *it));
	}

	return res;
}
