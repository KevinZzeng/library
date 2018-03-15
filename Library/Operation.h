#pragma once
#include <string>
#include <vector>
#include "Admin.h"
using namespace std;
class Operation {

private:
	int id;
	string numberID;
	string operation;
	string date;
public:
	bool save(Admin &ad);
	static vector<Operation> getAllOperaions();
};