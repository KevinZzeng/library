#pragma once
#include <string>
#include <list>
#include "Dao.h"
using namespace std;

class DaoDemo {

private:

	//�����л�����,���� Dao �� selcet  getById �����ķ���ֵ
	void deserialize(map<int, char*> &m) {
		this->id =  reinterpret_cast<int>(m[-1]);		//-1��idֵ
		this->b = reinterpret_cast<int>(m[0]);			//0 �� b�� Ҳ���ǵ�һ��
		memcpy(this->c, m[1], 20);
	}

	//���л����������� inster_into update ��������
	vector<char *> serialize() {
		vector<char *> r;
		r.push_back(reinterpret_cast<char *>(this->b));
		r.push_back(c);
		return r;
	}


public:
	int id;
	int b;
	char  c[20];
};