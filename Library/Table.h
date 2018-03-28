#pragma once
#include <set>
#include <vector>
#include "File.h"
#include <fstream>
using namespace std;

//class Table {
//public:
//	int add(char *data) {};
//	set<int> find(int colum, char * key) { return set<int>(); }
//	char *get(int id) { return ""; }
//	vector<pair<int, char *> > get_all() { return vector<pair<int, char *> >(); }
//	bool del(int id) {}
//	void change(int id, int colum, char* attr) {}
//	vector<int> get_column_length() { return vector<int>(); }
//};

class Table
{
public:
	Table(string _name, int _num, int _len[], bool _ifsearch[]);     ///�½���(�����������������ʽ�������Ƿ�μ���)
	
	Table(string _name);  ///�򿪱�

	Table();
	
	int add(char* data);	///�������Ϣ
	
	set<int> find(int colum, char* key);///���ݵڼ��ؼ���,��ȡ���������������е�id


	char* get(int id); /// ������id��ȡ��Ӧ��,,�˴��д�����,�׵����ڴ���ʧ�����Ƽ�ʹ�� ���delete
	
	bool get(char* a, int id); /// �Ƽ�ʹ�õķ���
	
	bool change(int id, int column, char * attr);

	int size();///������

	vector<int> get_column_length();

	vector< pair<int, char*> > get_all();

	bool del(int id); ///������idɾ����

protected:
	int get_len_sum();
	
	char* order();
	
private:
	string name;
	int num;         ///����
	vector<int> len;           ///ÿһ�еĿ��
	vector<bool> if_search;    ///�Ƿ�֧������
	File table;
};