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
	//获取特定状态借阅信息，可用于欠费金额统计
	static vector<BorrowInfo> getInfoByNumberID(string numberID, Book_status status);
	//获取当前借阅信息
	static vector<BorrowInfo> getNowInfoByNumberID(string numberID);
	//获取借阅历史
	static vector<BorrowInfo> getHistoryInfoByNumberID(string numberID);



};