#include "HH.h"
#include <iostream>
list<HH> HH::getAll()
{
	int len = 5;
	list<HH> v;
	cout << "begin for" << endl;
	for (int i = 0; i < len; i++)
		v.push_back(HH("a"+i, i, 50 / 5));

	/*for (int j = 0; j < len; j++)
		cout << v[j].b << endl;*/

	cout << "·µ»Øµ÷ÓÃ" << endl;
	return v ;
}

HH::HH(HH & ch)
{
	aa = ch.aa;
	b = ch.b;
	c = ch.c;
	cout << "copy func" << endl;
}
