#pragma once
#include <string>
#include "Table.h"
using namespace std;
//class Data {
//public:
//	bool static create_table(string name, int cloum, int length[], bool if_search[]) { return true; };
//	static Table get_table(string name) { return Table(); };
//	bool static del_table(string name) { return true; };
//	
//};

class Data
{
public:
	static Table create_table(string name, int num, int len[], bool ifsearch[]);///�½���(�����������������ʽ�������Ƿ�μ���)
	
	static void delete_table(string name);
	
	static Table get_table(string name);
};