#include "BookCategory.h"


BookCategory::BookCategory(int ID, string category)
{
	init();
	this->ID = ID;
	strcpy(this->category, category.c_str());
}

int BookCategory::getID()
{
	return ID;
}

string BookCategory::getCategory()
{
	return string(category);
}

void BookCategory::setCategory(string category)
{
	strcpy(this->category, category.c_str());
}

void BookCategory::setID(int ID)
{
	this->ID = ID;
}

bool BookCategory::save()
{
	Dao d;
	vector<char*> v;
	v.push_back(this->category);
	vector<pair<int, char*> > s;
	s.push_back(make_pair(0, this->category));
	vector<map<int, char *>> data = d.select("bookCategory", s);//依据category获取这个分类名字的id，判断这个分类名字存不存在
	if (data.empty()) {//如果这个分类不存在，才可以增加或者修改成这个分类
		if (this->ID == -1) {//id为-1说明是增加这个分类
			if (d.insert_into("bookCategory", v))//添加成功则返回true
				return true;
		}
		else {//否则则是update这个分类
			if (d.update("bookCategory", this->ID, v)) // 添加成功则返回true
				return true;
		}
	}
	return false;
}

bool BookCategory::destory()
{
	Dao d;
	if (this->ID != -1) {
		if (d.delete_from("bookCategory", this->ID));
			return true;//删除这个分类
	}
	return false;
}

map<int, string> BookCategory::getAllCategory()
{
	Dao d;
	vector<pair<int, char*> > s;
	vector<map<int, char *>> data = d.select("bookCategory", s);
	map<int, string> m;
	for (vector<map<int, char *>>::iterator it = data.begin(); it != data.end(); it++) {
		m.insert(make_pair(*reinterpret_cast<int*>((*it)[-1]), (*it)[0]));
	}// 循环把找出来的字符串数据转成category类型放进map中

	return m;
}

int BookCategory::getCategoryIdByName(string categoryName)
{
	Dao d;
	vector<pair<int, char*> > s;
	char n[40];
	strcpy(n, categoryName.c_str());
	s.push_back(make_pair(0, n));//根据分类名字查找分类ID
	vector<map<int, char *>> data = d.select("bookCategory", s);
	map<int, string> m;
	if (!data.empty()) {//如果不为空
		return *reinterpret_cast<int*>((data[0])[-1]);
	}
	return -1;//没找到返回-1
}

string BookCategory::getCategoryNameByID(int ID)
{
	Dao d;
	map<int, char *>  s = d.getById("bookCategory", ID);
	if (s.size() == 0)
		return "";
	return string(s[0]);
}
