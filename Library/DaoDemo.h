#pragma once
#include <string>
#include <list>
#include "Dao.h"
#include <iostream>
using namespace std;

class DaoDemo {

public:

	void print() {

		cout << "id:" << this->id << " b:" << this->b <<"  d:"<<this->d<< "  string: " << this->c << endl;

	}
	//�����л�����,���� Dao �� selcet  getById �����ķ���ֵ
	void deserialize(map<int, char*> &m) {
		this->id =  *(reinterpret_cast<int *>(m[-1]));		//-1��idֵ
		this->b = *(reinterpret_cast<int *>(m[0]));			//0 �� b�� Ҳ���ǵ�һ��
		this->d = *(reinterpret_cast<int *>(m[1]));
		memcpy(this->c, m[2], 20);
	}

	//���л����������� inster_into update ��������
	vector<char *> serialize() {
		vector<char *> r;
		r.push_back(reinterpret_cast<char *>(&this->b));
		r.push_back(reinterpret_cast<char *>(&this->d));
		r.push_back(c);
		return r;
	}


	int id;
	int b;
	int d;
	char  c[20];
};