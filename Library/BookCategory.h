#pragma once
#include <string>
#include <map>
using namespace std;
class BookCategory {
private:
	int id;
	string category;
public:
	bool save();
	bool destory();
	//返回 <id,category> 前台绑定
	static map<string, string> getAllCategory();
	static int getCategoryIdByName(string categoryName);

};