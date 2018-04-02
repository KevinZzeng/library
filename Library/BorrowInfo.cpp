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
	if (this->ID == -1) {//idΪ-1˵��������b
		vector<pair<int, char*>> s;
		char* ISBN =strtok(this->ISBN_ID, "-");
		s.push_back(make_pair(0, ISBN));
		vector<map<int, char *>> data = d.select("borrowInfo", s);
		if (!(data[0])[8])//����ñ����ʣ������<=0��˵�������ٽ��ˣ�ֱ�ӷ���false
			return false;
		if (d.insert_into("borrowInfor", v))//��ӳɹ��򷵻�true
			return true;
	}
	else {//��������update�������
		if (d.update("borrowInfo", this->ID, v))//���³ɹ�
			return true;
	}
	return false;
}

vector<BorrowInfo> BorrowInfo::getInfoByNumberID(string numberID, Book_status status)
{
	Dao d;
	vector<pair<int, char*> > s;//��Ӳ�ѯ����
	char n[13];
	strcpy(n, numberID.c_str());
	s.push_back(make_pair(0, n));//numberID
	s.push_back(make_pair(4,reinterpret_cast<char*>(status)));//status
	vector<map<int, char *>> data = d.select("borrowInfo", s);
	vector<BorrowInfo> list;
	for (vector<map<int, char *>>::iterator it = data.begin(); it != data.end(); it++) {
		BorrowInfo borrowInfo(reinterpret_cast<int>((*it)[-1]), (*it)[0], (*it)[1], (*it)[2], (*it)[3], (Book_status)reinterpret_cast<int>((*it)[4]));
		list.push_back(borrowInfo);
	}///ѭ�����ҳ������ַ�������ת��BorrowInfo���ͷŽ�list��
	return list;
}

vector<BorrowInfo> BorrowInfo::getNowInfoByNumberID(string numberID)
{
	Dao d;
	vector<pair<int, char*> > s;
	char n[13];
	strcpy(n, numberID.c_str());
	s.push_back(make_pair(0, n));//��ѯ����numberID
	s.push_back(make_pair(4, reinterpret_cast<char*>(0)));//��ѯ����statusΪNORMAL
	vector<BorrowInfo> list;

	vector<map<int, char *>> data = d.select("borrowInfo", s);
	for (vector<map<int, char *>>::iterator it = data.begin(); it != data.end(); it++) {
		BorrowInfo borrowInfo(reinterpret_cast<int>((*it)[-1]), (*it)[0], (*it)[1], (*it)[2], (*it)[3], (Book_status)reinterpret_cast<int>((*it)[4]));
		list.push_back(borrowInfo);
	} // ѭ�����ҳ������ַ�������ת��borrowInfo���ͷŽ�list��
	s.pop_back();

	s.push_back(make_pair(4, reinterpret_cast<char*>(1)));//��ѯ����statusΪ DELAY
	for (vector<map<int, char *>>::iterator it = data.begin(); it != data.end(); it++) {
		BorrowInfo borrowInfo(reinterpret_cast<int>((*it)[-1]), (*it)[0], (*it)[1], (*it)[2], (*it)[3], (Book_status)reinterpret_cast<int>((*it)[4]));
		list.push_back(borrowInfo);
	}// ѭ�����ҳ������ַ�������ת��borrowInfo���ͷŽ�list��
	s.pop_back();

	s.push_back(make_pair(4, reinterpret_cast<char*>(3)));//��ѯ����statusΪEXCEED
	data = d.select("borrowInfo", s);
	for (vector<map<int, char *>>::iterator it = data.begin(); it != data.end(); it++) {
		BorrowInfo borrowInfo(reinterpret_cast<int>((*it)[-1]), (*it)[0], (*it)[1], (*it)[2], (*it)[3], (Book_status)reinterpret_cast<int>((*it)[4]));
		list.push_back(borrowInfo);
	}// ѭ�����ҳ������ַ�������ת��borrowInfo���ͷŽ�list��
	return list;
}

vector<BorrowInfo> BorrowInfo::getHistoryInfoByNumberID(string numberID)
{
	Dao d;
	vector<pair<int, char*> > s;
	char n[13];
	strcpy(n, numberID.c_str());
	s.push_back(make_pair(0, n));//��ѯ����ֻ��ѧ��
	vector<map<int, char *>> data = d.select("borrowInfo", s);
	vector<BorrowInfo> list;
	for (vector<map<int, char *>>::iterator it = data.begin(); it != data.end(); it++) {
		BorrowInfo borrowInfo(reinterpret_cast<int>((*it)[-1]), (*it)[0], (*it)[1], (*it)[2], (*it)[3], (Book_status)reinterpret_cast<int>((*it)[4]));
		list.push_back(borrowInfo);
	}// ѭ�����ҳ������ַ�������ת��borrowInfo���ͷŽ�list��
	return list;
}
