//#include "Dao.h"
//#include <iostream>
//#include <cstring>
//#include "DaoDemo.h"
//
//
//void print_obj(vector<map<int, char*>> &res) {
//	for (vector<map<int, char*>>::iterator it = res.begin(); it != res.end(); ++it) {
//		DaoDemo  tmp;
//		tmp.deserialize(*it);
//		tmp.print();
//	}
//}
//
//using namespace std;
//int main()
//{
//
//	Dao  dao;
//
//
//	//�½���
//	
//	//DaoDemo d;
//	//int column[3] = { sizeof(d.b), sizeof(d.d), sizeof(d.c) }, columns = 3;
//	//bool ifs[3] = { true, true ,true};
//	//DataSys::create("daodemo", columns, column, ifs);
//	
//
//
//
//	//��������
//	
//	//DaoDemo d;
//	//char q[20] = { "a0" };
//	//for (int i = 0; i < 20; i++)
//	//	printf("%d", q[i]);
//	//printf("\n");
//	//d.b = 8;
//	//d.d = 4;
//	//memcpy(d.c, q, 20);
//	//d.id = -1;
//	//dao.insert_into("daodemo",d.serialize());
//	
//
//
//
//	//��ȡһ���ű�
//	
//	//vector<pair<int, char*> > select_con;
//	//vector<map<int, char*>> res = dao.select("daodemo", select_con);
//	//cout <<"daodemo ������������ " <<res.size()<<endl;
//	////��ʾ����
//	//print_obj(res);
//	
//
//	//����������ȡ
//	//DaoDemo dd;
//	//vector<pair<int, char*> > select_con;
//	
//	////int ���ҷ���
//	//int se_b = 8;
//	//select_con.push_back(make_pair(0, reinterpret_cast<char *>(&se_b)));
//	//vector<map<int, char*>> res = dao.select("daodemo", select_con);
//	//cout << "������������������ " << res.size() << endl;
//	//print_obj(res);
//
//	//�ַ������ҷ���
//	//char  str[20] = { "hhhhhhhhhhhhhhhhhh0" };
//	//for (int i = 0; i < 20; i++)
//	//{
//	//	printf("%d", str[i]);
//	//}
//	//select_con.push_back(make_pair(2, str));
//	//vector<map<int, char*>> res = dao.select("daodemo", select_con);
//	//cout << "������������������ " << res.size() << endl;
//	//print_obj(res);
//
//	//int ���ϲ�ѯ
//	//int se_b = 8;
//	//int se_d = 4;
//	//select_con.push_back(make_pair(0, reinterpret_cast<char *>(&se_b)));
//	//select_con.push_back(make_pair(1, reinterpret_cast<char *>(&se_d)));
//	//vector<map<int, char*>> res = dao.select("daodemo", select_con);
//	//cout << "������������������ " << res.size() << endl;
//	//print_obj(res);
//
//
//	//ɾ��һ������
//	//cout << "�Ƿ�ɾ���ɹ�? " << (dao.delete_from("daodemo", 1) ? "�ɹ�" : "ʧ��") << endl;
//
//	
//	//��������
//	//���� int �ֶ�
//	//���Ȳ�ѯ������ȷ�� ID != -1
//	//vector<pair<int, char*> > select_con;
//	//int se_b = 8;
//	//select_con.push_back(make_pair(0, reinterpret_cast<char *>(&se_b)));
//	//vector<map<int, char*>> res = dao.select("daodemo", select_con);
//	//DaoDemo dd;
//	//if (res.size() > 0) {
//	//	dd.deserialize(res[0]);
//	//	cout << "����ǰ���ݣ�" << endl;
//	//	dd.print();
//	//	//dd.b = 999;
//	//	char ss[20] = "sss";
//	//	memcpy(dd.c, ss, 20);
//	//	Table tab = Data::get_table("daodemo");
//	//	cout << "!!!!!!!! " << tab.change(dd.id, 1, dd.c) << endl;
//
//	//	//cout << "���³ɹ��� " << (dao.update("daodemo", dd.id, dd.serialize()) ? "�ɹ�" : "ʧ��") << endl;
//	//	dd.deserialize(dao.getById("daodemo",dd.id));
//	//	cout << "���º����ݣ�" << endl;
//	//	dd.print();
//	//}
//
//	//�����޸Ĺ���
//	//map<int, char*> mm = dao.getById("daodemo", 5);
//	//DaoDemo dd;
//	//dd.deserialize(mm);
//	//cout << "����ǰ���ݣ�" << endl;
//	//dd.print();
//	//dd.d = 5;
//	//dd.b =8;
//	//char ss[20] = "susususus";
//	//memcpy(dd.c, ss, 20);
//
//	//cout << "���³ɹ��� " << (dao.update("daodemo", dd.id, dd.serialize()) ? "�ɹ�" : "ʧ��") << endl;
//	//dd.deserialize(dao.getById("daodemo",dd.id));
//	//cout << "���º����ݣ�" << endl;
//	//dd.print();
//
//
//	//ģ����ѯ
//	//vector<map<int, char*>> res = dao.select("daodemo", vector<pair<int, char *> >(), 2, "1");
//	//cout << "������������������ " << res.size() << endl;
//	//print_obj(res);
//
//
//
//	return 0;
//}