#include "BookCategory.h"

BookCategory::BookCategory()
{
}

BookCategory::BookCategory(int ID, string category)
{
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
	vector<map<int, char *>> data = d.select("book", s);//����category��ȡ����������ֵ�id���ж�����������ִ治����
	if (!data.empty()) {//���������಻���ڣ��ſ������ӻ����޸ĳ��������
		if (this->ID == -1) {//idΪ-1˵���������������
			if (d.inster_into("bookCategory", v))//��ӳɹ��򷵻�true
				return true;
		}
		else {//��������update�������
			if (d.update("bookCategory", this->ID, v)) // ��ӳɹ��򷵻�true
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
			return true;//ɾ���������
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
		m.insert(make_pair(reinterpret_cast<int>((*it)[-1]), (*it)[0]));
	}// ѭ�����ҳ������ַ�������ת��category���ͷŽ�map��

	return m;
}

int BookCategory::getCategoryIdByName(string categoryName)
{
	Dao d;
	vector<pair<int, char*> > s;
	char n[40];
	strcpy(n, categoryName.c_str());
	s.push_back(make_pair(0, n));//���ݷ������ֲ��ҷ���ID
	vector<map<int, char *>> data = d.select("bookCategory", s);
	map<int, string> m;
	if (!data.empty()) {//�����Ϊ��
		return reinterpret_cast<int>((data[0])[-1]);
	}
	return -1;//û�ҵ�����-1
}
