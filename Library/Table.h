#pragma once
#include <set>
#include <vector>
using namespace std;
class Table {
public:
	void add(char *data) {};
	set<int> find(int colum, char * key) { return set<int>(); };		//���� ʹ�� set �����ɷ�
	char *get(int id) { return ""; };
	void del(int id) {};
	void change(int id, int colum, char* attr) {};
	vector<int> get_column_length() { return vector<int>(); };
};
