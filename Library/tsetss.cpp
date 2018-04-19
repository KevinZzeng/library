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
	//Student login(-1,"test20","test20","name",1,"photo",1,"email", Student_NORMAL);
	//login.save();

	Student s(-1, "test20", "test20", "name", 1, "photo", 1, "email", Student_NORMAL);
	s.save();
	if (s.save()) {
		cout << "student save successfully" << endl;
	}
	if (s.login("test20", "test20")) {
		s.setPhoto("has changed");
		if (s.save()) {
			cout << "change student successfully" << endl;
		}
		Book b(-1, "dddddddddddddddd", "iamge", "name", "author", "press", "introduction", 0, 10, 10);
		if (b.save())
			cout << "save book successfully" << endl;
		Dao dao;
		vector<pair<int, char*>> s;
		vector<map<int, char *>> data = dao.select("book", s);
		CollectBook cb(-1, "test20", "F786D1EAF5DA75AE");
		if (cb.save()) {
			cout << "collect book successfully" << endl;
		}
		string tiem = Utils::getNowTime();
		string time = Utils::addTime(tiem, 30);
		BorrowInfo bi(-1, "test20", "F786D1EAF5DA75AE", tiem, time);
		if (bi.save()) {
			cout << "borrow book successfully" << endl;
		}
		
	}
	Student s1;
	s1.login("test20", "test20");
	cout << s1.getStatus() << endl;
	//Student s1;
	//s1.login("test20", "test20");
	//cout << s1.getPhoto() << endl;
	//login.login("test", "test");
	//CollectBook����� �ɹ�
	/*
	string numberID = "16020031095";

	//ͨ��ѧ�Ż�ȡ��ѧ��ԤԼ���鼮
	vector<CollectBook> v = CollectBook::getCollectionByNumberID(numberID);

	//BorrowInfo�����
	
	string numberID = "16020031095";
	string ISBN_ID= "12123";
	ISBN_ID += "-";
	ISBN_ID += MD5(Utils::getSpecificTime()).toStr16();
	string b_date = "2018-03-03";
	string r_date = Utils::addTime( b_date ,30);

	Book_status status = Book_NORMAL;
	BorrowInfo i(-1, numberID, ISBN_ID, b_date, r_date, status);
	//i.save();
	//��ȡ�ض�״̬������Ϣ��������Ƿ�ѽ��ͳ��
	vector<BorrowInfo> v1 = BorrowInfo::getInfoByNumberID(numberID, Book_EXCEED);
	//i.save();
	//��ȡ��ǰ������Ϣ
	vector<BorrowInfo> v2 = BorrowInfo::getNowInfoByNumberID(numberID);
	//��ȡ������ʷ
	//i.save();
	vector<BorrowInfo> v3 = BorrowInfo::getHistoryInfoByNumberID("1");

	//bookCategory����� �ɹ�

	map<int, string> all = BookCategory::getAllCategory();
	for (int i = 0; i < all.size(); i++) {
		cout << i << all[i] << endl;
	}
	
	string c = "��ѧ";
	BookCategory cate(-1,c);//�½�����
	if (cate.save()) {
		cout << c << "  new!" << endl;
	}
	else
		cout << -1 << endl;
	
	
	int cID = BookCategory::getCategoryIdByName(c);
	cate.setID(cID);
	if(cate.destory())
		cout << "ɾ���ɹ�";
	

	//book����� �ɹ�
	
	string ISBN = MD5( Utils::getNowTime() ).toStr32();
	string author = "fz";
	string press = "fzPress";
	string image="path1";
	string introduction = "none1";
	int amount = 101;
	int left = 101;
	string bookName = "�������������ɵ�";
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
		cout << "ɾ���ɹ�" << endl;
	
	vector<Book> b1 = Book::getBooksByName("��ѧ", -1);
	//ͨ�������Լ���������ȡ��
	
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
	//ͨ����������ȡ��
	vector<Book> b3 = Book::getBooksByCategory(-1);
	for (vector<Book>::iterator it = b3.begin(); it != b3.end(); it++) {
		cout << "ID" << (*it).getID() << endl;
		cout << "bookName:" << (*it).getBookName() << endl;
		cout << "category" << (*it).getCategory() << endl;

	}
	*/
	//getchar();0
	return 0;
}