//#include "Dao.h"
//#include <iostream>
//#include <string>
//#include <cstdio>
//using namespace std;
//int main() {
//
//	string tableName;
//	cout << "-----------------���ݿ⹤��-----------------" << endl;
//	cout << "1. �½���   2.ɾ����" << endl;
//	cout << "��ѡ��:";
//	int chose;
//	cin >> chose;
//	if (chose == 1) {
//		cout << "�����������:";
//		cin >> tableName;
//		cout << "������:";
//		int rows;
//		cin >> rows;
//		cout << "��������, ��ʽ: ���ͣ�0-int 1-char *�� ����(int ��0, char * ����ʵ����д) �Ƿ�ɼ���(1-�� 0-��)" << endl;
//		cout << "0 0 1" << "��˼�� int ���ͣ��ɼ���" << endl;
//		cout << "��������:" << endl;
//		int type, length, isIndex;
//		int *column = new int[rows];
//		bool *ifSearch = new bool[rows];
//		int tmp = 0;
//		while (tmp < rows) {
//			cin >> type >> length >> ifSearch[tmp];
//			if (type == 0)
//				column[tmp] = sizeof(int);
//			else
//				column[tmp] = length;
//			tmp++;
//		}
//		DataSys::create(tableName, rows, column, ifSearch);
//		cout << "!!!" << tableName << "�������!!!" << endl;
//
//		cout << "total rows:" << rows << endl;
//		for (int i = 0; i < rows; i++) {
//			cout << "len: " << column[i] << " if_search: " << ifSearch[i] << endl;
//		}
//
//		delete[] column;
//		delete[] ifSearch;
//	}
//	else if(chose ==2){
//
//		cout << "������Ҫɾ���ı����ƣ�";
//		cin >> tableName;
//		cout << "ȷ��Ҫɾ�� " << tableName << " ��?Y/N" << endl;
//		char ch;
//		cin >> ch;
//		if (ch == 'Y' || ch == 'y'){
//			
//			//remove((tableName + ".bls").c_str());
//			//Data::delete_table(tableName);
//			cout << tableName << (!remove((tableName + ".pag").c_str()) &&
//				!remove(tableName.c_str()) &&
//				!remove((tableName + ".bls").c_str())
//				 ?" ɾ���ɹ�!":"ɾ��ʧ��") << endl;
//		}
//	}
//	return 0;
//}