#pragma once
#include <string>
#include <vector>
using namespace std;
enum Book_status {
	NORMAL, DELAY, DONE, EXCEED
};
class BorrowInfo {
private:
	int id;
	string numberID;
	string ISBN_ID;
	string b_date;
	string r_date;
	Book_status status;
public:
	bool save();
	string getISBN_ID();
	//��ȡ�ض�״̬������Ϣ��������Ƿ�ѽ��ͳ��
	static vector<BorrowInfo> getInfoByNumberID(string numberID, Book_status status);
	//��ȡ��ǰ������Ϣ
	static vector<BorrowInfo> getNowInfoByNumberID(string numberID);
	//��ȡ������ʷ
	static vector<BorrowInfo> getHistoryInfoByNumberID(string numberID);



};