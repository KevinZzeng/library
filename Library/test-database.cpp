#include "Dao.h"
#include <iostream>
#include <cstring>
#include "DaoDemo.h"

using namespace std;
int main()
{

	DaoDemo d;
	char q[20] = { "4rtweer" };
	d.b = 3;
	memcpy(d.c, q, 20);
	d.id = -1;

	d.print();

	int column[2] = { sizeof(d.b), sizeof(d.c)}, columns = 2;
	bool ifs[2] = { true, true };
	//Table tab = Data::create_table("daodemo5", columns, column, ifs);

	cout << "ss" << endl;
/*
	for (int i = 0; i < 3; i++)
		cout << column[i] << "\t";
	cout << endl;*/
	//cout << "create ok!" << endl;



	//cout<<dao.inster_into("daodemo", d.serialize());

	//Table tab = Data::get_table("daodemo");
	Dao  dao;
	//vector<int>  v  =tab.get_column_length();
	dao.inster_into("daodemo5",d.serialize());


	
	//int rowLen = 0;
	//vector<int> t_info;
	//t_info.push_back(column[0]);
	//t_info.push_back(column[1]);

	//vector<char *> v = d.serialize();


	//for (vector<int>::iterator it = t_info.begin(); it != t_info.end(); ++it) {
	//	rowLen += *it;
	//}

	//char *res = new char[rowLen];
	//int step = 0, i = 0;
	//for (vector<char *>::iterator it = v.begin(); it != v.end(); ++it) {
	//	memcpy(res + step, *it, t_info[i]);
	//	step += t_info[i++];
	//}


	//DaoDemo dd;

	//
	//char *row = tab.get(0);
	//map<int, char *> res;
	////构造 char *
	//int step = 0;
	//for (int i = 0; i < columns; i++) {
	//	char *t = new char[t_info[i]];
	//	memcpy(t, row + step, t_info[i]);
	//	res.insert(pair<int, char*>(i, t));
	//	step += t_info[i];
	//}

	////插入ID key：-1  value：ID值
	//char *t = new char[4];
	//int id = 48;
	//res.insert(pair<int, char *>(-1, reinterpret_cast<char *>(&id)));






	/*for (int i = 0; i < rowLen; i++)
		printf("%d", *(res + i));
*/

	//存入数据库

	//cout<<tab.add(res);
	
	/*

	string s = "dfsdf";
	char p[20];
	int w[2] = { 5,3 };
	bool e[2] = { 1,0 };
	Table tab = Data::create_table(s, 2, w, e);
	int id = tab.add(q);
	int len = tab.size();
	bool t = tab.del(id);
	id = tab.add(q);
	vector<pair<int, char*> > a = tab.get_all();
	for (int i = 0; i < a.size(); i++) {
		cout << a[i].first << ' ' << a[i].second << endl;
		delete[] a[i].second;
	}*/
	return 0;
}