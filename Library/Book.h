#pragma once
#include <string>
#include <vector>
#include <list>
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

public:
	//���캯��
	Book();
	Book(int ID,string ISBN, string image,string bookName,string author,string press,string introduction,int category,int amount,int left);
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
	//ͨ�������Լ���������ȡ��
	static vector<Book> getBooksByName(string bookName, int category);
	//ͨ�������Լ���������ȡ��
	static vector<Book> getBooksByAuthor(string author, int category);
	//ͨ����������ȡ��
	static vector<Book> getBooksByCategory(int category);
};