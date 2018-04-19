#pragma once
#include "Blist.h"
class DataSys
{
public:
	static void create(string _name, int _num, int _len[], bool _ifsearch[]); ///新建表(表名，表的列数，格式描述，是否课检索)
	static DataSys* getData(string name);///获得数据表指针
	static void Sysclose(string name);///关闭指定名称数据表
	void close();///关闭数据管理器，请在程序结束前调用该方法以防止数据损失，与上一个方法效果相同
	string getName();///返回当前对象打开的表名
	int add(char* data);	///插入传入的信息
	bool del(int id); ///根据行id删除行
	vector<int> find(int column, char* key);///根据第几关键字,获取所有满足条件的行的id ，（若该列为非加速列则自动调用暴力查找）
	vector<int> fuzzy_search(int column, char* key);///模糊搜索
	bool change(int id, int column, char * attr);///改变指定行指定列的属性
	char* get(int id); /// 根据行id获取对应行,此处有待商议,易导致内存损失，不推荐使用 务必delete
	bool get(char* a, int id); /// 推荐使用的方法
	vector< pair<int, char*> > get_by_key(int column, char* key);///根据第几关键字,获取所有满足条件的行属性与id  char*需delete
	void del_by_key(int column, char * key);///直接根据条件key，删除满足该条件的行
	int size();///总行数
	vector<int> get_column_length();///获取每一列的宽度
	vector< pair<int, char*> > get_all();///湖区整张数据表的所有数据  char*需delete

protected:

	DataSys(string _name);  ///打开表

	int get_len_sum();

	vector<int> find_onybyone(int column, char * key);///暴力查找

private:
	static map<string, DataSys*> Sys;
	string name;
	int num;         ///列数
	vector<int> len;           ///每一列的宽度
	vector<bool> if_search;    ///是否支持索引
	FileOp table;
	Blist blist;
};