#include "Table.h"
#include <iostream>
Table::Table(string _name, int _num, int _len[], bool _ifsearch[])
{
	name = _name;
	num = _num;
	for (int i = 0; i < num; i++)
	{
		len.push_back(_len[i]);
		if_search.push_back(_ifsearch[i]);
	}

	ofstream info(name.c_str());
	char* infor = order();
	info.write(infor, 4 + 5 * num);
	delete[] infor;
	info.close();
	table.open(name + ".pag", get_len_sum());
	///还需创建块
}

Table::Table(string _name)
{
	name = _name;
	ifstream info(name.c_str());
	char* p;

	p = (char*)&num;
	info.read(p, 4);
	int *_len = new int[num];
	bool* _if_search = new bool[num];
	p = (char*)_len;
	info.read(p, 4 * num);
	p = (char*)_if_search;
	info.read(p, num);
	for (int i = 0; i < num; i++) {
		len.push_back(_len[i]);
		if_search.push_back(_if_search[i]);
	}
	delete[] _len;
	delete[] _if_search;
	table.open(name + ".pag");
}

Table::Table()
{
}



int Table::add(char * data)
{
	int id = table.add(data);
	return id;
}

vector<int> Table::find(int colum, char * key)
{
	vector<int> list_id;
	int n = table.length();
	int k = 0;
	char *a = new char[len[colum]];
	for (int i = 0; i < colum;  k += len[i], i++);
	for (int i = 0; i < n; i++)
	{
		if (!table.exist(i))
			continue;
		table.read(a, i, k, len[colum]);
		int j;
		for (j = 0; j < len[colum]; j++)
			if (a[j] != key[j])
				break;
		if (j == len[colum])
			list_id.push_back(i);
	}
	delete[] a;
	return list_id;
}

char * Table::get(int id)
{
	char* a = new char[get_len_sum()];
	if (table.get(a, id))
		return a;
	else
		return a;
}

bool Table::get(char * a, int id)
{
	if (table.get(a, id))
		return true;
	else
		return false;
}

bool Table::change(int id, int column, char * attr)
{
	if (table.exist(id) && column < num)
	{
		int k = 0;
		for (int i = 0; i < column; k += len[i], i++);
		table.write(attr, id, k, len[column]);
		return true;
	}
	else
		return false;
}

int Table::size()
{
	return table.get_num();
}

vector<int> Table::get_column_length()
{
	vector<int> column_length;
	for (int i = 0; i < num; i++)
		column_length.push_back(len[i]);
	return column_length;
}

vector<pair<int, char*>> Table::get_all()
{
	vector< pair<int, char*> > a;
	char* p;
	int length = get_len_sum();
	int n = table.length();
	p = new char[length];
	for (int i = 0; i < n; i++)
		if (table.get(p, i)) {
			a.push_back(make_pair(i, p));
			p = new char[length];
		}
	delete[] p;
	return a;
}

bool Table::del(int id)
{
	char *a = get(id);
	if (table.del(id))
		return true;
	else
		return false;
}

int Table::get_len_sum()
{

	int sum = 0;
	for (int i = 0; i < num; i++)
		sum += len[i];
	return sum;
}

char * Table::order()
{
	char *head, *p, *q;
	int *_len;
	bool* _if_search;
	head = new char[4 + 5 * num];
	p = head;
	q = (char*)&num;
	for (int i = 0; i < 4; i++, p++)
		*p = q[i];
	_len = new int[num];
	_if_search = new bool[num];
	for (int i = 0; i < num; i++) {
		_len[i] = len[i];
		_if_search[i] = if_search[i];
	}
	q = (char*)_len;
	for (int i = 0, n = num * 4; i < n; i++, p++)
		*p = q[i];
	q = (char*)_if_search;
	for (int i = 0; i < num; i++, p++)
		*p = q[i];
	delete[] _len;
	delete[] _if_search;
	return head;
}