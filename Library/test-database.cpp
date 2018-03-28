#include "Dao.h"
#include <iostream>
#include <cstring>
#include "DaoDemo.h"
using namespace std;
int main()
{

	DaoDemo d;
	char q[20] = { "4rtweer" };
	d.b = 1;
	memcpy(d.c, q, 20);
	d.id = -1;

	d.print();

	int column[2] = { sizeof(d.b), sizeof(d.c)}, columns = 2;
	bool ifs[2] = { true, true };
	//Table tab = Data::create_table("daodemo", columns, column, ifs);
/*
	for (int i = 0; i < 3; i++)
		cout << column[i] << "\t";
	cout << endl;*/
	//cout << "create ok!" << endl;


	//Table tab = Data::get_table("daodemo");
	//Dao dao;
	//cout<<dao.inster_into("daodemo", d.serialize());

	Table tab = Data::get_table("daodemo");
	tab.get_column_length();
	

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