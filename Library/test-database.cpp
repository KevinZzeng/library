#include "Dao.h"
#include <iostream>
#include <cstring>
#include "DaoDemo.h"


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


	//新建表
	/*
	DaoDemo d;
	int column[3] = { sizeof(d.b), sizeof(d.d), sizeof(d.c) }, columns = 3;
	bool ifs[3] = { true, true ,true};
	Table tab = Data::create_table("daodemo", columns, column, ifs);
	*/



	//增加数据
	
	//DaoDemo d;
	//char q[21] = { "hhhhhhhhhhhhhhhhhhhh" };
	//for (int i = 0; i < 20; i++)
	//	printf("%d", q[i]);
	//printf("\n");
	//d.b = 8;
	//d.d = 4;
	//memcpy(d.c, q, 20);
	//d.id = -1;
	//dao.insert_into("daodemo",d.serialize());
	



	//获取一整张表
	
	//vector<pair<int, char*> > select_con;
	//vector<map<int, char*>> res = dao.select("daodemo", select_con);
	//cout <<"daodemo 表数据条数： " <<res.size()<<endl;
	////显示出来
	//print_obj(res);
	

	//根据条件获取
	//DaoDemo dd;
	//vector<pair<int, char*> > select_con;
	
	//int 查找方法
	//int se_b = 999;
	//select_con.push_back(make_pair(0, reinterpret_cast<char *>(&se_b)));
	//vector<map<int, char*>> res = dao.select("daodemo", select_con);
	//cout << "符合条件数据条数： " << res.size() << endl;
	//print_obj(res);

	//字符串查找方法
	//char  str[20] = { "hhhhh" };
	//for (int i = 0; i < 20; i++)
	//{
	//	printf("%d", str[i]);
	//}
	//select_con.push_back(make_pair(2, str));
	//vector<map<int, char*>> res = dao.select("daodemo", select_con);
	//cout << "符合条件数据条数： " << res.size() << endl;
	//print_obj(res);

	//int 复合查询
	//int se_b = 4;
	//int se_d = 1;
	//select_con.push_back(make_pair(0, reinterpret_cast<char *>(&se_b)));
	//select_con.push_back(make_pair(1, reinterpret_cast<char *>(&se_d)));
	//vector<map<int, char*>> res = dao.select("daodemo", select_con);
	//cout << "符合条件数据条数： " << res.size() << endl;
	//print_obj(res);


	//这是个调用底层接口，还是不能查询到
	//Table tab = Data::get_table("daodemo");
	//cout << tab.find(1, str).size() << endl;;
	



	//删除一条数据
	//cout << "是否删除成功? " << (dao.delete_from("daodemo", 1) ? "成功" : "失败") << endl;

	
	//更新数据
	//更新 int 字段
	//首先查询出对象确保 ID != -1
	//vector<pair<int, char*> > select_con;
	//int se_b = 8;
	//select_con.push_back(make_pair(0, reinterpret_cast<char *>(&se_b)));
	//vector<map<int, char*>> res = dao.select("daodemo", select_con);
	//DaoDemo dd;
	//if (res.size() > 0) {
	//	dd.deserialize(res[0]);
	//	cout << "更新前数据：" << endl;
	//	dd.print();
	//	//dd.b = 999;
	//	char ss[20] = "sss";
	//	memcpy(dd.c, ss, 20);
	//	Table tab = Data::get_table("daodemo");
	//	cout << "!!!!!!!! " << tab.change(dd.id, 1, dd.c) << endl;

	//	//cout << "更新成功？ " << (dao.update("daodemo", dd.id, dd.serialize()) ? "成功" : "失败") << endl;
	//	dd.deserialize(dao.getById("daodemo",dd.id));
	//	cout << "更新后数据：" << endl;
	//	dd.print();
	//}

	//测试修改功能
	//map<int, char*> mm = dao.getById("daodemo", 0);
	//DaoDemo dd;
	//dd.deserialize(mm);
	//cout << "更新前数据：" << endl;
	//dd.print();
	//dd.d = 798;
	//dd.b =66;
	//char ss[20] = "susususus";
	//memcpy(dd.c, ss, 20);

	//cout << "更新成功？ " << (dao.update("daodemo", dd.id, dd.serialize()) ? "成功" : "失败") << endl;
	//dd.deserialize(dao.getById("daodemo",dd.id));
	//cout << "更新后数据：" << endl;
	//dd.print();



	//更新 char * 字段
	/*vector<pair<int, char*> > select_con;
	int se_b = 1769239923;
	select_con.push_back(make_pair(0, reinterpret_cast<char *>(&se_b)));
	vector<map<int, char*>> res = dao.select("daodemo", select_con);
	DaoDemo dd;
	if (res.size() > 0) {
		dd.deserialize(res[0]);
		cout << "更新前数据：" << endl;
		dd.print();
		char *aaa = "aaa";
		memcpy(dd.c, aaa, 20);
		cout << "更新成功？ " << (dao.update("daodemo", dd.id, dd.serialize()) ? "成功" : "失败") << endl;
		dd.deserialize(dao.getById("daodemo", dd.id));
		cout << "更新后数据：" << endl;
		dd.print();
	}*/

	return 0;
}