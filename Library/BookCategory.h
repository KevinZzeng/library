#pragma once
#include <string>
#include <map>
#include <vector>
#include "Dao.h"
using namespace std;
class BookCategory {
private:
	int ID;
	char category[40];
public:
	//构造
	BookCategory();
	BookCategory(int ID, string category);
	//get set
	int getID();
	string getCategory();
	void setCategory(string category);
	void setID(int ID);
	//新增或者修改一个分类
	bool save();
	//删除一个分类
	bool destory();
	//返回所有的 <id,category> 前台绑定
	static map<int, string> getAllCategory();
	//根据分类名字查找分类ID，没找到返回-1
	static int getCategoryIdByName(string categoryName);

};