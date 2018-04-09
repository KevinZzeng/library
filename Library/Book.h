#pragma once
#include <string>
#include <vector>
#include <list>
#include "md5.h"
#include "Utils.h"
#include "Dao.h"
using namespace std;

class Book {

private:
	int ID;
	char ISBN[35];
	char image[200];
	char bookName[50];
	char author[50];
	char press[50];
	char introduction[500];
	int category;
	int amount;
	int left;
	void init() {
		memset(ISBN, '\0', sizeof(ISBN));
		memset(image, '\0', sizeof(image));
		memset(bookName, '\0', sizeof(bookName));
		memset(author, '\0', sizeof(author));
		memset(press, '\0', sizeof(press));
		memset(introduction, '\0', sizeof(introduction));
	}
public:
	//���캯��
	Book(int ID=-1,string ISBN="", string image="",string bookName="",string author="",string press="",string introduction="",int category=-1,int amount=-1,int left=-1);
	//get set����
	int getID();
	string getISBN();
	string getImage();
	string getBookName();
	string getAuthor();
	string getPress();
	string getIntroduction();
	int getCategory();
	int getAmount();
	int getLeft();
	void setID(int ID);
	void setISBN(string ISBN);
	void setImage(string image);
	void setBookName(string bookName);
	void setAuthor(string author);
	void setPress(string press);
	void setIntroduction(string introduction);
	void setCategory(int category);
	void setAmount(int amount);
	void setLeft(int left);
	//�������߸���һ����
	bool save();
	//ɾ��һ����
	bool destory();
	//ͨ��ISBN��ȡ��
	static Book getBookByISBN(string ISBN);
	//ͨ�������Լ���������ȡ�� categoryΪ-1˵����ѯȫ������
	static vector<Book> getBooksByName(string bookName, int category);
	//ͨ�������Լ���������ȡ��  categoryΪ-1˵����ѯȫ������
	static vector<Book> getBooksByAuthor(string author, int category);
	//ͨ����������ȡ�� categoryΪ-1˵����ѯȫ������
	static vector<Book> getBooksByCategory(int category);
};