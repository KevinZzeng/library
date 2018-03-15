#pragma once
#include <string>
#include <vector>
using namespace std;
class BorrowInfo {
private:
	int id;
	string numberID;
	string ISBN_ID;
	string b_date;
	string r_date;
	enum S{
		NORMAL, DELAY, DONE, EXCEED
	}status;
public:
	bool save();
	//��ȡ�ض�״̬������Ϣ��������Ƿ�ѽ��ͳ��
	static vector<BorrowInfo> getInfoByNumberID(string numberID, S status);
	//��ȡ��ǰ������Ϣ
	static vector<BorrowInfo> getNowInfoByNumberID(string numberID);
	//��ȡ������ʷ
	static vector<BorrowInfo> getHistoryInfoByNumberID(string numberID);



};