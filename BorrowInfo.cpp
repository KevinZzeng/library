#include "BorrowInfo.h"


BorrowInfo::BorrowInfo(int ID, string numberID, string ISBN_ID, string b_date, string r_date, Book_status status)
{
	init();
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
	v.push_back(reinterpret_cast<char*>(&this->status));
	if (this->ID == -1) {//id为-1说明是增加b
		vector<pair<int, char*>> s;
		char* ISBN =strtok(this->ISBN_ID, "-");
		s.push_back(make_pair(0, ISBN));
		vector<map<int, char *>> data = d.select("book", s);
		if (data.empty()||!(data[0])[8])//这本书不存在或如果该本书的剩余数量<=0，说明不能再借了，直接返回false
			return false;
		if (d.insert_into("borrowInfo", v))//添加成功则返回true
			return true;
	}
	else {//否则则是update这个分类
		if (d.update("borrowInfo", this->ID, v))//更新成功
			return true;
	}
	return false;
}

bool BorrowInfo::returnBook(BorrowInfo b)
{
	b.setStatus(Book_DONE);
	if (b.save())
		return true;
	return false;
}

bool BorrowInfo::renewBook(BorrowInfo b)
{
	if (Utils::compareTime(Utils::getNowTime(), b.getR_date()) <= 0 && b.getStatus() == Book_NORMAL) {//如果当前时间<=归还时间以及借书状态为正常才可以续借
		b.setR_date(Utils::addTime(b.getR_date(), 7));//续借加7天
		if (b.save())
			return true;
	}
	return false;
}

vector<Student> BorrowInfo::getStudentInfoByISBN(string ISBN )
{
	Dao d;
	vector<pair<int, char*> > s;//添加查询条件
	vector<map<int, char *>> data0 = d.select("borrowInfo", s);
	vector<Student> res;
	for (vector<map<int, char *>>::iterator it = data0.begin(); it != data0.end(); it++) {
		char* ISBN0 = strtok((*it)[1], "-");
		if (ISBN == string(ISBN) && (Book_status)*reinterpret_cast<int*>((*it)[4]) != Book_DONE ){
			vector<Student> ans = Student::getStudent("",(*it)[0], -1);//根据numberID查student信息；
			res.push_back(ans[0]);
		}
	}
	return res;
}

vector<BorrowInfo> BorrowInfo::getInfoByNumberID(string numberID, Book_status status)
{
	Dao d;
	vector<pair<int, char*> > s;//添加查询条件
	vector<map<int, char *>> data0 = d.select("borrowInfo", s);
	string  now = Utils::getNowTime();
	for (vector<map<int, char *>>::iterator it = data0.begin(); it != data0.end(); it++) {
		Book_status sta = (Book_status)*reinterpret_cast<int*>((*it)[4]);
		int a = Utils::compareTime(now, (*it)[3]);
		if (Utils::compareTime(now, (*it)[3]) < 0 && (Book_status)*reinterpret_cast<int*>((*it)[4]) != Book_DONE &&(Book_status)*reinterpret_cast<int*>((*it)[4])!= Book_EXCEED) {
			
			BorrowInfo ans(*reinterpret_cast<int*>((*it)[-1]), (*it)[0], (*it)[1], (*it)[2], (*it)[3], Book_EXCEED);
			ans.save();
		}
	}//修改EXCEED状态
	char n[13];
	strcpy(n, numberID.c_str());
	s.push_back(make_pair(0, n));//numberID
	vector<map<int, char *>> data = d.select("borrowInfo", s);
	vector<BorrowInfo> list;
	for (vector<map<int, char *>>::iterator it = data.begin(); it != data.end(); it++) {
		if ((Book_status)*reinterpret_cast<int*>((*it)[4]) == status) {//status查询条件
			BorrowInfo borrowInfo(*reinterpret_cast<int*>((*it)[-1]), (*it)[0], (*it)[1], (*it)[2], (*it)[3], (Book_status)*reinterpret_cast<int*>((*it)[4]));
			list.push_back(borrowInfo);
		}
	}///循环把找出来的字符串数据转成BorrowInfo类型放进list中
	return list;
}

vector<BorrowInfo> BorrowInfo::getNowInfoByNumberID(string numberID)
{
	Dao d;
	vector<pair<int, char*> > s;
	vector<map<int, char *>> data0 = d.select("borrowInfo", s);
	for (vector<map<int, char *>>::iterator it = data0.begin(); it != data0.end(); it++) {
		if (Utils::compareTime(Utils::getNowTime(), (*it)[3]) < 0 && (Book_status)*reinterpret_cast<int*>((*it)[4]) != Book_DONE && (Book_status)*reinterpret_cast<int*>((*it)[4]) != Book_EXCEED) {
			BorrowInfo ans(*reinterpret_cast<int*>((*it)[-1]), (*it)[0], (*it)[1], (*it)[2], (*it)[3], Book_EXCEED);
			ans.save();
		}
	}//修改EXCEED状态
	char n[13];
	strcpy(n, numberID.c_str());
	s.push_back(make_pair(0, n));//查询条件numberID
	vector<BorrowInfo> list;
	vector<map<int, char *>> data = d.select("borrowInfo", s);
	for (vector<map<int, char *>>::iterator it = data.begin(); it != data.end(); it++) {
		if ((Book_status)*reinterpret_cast<int*>((*it)[4]) != Book_DONE) {//status查询条件
			BorrowInfo borrowInfo(*reinterpret_cast<int*>((*it)[-1]), (*it)[0], (*it)[1], (*it)[2], (*it)[3], (Book_status)*reinterpret_cast<int*>((*it)[4]));
			list.push_back(borrowInfo);
		}
	} // 循环把找出来的字符串数据转成borrowInfo类型放进list中
	return list;
}

vector<BorrowInfo> BorrowInfo::getHistoryInfoByNumberID(string numberID)
{
	Dao d;
	vector<pair<int, char*> > s;
	vector<map<int, char *>> data0 = d.select("borrowInfo", s);
	for (vector<map<int, char *>>::iterator it = data0.begin(); it != data0.end(); it++) {
		if (Utils::compareTime(Utils::getNowTime(), (*it)[3]) < 0 && (Book_status)*reinterpret_cast<int*>((*it)[4]) != Book_DONE && (Book_status)*reinterpret_cast<int*>((*it)[4]) != Book_EXCEED) {
			BorrowInfo ans(*reinterpret_cast<int*>((*it)[-1]), (*it)[0], (*it)[1], (*it)[2], (*it)[3], Book_EXCEED);
			ans.save();
		}
	}//修改EXCEED状态
	char n[13];
	strcpy(n, numberID.c_str());
	s.push_back(make_pair(0, n));//查询条件只有学号
	vector<map<int, char *>> data = d.select("borrowInfo", s);
	vector<BorrowInfo> list;
	for (vector<map<int, char *>>::iterator it = data.begin(); it != data.end(); it++) {
		BorrowInfo borrowInfo(*reinterpret_cast<int*>((*it)[-1]), (*it)[0], (*it)[1], (*it)[2], (*it)[3], (Book_status)*reinterpret_cast<int*>((*it)[4]));
		list.push_back(borrowInfo);
	}// 循环把找出来的字符串数据转成borrowInfo类型放进list中
	return list;
}
