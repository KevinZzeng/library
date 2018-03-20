#pragma once
#include <vector>
#include "Book.h"
#include "Dao.h"
#include "md5.h"
#include "BorrowInfo.h"
using namespace std;
enum status_class {
	NORMAL, LOCK
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
	double money;
	char email[30];
	status_class status;
public:
	//����setter �� getter
	void setId(int id);
	int getId();
	void setNumberID(string numberID);
	string getNumberID();
	void setPassword(string password);
	string getPassword();
	void setName(string name);
	string getName();
	void setMajor(int major);
	int getMajor();
	void setPhoto(string photo);
	string getPhoto();
	void setMoney(double money);
	double getMoney();
	void setEmail(string email);
	string getEmail();
	void setStatus(status_class status);
	status_class getStatus();
	//login success Ӧ���������private ֵ������ʹ��
	bool login(string numberID, string password);
	//�޸ĸ�����Ϣ���������ݿ�
	bool save();
	bool destory();
	vector<Book> getInterestingBooks();
	//��ȡ��Ϣ����
	vector<string> getMessages();



};