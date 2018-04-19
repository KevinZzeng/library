#include "Dao.h"
#include "Utils.h"
#include <set>
#include <exception>
#include <iostream>
bool Dao::init(string tableName)
{
	if (!_tableName.compare(tableName))
		return true;
	this->_tableName = tableName;
	try {
		this->_table = DataSys::getData(tableName);
		return true;
	}
	catch (const int e){
		if(e == -1)
			cout << "Table not in disk!" << endl;
		return false;
	}
}

map<int, char*> Dao::transCharPtr2Map(string tableName, int id, char * row)
{
	map<int, char *> res;
	//�����ݿ�ײ���ݱ����õ� length[] 
	vector<int> t_info;
	int colums;
	try {

		t_info = _table->get_column_length();
		colums = t_info.size();
	}
	catch (exception &e) {
		cout << "DataBase Operate Error:" << e.what() << endl;
		return res;
	}

	//���� char *
	int step = 0;
	for (int i = 0; i < colums; i++) {
		char *t = new char[t_info[i]];
		memcpy(t, row + step, t_info[i]);
		res.insert(pair<int, char*>(i, t));
		step += t_info[i];
	}

	//����ID key��-1  value��IDֵ
	char * tmp = new char[4];
	memcpy(tmp, &id, 4);
	res.insert(pair<int, char*>(-1, tmp));
	//res.insert(pair<int, char *>(-1, reinterpret_cast<char *>(&id)));

	return res;
}

Dao::Dao()
{
	this->_tableName = "";
}

bool Dao::insert_into(const string tableName, vector<char*> &v)
{
	
	if (!init(tableName)) return false;

	//�����ݿ�ײ��õ� length[] & colums Ҳ���� 
	//�����ȣ�����ƴ�� char* �ַ���
	//Table tab = Data::get_table("daodemo");

	int rowLen = 0;


	vector<int> t_info = _table->get_column_length();


	for (vector<int>::iterator it = t_info.begin(); it != t_info.end(); ++it) {
		rowLen += *it;
	}

	char *res = new char[rowLen];
	int step = 0, i = 0;
	for (vector<char *>::iterator it = v.begin(); it != v.end(); ++it) {
		memcpy(res + step, *it, t_info[i]);
		step += t_info[i++];
	}

	//�������ݿ�
	try {
		cout << "����ɹ��� ID:" << _table->add(res) << endl;
		Utils::freeSpace(res);
		return true;
	}
	catch (const int e) {
		if(!e)
			cout << "DataBase Operate Error" << endl;
		Utils::freeSpace(res);
		return false;
	}

}

bool Dao::update(const string tableName, int id, vector<char*> &v)
{
	if (id == -1)
		return false;
	
	if (!init(tableName)) return false;

	//��ȡԭ���������ԣ�ȷ���ĸ����Է����˱仯��Ȼ�����update
	vector<int> submitColumn;
	vector<int> column_len = _table->get_column_length();
	int i = 0;
	try {
		map<int, char *> obj = this->getById(tableName, id);
		for (map<int, char *>::iterator it = obj.begin(); it != obj.end(); ++it) {
			if (it->first == -1)
				continue;
			if (memcmp(it->second, v[it->first], column_len[i++]) != 0) {
				//if (strcmp(it->second, v[it->first]) != 0) {
				submitColumn.push_back(it->first);
			}
		}

		bool submitFlag = true;
		//�����ύ�����ݿ�
		for (vector<int>::iterator it = submitColumn.begin(); submitFlag && it != submitColumn.end(); ++it) {
			if (!_table->change(id, *it, v[*it]))
				submitFlag = false;
		}
		return submitFlag;
	}
	catch (int &e) {
		if(!e)
			cout << "DataBase Operate Error" << endl;
		return false;
	}
}


bool Dao::delete_from(const string tableName, int id)
{
	if (id == -1)
		return false;

	if (!init(tableName)) return false;

	try {
		return _table->del(id);
	}
	catch (int e) {
		if(!e)
			cout << "DataBase Operate Error!" << endl;
		return false;
	}
}

map<int, char *> Dao::getById(const string tableName, int id)
{
	map<int, char *> res;
	if (id == -1)
		return res;

	if (!init(tableName)) return res;
	char *ret = NULL;
	try {
		ret = _table->get(id);
	}
	catch (int &e) {
		if(!e)
			cout << "DataBase Operate Error" << endl;
		return res;
	}
	res = this->transCharPtr2Map(tableName, id, ret);

	Utils::freeSpace(ret);

	return res;
}


vector<map<int, char*>> Dao::select(const string tableName, vector<pair<int, char*>>& v, int colIndex, char * val)
{
	//��ȡ���ϲ�ѯ������ ID
	vector<map<int, char*>> res;
	if(!init(tableName)) return res;
	try {
		//�����ѯ�����ǿ� && ����ģ����ѯĳһ�� ����ô���ǻ�ȡһ���ű���Ϣ
		if (v.size() == 0 && colIndex == -1 && val == NULL) {
			vector<pair<int, char*> > tableAll = _table->get_all();
			for (vector<pair<int, char*> >::iterator it = tableAll.begin(); it != tableAll.end(); ++it) {
				res.push_back(this->transCharPtr2Map(tableName, it->first, it->second));
				//�ͷ����ݿ� new ���ַ���
				Utils::freeSpace(it->second);
			}
		}
		else {
			vector<int> t1;
			//�������޵�����ģ��
			if (v.size()) {
				t1= _table->find(v[0].first, v[0].second);
				for (int i = 1; i < v.size(); i++) {
					Utils::getIntersection(t1, _table->find(v[i].first, v[i].second));
				}
			}
			//������ && һ��ģ������
			if(v.size() && colIndex != -1 && val != NULL)
				Utils::getIntersection(t1, _table->fuzzy_search(colIndex, val));
			//ֻģ����ѯ
			if(!v.size())
				t1 = _table->fuzzy_search(colIndex, val);

			for (vector<int>::iterator it = t1.begin(); it != t1.end(); ++it) {
				res.push_back(this->getById(tableName, *it));
			}
		}
		return res;
	}
	catch (int &e) {
		if(!e)
			cout << "DataBase Operate Error" << endl;
		return res;
	}
}