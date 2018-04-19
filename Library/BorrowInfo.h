#pragma once
#include <string>
#include "Utils.h"
#include <vector>
#include "Dao.h"
using namespace std;
enum Book_status {
	Book_NORMAL, Book_DELAY, Book_DONE, Book_EXCEED
};

class BorrowInfo {
private:
	int ID;
	char numberID[13];
	char ISBN_ID[35];
	char b_date[20];
	char r_date[20];
	Book_status status;
	void init() {
		memset(numberID, '\0', sizeof(numberID));
		memset(ISBN_ID, '\0', sizeof(ISBN_ID));
		memset(b_date, '\0', sizeof(b_date));
		memset(r_date, '\0', sizeof(r_date));
	}
public:
	//���캯��
	BorrowInfo(int ID=-1, string numberID="", string ISBN_ID="", string b_date="", string r_date="", Book_status status= Book_NORMAL);
	//get set
	int getID();
	string getNumberID();
	string getISBN_ID();
	string getB_date();
	string getR_date();
	Book_status getStatus();
	void setID(int ID);
	void setNumberID(string numberID);
	void setISBN_ID(string ISBN_ID);
	void setB_date(string b_date);
	void setR_date(string r_date);
	void setStatus(Book_status status);
	//����һ�����ļ�¼
	bool save();
	//��ȡ�ض�״̬������Ϣ��������Ƿ�ѽ��ͳ��
	static vector<BorrowInfo> getInfoByNumberID(string numberID, Book_status status);
	//��ȡ��ǰ������Ϣ
	static vector<BorrowInfo> getNowInfoByNumberID(string numberID);
	//��ȡ������ʷ
	static vector<BorrowInfo> getHistoryInfoByNumberID(string numberID);



};