#include "BorrowInfo.h"

BorrowInfo::BorrowInfo()
{
}

BorrowInfo::BorrowInfo(int ID, string numberID, string ISBN_ID, string b_date, string r_date, Book_status status)
{
	this->ID = ID;
	strcpy(this->numberID, numberID.c_str());
	strcpy(this->ISBN_ID, ISBN_ID.c_str());
	strcpy(this->b_date,b_date.c_str());
	strcpy(this->r_date, r_date.c_str());
	this->status = status;
}

int BorrowInfo::getID()
{
	return ID;
}

string BorrowInfo::getNumberID()
{
	return string(numberID);
}

string BorrowInfo::getISBN_ID()
{
	return string(ISBN_ID);
}

string BorrowInfo::getB_date()
{
	return string(b_date);
}

string BorrowInfo::getR_date()
{
	return string(r_date);
}

Book_status BorrowInfo::getStatus()
{
	return Book_status(status);
}

void BorrowInfo::setID(int ID)
{
	this->ID = ID;
}

void BorrowInfo::setNumberID(string numberID)
{
	strcpy(this->numberID, numberID.c_str());
}

void BorrowInfo::setISBN_ID(string ISBN_ID)
{
	strcpy(this->ISBN_ID, ISBN_ID.c_str());
}

void BorrowInfo::setB_date(string b_date)
{
	strcpy(this->b_date, b_date.c_str());
}

void BorrowInfo::setR_date(string r_date)
{
	strcpy(this->r_date, r_date.c_str());
}

void BorrowInfo::setStatus(Book_status status)
{
	this->status = status;
}

bool BorrowInfo::save()
{
	Dao d;
	vector<char*> v;
	v.push_back(numberID);
	v.push_back(ISBN_ID);
	v.push_back(b_date);
	v.push_back(r_date);
	v.push_back(reinterpret_cast<char*>(this->status));
	if (this->ID == -1) {//id为-1说明是增加b
		vector<pair<int, char*>> s;
		char* ISBN =strtok(this->ISBN_ID, "-");
		s.push_back(make_pair(0, ISBN));
		vector<map<int, char *>> data = d.select("borrowInfo", s);
		if (!(data[0])[8])//如果该本书的剩余数量<=0，说明不能再借了，直接返回false
			return false;
		if (d.inster_into("borrowInfor", v))//添加成功则返回true
			return true;
	}
	else {//否则则是update这个分类
		if (d.update("borrowInfo", this->ID, v))//更新成功
			return true;
	}
	return false;
}

vector<BorrowInfo> BorrowInfo::getInfoByNumberID(string numberID, Book_status status)
{
	Dao d;
	vector<pair<int, char*> > s;//添加查询条件
	char n[13];
	strcpy(n, numberID.c_str());
	s.push_back(make_pair(0, n));//numberID
	s.push_back(make_pair(4,reinterpret_cast<char*>(status)));//status
	vector<map<int, char *>> data = d.select("borrowInfo", s);
	vector<BorrowInfo> list;
	for (vector<map<int, char *>>::iterator it = data.begin(); it != data.end(); it++) {
		BorrowInfo borrowInfo(reinterpret_cast<int>((*it)[-1]), (*it)[0], (*it)[1], (*it)[2], (*it)[3], (Book_status)reinterpret_cast<int>((*it)[4]));
		list.push_back(borrowInfo);
	}///循环把找出来的字符串数据转成BorrowInfo类型放进list中
	return list;
}

vector<BorrowInfo> BorrowInfo::getNowInfoByNumberID(string numberID)
{
	Dao d;
	vector<pair<int, char*> > s;
	char n[13];
	strcpy(n, numberID.c_str());
	s.push_back(make_pair(0, n));//查询条件numberID
	s.push_back(make_pair(4, reinterpret_cast<char*>(0)));//查询条件status为NORMAL
	vector<BorrowInfo> list;

	vector<map<int, char *>> data = d.select("borrowInfo", s);
	for (vector<map<int, char *>>::iterator it = data.begin(); it != data.end(); it++) {
		BorrowInfo borrowInfo(reinterpret_cast<int>((*it)[-1]), (*it)[0], (*it)[1], (*it)[2], (*it)[3], (Book_status)reinterpret_cast<int>((*it)[4]));
		list.push_back(borrowInfo);
	} // 循环把找出来的字符串数据转成borrowInfo类型放进list中
	s.pop_back();

	s.push_back(make_pair(4, reinterpret_cast<char*>(1)));//查询条件status为 DELAY
	vector<map<int, char *>> data = d.select("borrowInfo", s);
	for (vector<map<int, char *>>::iterator it = data.begin(); it != data.end(); it++) {
		BorrowInfo borrowInfo(reinterpret_cast<int>((*it)[-1]), (*it)[0], (*it)[1], (*it)[2], (*it)[3], (Book_status)reinterpret_cast<int>((*it)[4]));
		list.push_back(borrowInfo);
	}// 循环把找出来的字符串数据转成borrowInfo类型放进list中
	s.pop_back();

	s.push_back(make_pair(4, reinterpret_cast<char*>(3)));//查询条件status为EXCEED
	vector<map<int, char *>> data = d.select("borrowInfo", s);
	for (vector<map<int, char *>>::iterator it = data.begin(); it != data.end(); it++) {
		BorrowInfo borrowInfo(reinterpret_cast<int>((*it)[-1]), (*it)[0], (*it)[1], (*it)[2], (*it)[3], (Book_status)reinterpret_cast<int>((*it)[4]));
		list.push_back(borrowInfo);
	}// 循环把找出来的字符串数据转成borrowInfo类型放进list中
	return list;
}

vector<BorrowInfo> BorrowInfo::getHistoryInfoByNumberID(string numberID)
{
	Dao d;
	vector<pair<int, char*> > s;
	char n[13];
	strcpy(n, numberID.c_str());
	s.push_back(make_pair(0, n));//查询条件只有学号
	vector<map<int, char *>> data = d.select("borrowInfo", s);
	vector<BorrowInfo> list;
	for (vector<map<int, char *>>::iterator it = data.begin(); it != data.end(); it++) {
		BorrowInfo borrowInfo(reinterpret_cast<int>((*it)[-1]), (*it)[0], (*it)[1], (*it)[2], (*it)[3], (Book_status)reinterpret_cast<int>((*it)[4]));
		list.push_back(borrowInfo);
	}// 循环把找出来的字符串数据转成borrowInfo类型放进list中
	return list;
}
