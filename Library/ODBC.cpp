#include "Dao.h"
#include <iostream>
#include <string>
using namespace std;
int main() {

	string tableName;
	cout << "-----------------数据库工具-----------------" << endl;
	cout << "1. 新建表   2.删除表" << endl;
	cout << "请选择:";
	int chose;
	cin >> chose;
	if (chose == 1) {
		cout << "请输入表名称:";
		cin >> tableName;
		cout << "共几列:";
		int rows;
		cin >> rows;
		cout << "请输入列, 格式: 类型（0-int 1-char *） 长度(int 填0, char * 按照实际填写) 是否可检索(1-是 0-否)" << endl;
		cout << "0 0 1" << "意思： int 类型，可检索" << endl;
		cout << "请输入列:" << endl;
		int type, length, isIndex;
		int *column = new int[rows];
		bool *ifSearch = new bool[rows];
		int tmp = 0;
		while (tmp < rows) {
			cin >> type >> length >> ifSearch[tmp];
			if (type == 0)
				column[tmp] = sizeof(int);
			else
				column[tmp] = length;
			tmp++;
		}
		Data::create_table(tableName, rows, column, ifSearch);
		cout << "!!!" << tableName << "创建完成!!!" << endl;

		cout << "total rows:" << rows << endl;
		for (int i = 0; i < rows; i++) {
			cout << "len: " << column[i] << " if_search: " << ifSearch[i] << endl;
		}

		delete[] column;
		delete[] ifSearch;
	}
	else if(chose ==2){

		cout << "请输入要删除的表名称：";
		cin >> tableName;
		cout << "确定要删除 " << tableName << " 吗?Y/N" << endl;
		char ch;
		cin >> ch;
		if (ch == 'Y' || ch == 'y'){
			Data::delete_table(tableName);
			cout << tableName << " 删除成功!" << endl;
		}
	}
	return 0;
}