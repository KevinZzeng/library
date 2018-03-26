#pragma once

/*************** notice *************
TODO：底层提供一个返回表所有数据的接口

*/

/*
每个类中加入 ID ，为了维护数据方便
每个类写好序列化函数，反序列化函数
序列化函数： 对每个分别字段进行序列化
反序列化函数： Dao 类提供给你 序列化的数据和在类中对应的成员顺序编号，你负责绑定到类上面
*/


//所有 char ＊　调用方使用完应该 delete
//char * res 都是 new 出来的，使用完成 delete，数据库层操作
#include "Data.h"
#include "Table.h"
#include <map>
#include <vector>


class Dao {
private :
	Table _table;
	string _tableName;

	//根据用户调用的数据库名称获取数据库，如果 _tableName 和调用一样不则重新获取，有个问题？不重新获取数据库的话，数据更新了可以查到新的数据嘛？
	void init(string tableName);

public:

	Dao();

	//void inster_into(const string tableName, vector<pair<int, char *> > &v);  //废弃函数
	//inster_into vector <value> value 是序列化的成员变量，按照顺序写入vector
	bool inster_into(const string tableName, vector<char *> &v);
	
	//bool update(const string tableName, int id, vector<pair<int, char *> > &v); //废弃函数
	//updae vector <value> value 是序列化的成员变量，按照顺序写入vector
	bool update(const string tableName, int id, vector<char *> &v);

	bool delete_from(const string tableName, int id);


	//通过ID 快速返回数据, <int ,char *> int 是类成员变量顺序， -1表示ID， char *就是数据项
	map<int, char *> getById(const string tableName, int id);


	//select vector<map<int, char *>> 存放查询条件，多条件实现
	//返回一个 map 数组，每个 map　里面包括每个对象的变量，　-1 表示ID
	vector<map<int, char *>> select(const string tableName, vector<pair<int, char*> >&v);
	
};