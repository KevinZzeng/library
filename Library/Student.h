#pragma once
#include <vector>
#include "Book.h"
using namespace std;

//ÿ�ε�½�ɹ���Ӧ�ü����û���Ƿ����Ϣ�����½�����ʷ����Ϣ��״̬
class Student {
private:
	string numberID;
	string password;
	string name;
	int major;
	string photo;
	//һ��һԪ���㹫ʽ
	double money;
	string emil;
	enum { 
		NORMAL,LOCK
	}status;
public:
	//����setter �� getter
	//login success Ӧ���������private ֵ������ʹ��
	bool login();
	//�޸ĸ�����Ϣ���������ݿ�
	bool save();
	bool destory();
	vector<Book> getInterestingBooks();
	//��ȡ��Ϣ����
	vector<string> getMessages();




};