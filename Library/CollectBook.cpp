#include "CollectBook.h"


CollectBook::CollectBook(int ID, string numberID, string ISBN)
{
	this->ID = ID;
	strcpy(this->numberID, numberID.c_str());
	strcpy(this->ISBN, ISBN.c_str());
}

int CollectBook::getID()
{
	return ID;
}

string CollectBook::getNumberID()
{
	return string(numberID);
}

string CollectBook::getISBN()
{
	return string(ISBN);
}

void CollectBook::setID(int ID)
{
	this->ID = ID;
}

void CollectBook::setNumberID(string numberID)
{
	strcpy(this->numberID , numberID.c_str());
}

void CollectBook::setISBN(string ISBN)
{
	strcpy(this->ISBN, ISBN.c_str());
}

bool CollectBook::save()
{
	Dao d;
	vector<char*> v;
	v.push_back(numberID);
	v.push_back(ISBN);
	if (this->ID == -1) {//id为-1说明是增加b
		vector<pair<int, char*>> s;
		s.push_back(make_pair(0, this->ISBN));
		vector<map<int, char *>> data = d.select("book", s);
		if (data.empty())//如果该书不存在，则不能被预约
			return false;
		vector < map<int, char*> >::iterator ans = data.begin();
		if ((*ans)[8])//如果还能借则不能预约
			return false;
		s.pop_back();
		s.push_back(make_pair(1, this->ISBN));
		data = d.select("collectBook", s);
		for (ans = data.begin(); ans != data.end(); ans++) {
			if ((*ans)[0] == numberID) {//如果该本书已经被该用户预约了，说明不能再预约了，直接返回false
				return false;
			}
		}
		if (d.insert_into("collectBook", v))//添加成功则返回true
			return true;
	}
	else {//否则则是update这条预约记录
		if (d.update("collectBook", this->ID, v))//更新成功
			return true;
	}
	return false;
}

bool CollectBook::destory()
{
	Dao d;
	if (this->ID != -1) {
		if (d.delete_from("collectBook", this->ID));
		return true;//删除这条预约记录
	}
	return false;
}

vector<CollectBook> CollectBook::getCollectionByNumberID(string numberID)
{
	Dao d;
	vector<pair<int, char*> > s;//添加查询条件
	char n[13];
	strcpy(n, numberID.c_str());
	s.push_back(make_pair(0, n));//numberID
	vector<map<int, char *>> data = d.select("collectBook", s);//查找数据
	vector<CollectBook> list;
	for (vector<map<int, char *>>::iterator it = data.begin(); it != data.end(); it++) {
		CollectBook c_book(*reinterpret_cast<int*>((*it)[-1]), (*it)[0], (*it)[1]);
		list.push_back(c_book);//循环把找出来的字符串数据转成collectBook类型放进list中
	}
	return list;
}
