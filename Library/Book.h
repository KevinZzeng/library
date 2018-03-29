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
	//构造函数
	Book();
	Book(int ID,string ISBN, string image,string bookName,string author,string press,string introduction,int category,int amount,int left);
	//get set方法
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
	//新增或者更新一本书
	bool save();
	//删除一本书
	bool destory();
	//通过ISBN获取书
	static Book getBookByISBN(string ISBN);
	//通过分类以及书名来获取书
	static vector<Book> getBooksByName(string bookName, int category);
	//通过分类以及作者来获取书
	static vector<Book> getBooksByAuthor(string author, int category);
	//通过分类来获取书
	static vector<Book> getBooksByCategory(int category);
};