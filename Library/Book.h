#pragma once
#include <string>
#include <vector>
using namespace std;
class Book {

private:
	string ISBN;
	string image;
	string bookName;
	string author;
	string press;
	string introduction;
	int category;
	int amount;
	int left;

public:
	bool save();
	int getCategory();
	//É¾³ýÒ»±¾Êé
	bool destory();
	static Book getBookByISBN(string ISBN);
	static vector<Book> getBooksByName(string bookName, int category);
	static vector<Book> getBooksByAuthor(string author, int category);
	static vector<Book> getBooksByCategory(int category);




};