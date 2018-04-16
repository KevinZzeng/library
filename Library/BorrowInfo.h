#pragma once
#include <vector>
#include "Student.h"
#include <string>
#include "Utils.h"
#include "Dao.h"
using namespace std;
enum Book_status {
	Book_NORMAL, Book_DELAY, Book_DONE, Book_EXCEED
};
class Student;
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
	//构造函数
	BorrowInfo(int ID = -1, string numberID = "", string ISBN_ID = "", string b_date = "", string r_date = "", Book_status status = (Book_status)0);
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
	//新增一条借阅记录
	bool save();
	//还书
	static bool returnBook(BorrowInfo b);
	//续借+7天
	static bool renewBook(BorrowInfo b);
	//根据ISBN获取该书的借阅用户的信息
	static vector<Student> getStudentInfoByISBN(string ISBN);
	//获取特定状态借阅信息，可用于欠费金额统计
	static vector<BorrowInfo> getInfoByNumberID(string numberID, Book_status status);
	//获取当前借阅信息
	static vector<BorrowInfo> getNowInfoByNumberID(string numberID);
	//获取借阅历史
	static vector<BorrowInfo> getHistoryInfoByNumberID(string numberID);



};