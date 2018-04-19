#pragma once
#include "Blist.h"
class DataSys
{
public:
	static void create(string _name, int _num, int _len[], bool _ifsearch[]); ///�½���(�����������������ʽ�������Ƿ�μ���)
	static DataSys* getData(string name);///������ݱ�ָ��
	static void Sysclose(string name);///�ر�ָ���������ݱ�
	void close();///�ر����ݹ����������ڳ������ǰ���ø÷����Է�ֹ������ʧ������һ������Ч����ͬ
	string getName();///���ص�ǰ����򿪵ı���
	int add(char* data);	///���봫�����Ϣ
	bool del(int id); ///������idɾ����
	vector<int> find(int column, char* key);///���ݵڼ��ؼ���,��ȡ���������������е�id ����������Ϊ�Ǽ��������Զ����ñ������ң�
	vector<int> fuzzy_search(int column, char* key);///ģ������
	bool change(int id, int column, char * attr);///�ı�ָ����ָ���е�����
	char* get(int id); /// ������id��ȡ��Ӧ��,�˴��д�����,�׵����ڴ���ʧ�����Ƽ�ʹ�� ���delete
	bool get(char* a, int id); /// �Ƽ�ʹ�õķ���
	vector< pair<int, char*> > get_by_key(int column, char* key);///���ݵڼ��ؼ���,��ȡ����������������������id  char*��delete
	void del_by_key(int column, char * key);///ֱ�Ӹ�������key��ɾ���������������
	int size();///������
	vector<int> get_column_length();///��ȡÿһ�еĿ��
	vector< pair<int, char*> > get_all();///�����������ݱ����������  char*��delete

protected:

	DataSys(string _name);  ///�򿪱�

	int get_len_sum();

	vector<int> find_onybyone(int column, char * key);///��������

private:
	static map<string, DataSys*> Sys;
	string name;
	int num;         ///����
	vector<int> len;           ///ÿһ�еĿ��
	vector<bool> if_search;    ///�Ƿ�֧������
	FileOp table;
	Blist blist;
};