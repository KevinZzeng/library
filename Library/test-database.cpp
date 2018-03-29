#include "Dao.h"
#include <iostream>
#include <cstring>
#include "DaoDemo.h"
/****************���Ա�ע*******************
1. find �������ַ����Ҳ���
2. update �������޸�ʧ�ܣ������޸���һ�У����ս�������޸ĵ�һ��
*/


void print_obj(vector<map<int, char*>> &res) {
	for (vector<map<int, char*>>::iterator it = res.begin(); it != res.end(); ++it) {
		DaoDemo  tmp;
		tmp.deserialize(*it);
		tmp.print();
	}
}

using namespace std;
int main()
{
	//d.print();

	Dao  dao;


	//�½���
	/*
	DaoDemo d;
	int column[3] = { sizeof(d.b), sizeof(d.d), sizeof(d.c) }, columns = 3;
	bool ifs[3] = { true, true ,true};
	Table tab = Data::create_table("daodemo", columns, column, ifs);
	*/



	//��������
	/*
	DaoDemo d;
	char q[20] = { "hhhhh" };
	d.b = 4;
	d.d = 4;
	memcpy(d.c, q, 20);
	d.id = -1;
	dao.insert_into("daodemo",d.serialize());
	*/



	//��ȡһ���ű�
	
	//vector<pair<int, char*> > select_con;
	//vector<map<int, char*>> res = dao.select("daodemo", select_con);
	//cout <<"daodemo ������������ " <<res.size()<<endl;
	////��ʾ����
	//print_obj(res);
	
	




	//����������ȡ
	//DaoDemo dd;
	vector<pair<int, char*> > select_con;
	
	//int ���ҷ���
	//int se_b = 999;
	//select_con.push_back(make_pair(0, reinterpret_cast<char *>(&se_b)));
	//vector<map<int, char*>> res = dao.select("daodemo", select_con);
	//cout << "������������������ " << res.size() << endl;
	//print_obj(res);

	//�ַ������ҷ���
	//char * str = "hhhhh";
	//select_con.push_back(make_pair(2, str));
	//vector<map<int, char*>> res = dao.select("daodemo", select_con);
	//cout << "������������������ " << res.size() << endl;
	//print_obj(res);

	//int ���ϲ�ѯ
	//int se_b = 4;
	//int se_d = 1;
	//select_con.push_back(make_pair(0, reinterpret_cast<char *>(&se_b)));
	//select_con.push_back(make_pair(1, reinterpret_cast<char *>(&se_d)));
	//vector<map<int, char*>> res = dao.select("daodemo", select_con);
	//cout << "������������������ " << res.size() << endl;
	//print_obj(res);


	//���Ǹ����õײ�ӿڣ����ǲ��ܲ�ѯ��
	//Table tab = Data::get_table("daodemo");
	//cout << tab.find(1, str).size() << endl;;
	



	//ɾ��һ������
	//cout << "�Ƿ�ɾ���ɹ�? " << (dao.delete_from("daodemo", 1) ? "�ɹ�" : "ʧ��") << endl;

	
	//��������
	//���� int �ֶ�
	//���Ȳ�ѯ������ȷ�� ID != -1
	//vector<pair<int, char*> > select_con;
	//int se_b = 8;
	//select_con.push_back(make_pair(0, reinterpret_cast<char *>(&se_b)));
	//vector<map<int, char*>> res = dao.select("daodemo", select_con);
	//DaoDemo dd;
	//if (res.size() > 0) {
	//	dd.deserialize(res[0]);
	//	cout << "����ǰ���ݣ�" << endl;
	//	dd.print();
	//	//dd.b = 999;
	//	char ss[20] = "sss";
	//	memcpy(dd.c, ss, 20);
	//	Table tab = Data::get_table("daodemo");
	//	cout << "!!!!!!!! " << tab.change(dd.id, 1, dd.c) << endl;

	//	//cout << "���³ɹ��� " << (dao.update("daodemo", dd.id, dd.serialize()) ? "�ɹ�" : "ʧ��") << endl;
	//	dd.deserialize(dao.getById("daodemo",dd.id));
	//	cout << "���º����ݣ�" << endl;
	//	dd.print();
	//}

	//�����޸Ĺ���
	//map<int, char*> mm = dao.getById("daodemo", 0);
	//DaoDemo dd;
	//dd.deserialize(mm);
	//cout << "����ǰ���ݣ�" << endl;
	//dd.print();
	//dd.d = 4;
	///*char ss[20] = "sss";
	//memcpy(dd.c, ss, 20);
	//Table tab = Data::get_table("daodemo");
	//cout << "!!!!!!!! " << tab.change(dd.id, 1, dd.c) << endl;*/

	//cout << "���³ɹ��� " << (dao.update("daodemo", dd.id, dd.serialize()) ? "�ɹ�" : "ʧ��") << endl;
	//dd.deserialize(dao.getById("daodemo",dd.id));
	//cout << "���º����ݣ�" << endl;
	//dd.print();



	//���� char * �ֶ�
	/*vector<pair<int, char*> > select_con;
	int se_b = 1769239923;
	select_con.push_back(make_pair(0, reinterpret_cast<char *>(&se_b)));
	vector<map<int, char*>> res = dao.select("daodemo", select_con);
	DaoDemo dd;
	if (res.size() > 0) {
		dd.deserialize(res[0]);
		cout << "����ǰ���ݣ�" << endl;
		dd.print();
		char *aaa = "aaa";
		memcpy(dd.c, aaa, 20);
		cout << "���³ɹ��� " << (dao.update("daodemo", dd.id, dd.serialize()) ? "�ɹ�" : "ʧ��") << endl;
		dd.deserialize(dao.getById("daodemo", dd.id));
		cout << "���º����ݣ�" << endl;
		dd.print();
	}*/

	return 0;
}