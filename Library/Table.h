#pragma once
#include <set>
#include <vector>
using namespace std;
class Table {
public:
	void add(char *data) {};
	set<int> find(int colum, char * key) { return set<int>(); };		//���� ʹ�� set �����ɷ�
	char *get(int id) { return ""; };
	vector<pair<int, char *> > get_all() { return vector<pair<int, char *> >(); }
	void del(int id) {};
	void change(int id, int colum, char* attr) {};
	vector<int> get_column_length() { return vector<int>(); };
};
