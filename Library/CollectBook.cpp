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
	if (this->ID == -1) {//idΪ-1˵��������b
		vector<pair<int, char*>> s;
		s.push_back(make_pair(0, this->ISBN));
		vector<map<int, char *>> data = d.select("book", s);
		if (data.empty())//������鲻���ڣ����ܱ�ԤԼ
			return false;
		vector < map<int, char*> >::iterator ans = data.begin();
		if ((*ans)[8])//������ܽ�����ԤԼ
			return false;
		s.pop_back();
		s.push_back(make_pair(1, this->ISBN));
		data = d.select("collectBook", s);
		for (ans = data.begin(); ans != data.end(); ans++) {
			if ((*ans)[0] == numberID) {//����ñ����Ѿ������û�ԤԼ�ˣ�˵��������ԤԼ�ˣ�ֱ�ӷ���false
				return false;
			}
		}
		if (d.insert_into("collectBook", v))//��ӳɹ��򷵻�true
			return true;
	}
	else {//��������update����ԤԼ��¼
		if (d.update("collectBook", this->ID, v))//���³ɹ�
			return true;
	}
	return false;
}

bool CollectBook::destory()
{
	Dao d;
	if (this->ID != -1) {
		if (d.delete_from("collectBook", this->ID));
		return true;//ɾ������ԤԼ��¼
	}
	return false;
}

vector<CollectBook> CollectBook::getCollectionByNumberID(string numberID)
{
	Dao d;
	vector<pair<int, char*> > s;//��Ӳ�ѯ����
	char n[13];
	strcpy(n, numberID.c_str());
	s.push_back(make_pair(0, n));//numberID
	vector<map<int, char *>> data = d.select("collectBook", s);//��������
	vector<CollectBook> list;
	for (vector<map<int, char *>>::iterator it = data.begin(); it != data.end(); it++) {
		CollectBook c_book(*reinterpret_cast<int*>((*it)[-1]), (*it)[0], (*it)[1]);
		list.push_back(c_book);//ѭ�����ҳ������ַ�������ת��collectBook���ͷŽ�list��
	}
	return list;
}
