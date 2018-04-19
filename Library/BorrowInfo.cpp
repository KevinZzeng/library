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
	if (this->ID == -1) {//idΪ-1˵��������b
		vector<pair<int, char*>> s;
		char* ISBN =strtok(this->ISBN_ID, "-");
		s.push_back(make_pair(0, ISBN));
		vector<map<int, char *>> data = d.select("book", s);
		if (data.empty()||!(data[0])[8])//�Ȿ�鲻���ڻ�����ñ����ʣ������<=0��˵�������ٽ��ˣ�ֱ�ӷ���false
			return false;
		if (d.insert_into("borrowInfo", v))//��ӳɹ��򷵻�true
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
	vector<map<int, char *>> data0 = d.select("borrowInfo", s);
	string  now = Utils::getNowTime();
	for (vector<map<int, char *>>::iterator it = data0.begin(); it != data0.end(); it++) {
		Book_status sta = (Book_status)*reinterpret_cast<int*>((*it)[4]);
		int a = Utils::compareTime(now, (*it)[3]);
		if (Utils::compareTime(now, (*it)[3]) < 0 && (Book_status)*reinterpret_cast<int*>((*it)[4]) != Book_DONE &&(Book_status)*reinterpret_cast<int*>((*it)[4])!= Book_EXCEED) {
			
			BorrowInfo ans(*reinterpret_cast<int*>((*it)[-1]), (*it)[0], (*it)[1], (*it)[2], (*it)[3], Book_EXCEED);
			ans.save();
		}
	}//�޸�EXCEED״̬
	char n[13];
	strcpy(n, numberID.c_str());
	s.push_back(make_pair(0, n));//numberID
	vector<map<int, char *>> data = d.select("borrowInfo", s);
	vector<BorrowInfo> list;
	for (vector<map<int, char *>>::iterator it = data.begin(); it != data.end(); it++) {
		if ((Book_status)*reinterpret_cast<int*>((*it)[4]) == status) {//status��ѯ����
			BorrowInfo borrowInfo(*reinterpret_cast<int*>((*it)[-1]), (*it)[0], (*it)[1], (*it)[2], (*it)[3], (Book_status)*reinterpret_cast<int*>((*it)[4]));
			list.push_back(borrowInfo);
		}
	}///ѭ�����ҳ������ַ�������ת��BorrowInfo���ͷŽ�list��
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
	}//�޸�EXCEED״̬
	char n[13];
	strcpy(n, numberID.c_str());
	s.push_back(make_pair(0, n));//��ѯ����numberID
	vector<BorrowInfo> list;
	vector<map<int, char *>> data = d.select("borrowInfo", s);
	for (vector<map<int, char *>>::iterator it = data.begin(); it != data.end(); it++) {
		if ((Book_status)*reinterpret_cast<int*>((*it)[4]) != Book_DONE) {//status��ѯ����
			BorrowInfo borrowInfo(*reinterpret_cast<int*>((*it)[-1]), (*it)[0], (*it)[1], (*it)[2], (*it)[3], (Book_status)*reinterpret_cast<int*>((*it)[4]));
			list.push_back(borrowInfo);
		}
	} // ѭ�����ҳ������ַ�������ת��borrowInfo���ͷŽ�list��
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
	}//�޸�EXCEED״̬
	char n[13];
	strcpy(n, numberID.c_str());
	s.push_back(make_pair(0, n));//��ѯ����ֻ��ѧ��
	vector<map<int, char *>> data = d.select("borrowInfo", s);
	vector<BorrowInfo> list;
	for (vector<map<int, char *>>::iterator it = data.begin(); it != data.end(); it++) {
		BorrowInfo borrowInfo(*reinterpret_cast<int*>((*it)[-1]), (*it)[0], (*it)[1], (*it)[2], (*it)[3], (Book_status)*reinterpret_cast<int*>((*it)[4]));
		list.push_back(borrowInfo);
	}// ѭ�����ҳ������ַ�������ת��borrowInfo���ͷŽ�list��
	return list;
}
