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
	//���� <id,category> ǰ̨��
	static map<string, string> getAllCategory();
	static int getCategoryIdByName(string categoryName);

};