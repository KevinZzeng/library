#pragma once
#include <string>
#include <list>
using namespace std;

class HH {

public:
	HH(string aa, int b, double c) :aa(aa), b(b), c(c) {};
	string aa;
	int b;
	double c;
	static list<HH> getAll();
	HH() {};
	HH(HH &ch);
};