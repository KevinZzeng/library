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

void Dao::inster_into(const string tableName, vector<char*> &v)
{
	init(tableName);
	//�����ݿ�ײ��õ� length[] & colums Ҳ���� 
	//�����ȣ�����ƴ�� char* �ַ���

	int rowLen = 0;
	/*	for (vector<pair<int, char*>>::iterator it = v.begin(); it != v.end(); ++it)
		rowLen += it->first;
*/
	vector<int> t_info = _table.get_column_length();
	for (vector<int>::iterator it = t_info.begin(); it != t_info.end(); ++it)
		rowLen += *it;

	char *res = new char[rowLen];
	int step = 0, i =0;
	for (vector<char *>::iterator it = v.begin(); it != v.end(); ++it) {
		memcpy(res + step, *it, t_info[i]);
		step += t_info[i++];
	}

	//�������ݿ�
	_table.add(res);
	
}

bool Dao::update(const string tableName, int id, vector<char*> &v)
{
	init(tableName);
	if (id == -1)
		return false;

	//��ȡԭ���������ԣ�ȷ���ĸ����Է����˱仯��Ȼ�����update
	vector<int> submitColumn;
	map<int, char *> obj = this->getById(tableName, id);
	for (map<int, char *>::iterator it = obj.begin(); it != obj.end(); ++it) {
		if (strcmp(it->second, v[it->first]) != 0) {
			submitColumn.push_back(it->first);
		}
	}

	//�����ύ�����ݿ�
	for (vector<int>::iterator it = submitColumn.begin(); it != submitColumn.end(); ++it) {
		_table.change(id, *it , v[*it]);
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
	//�����ݿ�ײ���ݱ����õ� length[] 
	
	vector<int> t_info = _table.get_column_length();
	int colums = t_info.size();
	

	//���ݲ����ڻ᷵��ʲô?
	char *ret = _table.get(id);

	//���� char *
	int step = 0;
	for (int i = 0; i < colums; i++) {
		char *t = new char[t_info[i]];
		memcpy(t, ret + step, t_info[i]);
		res.insert(pair<int, char*>(i, t));
		step += t_info[i];
	}

	//����ID key��-1  value��IDֵ
	char *t = new char[4];
	res.insert(pair<int, char *>(-1, reinterpret_cast<char *>(&id)));
	
	return res;
}

vector<map<int, char*>> Dao::select(const string tableName, vector<pair<int, char*>>& v)
{
	init(tableName);
	//��ȡ���ϲ�ѯ������ ID
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
