#include<iostream>
#include"Student.h"
#include "Book.h"
#include "Utils.h"
#include "md5.h"
#include "BorrowInfo.h"
#include "CollectBook.h"
#include "bookCategory.h"
#include "CollectBook.h"
int main() {
	//vector<Student> vs = Student::getStudent("", "test", -1);
	//Student stu = vs[0];
	//stu.setPassword("test");
	//stu.setEmail("qq.com");
	//stu.setStatus(Student_NORMAL);
	//stu.save();

	Student login(-1,"test8","test8","name",1,"photo",1,"email", Student_NORMAL);
	login.save();
	Student s;
	s.login("test8", "test8");
	//login.login("test", "test");
	//CollectBook类测试 成功
	/*
	string numberID = "16020031095";

	//通过学号获取该学号预约的书籍
	vector<CollectBook> v = CollectBook::getCollectionByNumberID(numberID);

	//BorrowInfo类测试
	
	string numberID = "16020031095";
	string ISBN_ID= "12123";
	ISBN_ID += "-";
	ISBN_ID += MD5(Utils::getSpecificTime()).toStr16();
	string b_date = "2018-03-03";
	string r_date = Utils::addTime( b_date ,30);

	Book_status status = Book_NORMAL;
	BorrowInfo i(-1, numberID, ISBN_ID, b_date, r_date, status);
	//i.save();
	//获取特定状态借阅信息，可用于欠费金额统计
	vector<BorrowInfo> v1 = BorrowInfo::getInfoByNumberID(numberID, Book_EXCEED);
	//i.save();
	//获取当前借阅信息
	vector<BorrowInfo> v2 = BorrowInfo::getNowInfoByNumberID(numberID);
	//获取借阅历史
	//i.save();
	vector<BorrowInfo> v3 = BorrowInfo::getHistoryInfoByNumberID("1");

	//bookCategory类测试 成功

	map<int, string> all = BookCategory::getAllCategory();
	for (int i = 0; i < all.size(); i++) {
		cout << i << all[i] << endl;
	}
	
	string c = "科学";
	BookCategory cate(-1,c);//新建分类
	if (cate.save()) {
		cout << c << "  new!" << endl;
	}
	else
		cout << -1 << endl;
	
	
	int cID = BookCategory::getCategoryIdByName(c);
	cate.setID(cID);
	if(cate.destory())
		cout << "删除成功";
	

	//book类测试 成功
	
	string ISBN = MD5( Utils::getNowTime() ).toStr32();
	string author = "fz";
	string press = "fzPress";
	string image="path1";
	string introduction = "none1";
	int amount = 101;
	int left = 101;
	string bookName = "钢铁是怎样炼成的";
	Book b( -1,ISBN , image, bookName , author, press , introduction , cID, amount , left );
	if (b.save()) {
		cout << bookName << " success!" << endl;
	}
	
	Book b0 = Book::getBookByISBN("893b18d9220dfecc7daa5a275109a99f");
	cout << "ID" << b0.getID() << endl;
	cout << "ISBN" << b0.getISBN() << endl;
	cout << "bookName:" << b0.getBookName() << endl;
	cout << "category" << b0.getCategory() << endl;
	cout << "b1" << endl;
	if (b0.destory())
		cout << "删除成功" << endl;
	
	vector<Book> b1 = Book::getBooksByName("数学", -1);
	//通过分类以及作者来获取书
	
	for (vector<Book>::iterator it = b1.begin(); it != b1.end(); it++) {
		cout << "ID" << (*it).getID() << endl;
		cout << "ISBN" << (*it).getISBN() << endl;
		cout << "bookName:" << (*it).getBookName() << endl;
		cout << "category" << (*it).getCategory() << endl;

	}
	
	cout << "b2" << endl;
	vector<Book> b2 = Book::getBooksByAuthor("fz", -1);
	for (vector<Book>::iterator it = b2.begin(); it != b2.end(); it++) {
		cout << "ID" << (*it).getID() << endl;
		cout << "bookName:" << (*it).getBookName() << endl;
		cout << "category" << (*it).getCategory() << endl;

	}
	//通过分类来获取书
	vector<Book> b3 = Book::getBooksByCategory(-1);
	for (vector<Book>::iterator it = b3.begin(); it != b3.end(); it++) {
		cout << "ID" << (*it).getID() << endl;
		cout << "bookName:" << (*it).getBookName() << endl;
		cout << "category" << (*it).getCategory() << endl;

	}
	*/
	//getchar();
	return 0;
}