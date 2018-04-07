#include "Book.h"
#include <iostream>

Book::Book(int ID,string ISBN, string image, string bookName, string author, string press, string introduction, int category, int amount, int left)
{
	this->ID = ID;
	strcpy(this->ISBN, ISBN.c_str());
	strcpy(this->image, image.c_str());
	strcpy(this->bookName, bookName.c_str());
	strcpy(this->author, author.c_str());
	strcpy(this->press, press.c_str());
	strcpy(this->introduction, introduction.c_str());
	this->category = category;
	this->amount = amount;
	this->left = left;
}

int Book::getID()
{
	return ID;
}

string Book::getISBN()
{
	return string(ISBN);
}

string Book::getImage()
{
	return string(image);
}

string Book::getBookName()
{
	return string(bookName);
}

string Book::getAuthor()
{
	return string(author);
}

string Book::getPress()
{
	return string(press);
}

string Book::getIntroduction()
{
	return string(introduction);
}

int Book::getCategory()
{
	return category;
}

int Book::getAmount()
{
	return amount;
}

int Book::getLeft()
{
	return left;
}

void Book::setID(int ID)
{
	this->ID = ID;
}

void Book::setISBN(string ISBN)
{
	strcpy(this->ISBN , ISBN.c_str());
}

void Book::setImage(string image)
{
	strcpy(this->image, image.c_str());
}

void Book::setBookName(string bookName)
{
	strcpy(this->bookName, bookName.c_str());
}

void Book::setAuthor(string author)
{
	strcpy(this->author, author.c_str());
}

void Book::setPress(string press)
{
	strcpy(this->press, press.c_str());
}

void Book::setIntroduction(string introduction)
{
	strcpy(this->introduction,introduction.c_str());
}

void Book::setCategory(int category)
{
	this->category = category;
}

void Book::setAmount(int amount)
{
	this->amount = amount;
}

void Book::setLeft(int left)
{
	this->left = left;
}

//存书
bool Book::save()
{
	Dao d;
	vector<pair<int, char*> > s;
	s.push_back(make_pair(0, this->ISBN));
	vector<map<int, char *>> data = d.select("book", s);//依据ISBN获取这本书的id

	vector<char*> v;

	if (this->ID == -1) {//id为1 意思是新增这本书
		this->setISBN(MD5(Utils::getNowTime()).toStr16());
		v.push_back(this->ISBN);
		v.push_back(this->image);
		v.push_back(this->bookName);
		v.push_back(this->author);
		v.push_back(this->press);
		v.push_back(this->introduction);
		v.push_back(reinterpret_cast<char*>(&category));
		v.push_back(reinterpret_cast<char*>(&amount));
		v.push_back(reinterpret_cast<char*>(&left));
		if (d.insert_into("book", v))
			return true;
	}
	else {
		v.push_back(this->ISBN);
		v.push_back(this->image);
		v.push_back(this->bookName);
		v.push_back(this->author);
		v.push_back(this->press);
		v.push_back(this->introduction);
		v.push_back(reinterpret_cast<char*>(&category));
		v.push_back(reinterpret_cast<char*>(&amount));
		v.push_back(reinterpret_cast<char*>(&left));
		if (d.update("book", this->ID, v))
			return true;
	}

	return false;
}

//删书
bool Book::destory()
{
	Dao d;
	if (this->ID != -1) {
		if (d.delete_from("book", this->ID))
			return true;//删除这本书
	}
	return false;
}

Book Book::getBookByISBN(string ISBN)
{
	Dao d;
	vector<pair<int, char*> > s;
	char I[35];
	strcpy(I, ISBN.c_str());
	s.push_back(make_pair(0, I));
	vector<map<int, char *>> data = d.select("book", s);
	if (!data.empty()) {//如果不为空
		map<int, char *> b = data[0];
		Book book(*reinterpret_cast<int*>(b[-1]), b[0], b[1], b[2], b[3], b[4], b[5], *reinterpret_cast<int*>(b[6]), *reinterpret_cast<int*>(b[7]),*reinterpret_cast<int*>(b[8]));
		return book;
	}
	return Book();
}

vector<Book> Book::getBooksByName(string bookName, int category)
{
	Dao d;
	vector<pair<int, char*> > s;
	char n[50];
	strcpy(n, bookName.c_str());
	//s.push_back(make_pair(2, n));
	vector<map<int, char *>> data=d.select("book", s);
	vector<Book> v;
	for (vector<map<int, char *>>::iterator it = data.begin(); it != data.end(); it++) {
		if(category==-1 || *reinterpret_cast<int*>((*it)[6]) == category)
			v.push_back(Book(*reinterpret_cast<int*>((*it)[-1]), (*it)[0], (*it)[1], (*it)[2], (*it)[3], (*it)[4], (*it)[5], *reinterpret_cast<int*>((*it)[6]), *reinterpret_cast<int*>((*it)[7]), *reinterpret_cast<int*>((*it)[8])));
	}


	return v;
}

vector<Book> Book::getBooksByAuthor(string author, int category)
{
	Dao d;

	vector<pair<int, char*> > s;
	char a[50];
	strcpy(a, author.c_str());
	s.push_back(make_pair(3, a));
	vector<map<int, char *>> data = d.select("book", s);
	vector<Book> v;
	for (vector<map<int, char *>>::iterator it = data.begin(); it != data.end(); it++) {
		if (category == -1 || *reinterpret_cast<int*>((*it)[6]) == category)
			v.push_back(Book(*reinterpret_cast<int*>((*it)[-1]), (*it)[0], (*it)[1], (*it)[2], (*it)[3], (*it)[4], (*it)[5], *reinterpret_cast<int*>((*it)[6]), *reinterpret_cast<int*>((*it)[7]), *reinterpret_cast<int*>((*it)[8])));
	}
	return v;
}

vector<Book> Book::getBooksByCategory(int category)
{
	Dao d;
	vector<pair<int, char*> > s;
	if(category!=-1)
		s.push_back(make_pair(6, reinterpret_cast<char*>(&category)));
	vector<map<int, char *>> data = d.select("book", s);
	vector<Book> v;
	for (vector<map<int, char *>>::iterator it = data.begin(); it != data.end(); it++) {
		v.push_back(Book(*reinterpret_cast<int*>((*it)[-1]), (*it)[0], (*it)[1], (*it)[2], (*it)[3], (*it)[4], (*it)[5], *reinterpret_cast<int*>( (*it)[6]), *reinterpret_cast<int*>((*it)[7]), *reinterpret_cast<int*>((*it)[8])));
	}
	return v;
}

