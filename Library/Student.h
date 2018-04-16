#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include "Book.h"
#include "Dao.h"
#include "md5.h"
#include "BorrowInfo.h"
#include "Utils.h"
using namespace std;
class Book;
enum status_class {
	Student_NORMAL, Student_LOCK
};
//ÿ�ε�½�ɹ���Ӧ�ü����û���Ƿ����Ϣ�����½�����ʷ����Ϣ��״̬
class Student {
private:
	int id;
	char numberID[13];
	char password[33];
	char name[50];
	int major;
	char photo[200];
	//һ��һԪ���㹫ʽ
	int money;
	char email[30];
	status_class status;
	void init() {
		memset(numberID, '\0', sizeof(numberID));
		memset(password, '\0', sizeof(password));
		memset(name, '\0', sizeof(name));
		memset(photo, '\0', sizeof(photo));
		memset(email, '\0', sizeof(email));
	}
public:
	//����setter �� getter
	Student();
	Student(int id, string numberID, string password, string name, int major, string photo, int money, string email, status_class status);
	void setId(int id);
	int getId();
	void setNumberID(string numberID);
	string getNumberID();
	void setPassword(string password);
	void setName(string name);
	string getName();
	void setMajor(int major);
	int getMajor();
	void setPhoto(string photo);
	string getPhoto();
	void setMoney(int money);
	int getMoney();
	void setEmail(string email);
	string getEmail();
	void setStatus(status_class status);
	status_class getStatus();
	//login success Ӧ���������private ֵ������ʹ��
	bool login(string numberID, string password);
	//��ȡѧ����Ϣ������Ҫ����������""����-1
	static vector<Student> getStudent(string name, string numberID, int major);
	//�޸ĸ�����Ϣ���������ݿ⣬�Ѵ����û�save����false
	bool save();
	bool destory();
	vector<Book> getInterestingBooks();
	//��ȡ��Ϣ����
	vector<string> getMessages();



};