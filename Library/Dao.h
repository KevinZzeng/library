#pragma once

/*************** notice *************
TODO���ײ��ṩһ�����ر��������ݵĽӿ�

*/

/*
ÿ�����м��� ID ��Ϊ��ά�����ݷ���
ÿ����д�����л������������л�����
���л������� ��ÿ���ֱ��ֶν������л�
�����л������� Dao ���ṩ���� ���л������ݺ������ж�Ӧ�ĳ�Ա˳���ţ��㸺��󶨵�������
*/


//���� char �������÷�ʹ����Ӧ�� delete
//char * res ���� new �����ģ�ʹ����� delete�����ݿ�����
#include "Data.h"
#include "Table.h"
#include <map>
#include <vector>


class Dao {
private :
	Table _table;
	string _tableName;

	//�����û����õ����ݿ����ƻ�ȡ���ݿ⣬��� _tableName �͵���һ���������»�ȡ���и����⣿�����»�ȡ���ݿ�Ļ������ݸ����˿��Բ鵽�µ������
	void init(string tableName);

	//ת�����ݿ�ԭʼ char *  ������
	map<int, char *> transCharPtr2Map(string tableName, int id, char * row);
public:

	Dao();

	//inster_into vector <value> value �����л��ĳ�Ա����������˳��д��vector
	bool insert_into(const string tableName, vector<char *> &v);
	
	//updae vector <value> value �����л��ĳ�Ա����������˳��д��vector
	bool update(const string tableName, int id, vector<char *> &v);

	bool delete_from(const string tableName, int id);


	//ͨ��ID ���ٷ�������, <int ,char *> int �����Ա����˳�� -1��ʾID�� char *����������
	map<int, char *> getById(const string tableName, int id);


	//select vector<map<int, char *>> ��Ų�ѯ������������ʵ��
	//����һ�� map ���飬ÿ�� map���������ÿ������ı�������-1 ��ʾID
	vector<map<int, char *>> select(const string tableName, vector<pair<int, char*> >&v);
	
};