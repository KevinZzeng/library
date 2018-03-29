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
	//反序列化函数,处理 Dao 中 selcet  getById 函数的返回值
	void deserialize(map<int, char*> &m) {
		this->id =  *(reinterpret_cast<int *>(m[-1]));		//-1是id值
		this->b = *(reinterpret_cast<int *>(m[0]));			//0 是 b， 也就是第一项
		this->d = *(reinterpret_cast<int *>(m[1]));
		memcpy(this->c, m[2], 20);
	}

	//序列化函数，处理 inster_into update 函数参数
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