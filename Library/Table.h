#pragma once
#include <set>
#include <vector>
#include "File.h"
#include <fstream>
using namespace std;

//class Table {
//public:
//	int add(char *data) {};
//	set<int> find(int colum, char * key) { return set<int>(); }
//	char *get(int id) { return ""; }
//	vector<pair<int, char *> > get_all() { return vector<pair<int, char *> >(); }
//	bool del(int id) {}
//	void change(int id, int colum, char* attr) {}
//	vector<int> get_column_length() { return vector<int>(); }
//};

class Table
{
public:
	Table(string _name, int _num, int _len[], bool _ifsearch[]);     ///新建表(表名，表的列数，格式描述，是否课检索)
	
	Table(string _name);  ///打开表
	
	Table();

	~Table();
	
	int add(char* data);	///传入的信息
	
	set<int> find(int colum, char* key);///根据第几关键字,获取所有满足条件的行的id


	char* get(int id); /// 根据行id获取对应行,,此处有待商议,易导致内存损失，不推荐使用 务必delete
	
	bool get(char* a, int id); /// 推荐使用的方法
	
	bool change(int id, int column, char * attr);

	int size();///总行数

	vector<int> get_column_length();

	vector< pair<int, char*> > get_all();

	bool del(int id); ///根据行id删除行

protected:
	int get_len_sum();
	
	char* order();
	
private:
	string name;
	int num;         ///列数
	int* len;           ///每一列的宽度
	bool* if_search;    ///是否支持索引
	File table;
};