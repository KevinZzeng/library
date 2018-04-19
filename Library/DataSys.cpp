#include "DataSys.h"


map<string, DataSys*> DataSys::Sys;

void DataSys::create(string _name, int _num, int _len[], bool _ifsearch[])  ///新建表(表名，表的列数，格式描述，是否课检索)
{
	int sum = 0;
	for (int i = 0; i < _num; i++)
		sum += _len[i];
	ofstream info(_name.c_str(), ios::binary);
	info.write((char*)&_num, 4);
	info.write((char*)_len, 4 * _num);
	info.write((char*)_ifsearch, _num);
	info.close();
	FileOp _table;
	Blist _blist;
	_table.open(_name + ".pag", sum);
	vector<int> sear_len;
	for (int i = 0; i < _num; i++)
		if (_ifsearch[i])
			sear_len.push_back(_len[i]);
	_blist.build(_name, sear_len);
}

DataSys* DataSys::getData(string name)
{
	if (Sys[name])
		return Sys[name];
	else
	{
		try
		{
			DataSys* x = new DataSys(name);
			Sys[name] = x;
			return x;
		}
		catch (int e)
		{
			if (e == -1)
				throw - 1;
			else
				throw 0;
		}
	}
}

DataSys::DataSys(string _name)///如果抛出整形异常 -1 表示该数据表不存在
{
	name = _name;
	ifstream info(name.c_str(), ios::binary);
	if (!info)
		throw - 1;
	char* p;
	p = (char*)&num;
	info.read(p, 4);
	int *_len = new int[num];
	bool* _if_search = new bool[num];
	p = (char*)_len;
	info.read(p, 4 * num);
	p = (char*)_if_search;
	info.read(p, num);
	for (int i = 0; i < num; i++)
	{
		len.push_back(_len[i]);
		if_search.push_back(_if_search[i]);
	}
	delete[] _len;
	delete[] _if_search;
	table.open(name + ".pag");
	blist.open(name, table.get_num());
}

void DataSys::Sysclose(string name)
{
	if (Sys[name])
	{
		Sys[name]->blist.close();
		Sys[name]->table.close();
		delete Sys[name];
		Sys.erase(name);
	}
}

string DataSys::getName()
{
	return name;
}
void DataSys::close()
{
	DataSys::Sysclose(name);
}

vector< pair<int, char*> > DataSys::get_by_key(int column, char* key)
{
	vector< pair<int, char*> > a;
	char* p;
	vector<int> res_id = find(column, key);
	int n = res_id.size();
	for (int i = 0; i < n; i++)
		a.push_back(make_pair(res_id[i], get(res_id[i])));
	return a;
}

int DataSys::add(char * data)
{
	int id = table.add(data);
	vector<char*> key;
	for (int i = 0, k = 0; i < num; k += len[i], i++)
		if (if_search[i])
			key.push_back(data + k);
	blist.insert(key, id);
	return id;
}

bool DataSys::del(int id)
{
	if (table.exist(id))
	{
		char *data = get(id);
		table.del(id);
		vector<char*> key;
		for (int i = 0, k = 0; i < num; k += len[i], i++)
			if (if_search[i])
				key.push_back(data + k);
		blist.del(key, id);
		delete[] data;
	}
	else
		return false;
}

void DataSys::del_by_key(int column, char * key)
{
	vector<int> res_id = find(column, key);
	int n = res_id.size();
	for (int i = 0; i < n; i++)
		del(res_id[i]);
}

vector<int> DataSys::fuzzy_search(int column, char* key)
{
	if (if_search[column])
	{
		int i, k;
		for (i = 0, k = 0; i < column; i++)
			if (if_search[i])
				k++;
		return blist.fuzzy_search(k, key);
	}
	else
		throw 1;///抛出不可索引异常
}

vector<int> DataSys::find(int column, char * key)
{
	if (if_search[column])
	{
		int i, k;
		for (i = 0, k = 0; i < column; i++)
			if (if_search[i])
				k++;
		return blist.search(k, key);
	}
	else
		return find_onybyone(column, key);
}
vector<int> DataSys::find_onybyone(int column, char * key)
{
	vector<int> list_id;
	int n = table.length();
	int k = 0;
	char *a = new char[len[column]];
	for (int i = 0; i < column; k += len[i], i++);
	for (int i = 0; i < n; i++)
	{
		if (!table.exist(i))
			continue;
		table.read(a, i, k, len[column]);
		int j;
		for (j = 0; j < len[column]; j++)
			if (a[j] != key[j])
				break;
		if (j == len[column])
			list_id.push_back(i);
	}
	delete[] a;
	return list_id;
}

char * DataSys::get(int id)
{
	if (table.exist(id))
	{
		char* a = new char[get_len_sum()];
		table.get(a, id);
		return a;
	}
	else
		return NULL;
}

bool DataSys::get(char * a, int id)
{
	if (table.get(a, id))
		return true;
	else
		return false;
}

bool DataSys::change(int id, int column, char * attr)
{
	if (table.exist(id) && column < num)
	{
		int p = 0, k = 0;
		for (int i = 0; i < column; p += len[i], i++);
		if (if_search[column])
		{
			char* key = new char[len[column]];
			table.read(key, id, p, len[column]);
			for (int i = 0; i < column; i++)
				if (if_search[i])
					k++;
			blist.update(k, key, attr, id);
			delete[] key;
		}
		table.write(attr, id, p, len[column]);
		return true;
	}
	else
		return false;
}

int DataSys::size()
{
	return table.get_num();
}

vector<int> DataSys::get_column_length()
{
	vector<int> column_length;
	for (int i = 0; i < num; i++)
		column_length.push_back(len[i]);
	return column_length;
}

vector<pair<int, char*> > DataSys::get_all()
{
	vector< pair<int, char*> > a;
	char* p;
	int length = get_len_sum();
	int n = table.length();
	p = new char[length];
	for (int i = 0; i < n; i++)
		if (table.get(p, i))
		{
			a.push_back(make_pair(i, p));
			p = new char[length];
		}
	delete[] p;
	return a;
}

int DataSys::get_len_sum()
{

	int sum = 0;
	for (int i = 0; i < num; i++)
		sum += len[i];
	return sum;
}
