#pragma once
#include <algorithm>
#include <fstream>
using namespace std;

class File
{
public:
	/*
	初始四个字节为一个 int 型，描述块的大小
	接下来四个字节为一个 int 型，描述栈内元素的个数
	接下来 N 个字节，为栈
	接下来为文件内容
	*/
	bool open(string file_name, int new_block_size);	///新建文件 （文件名，块的大小）
	
	bool open(string file_name);				///打开
	
	void destroy();

	int length();

	bool exist(int page);
	
	int add(char *info);
	

	bool del(int page);
	

	bool get(char *a, int page);
	

	int get_num();

	///为了逻辑的完整性以及以外操作进行补全
	void read(char *a, int page, int point, int len);	///不定长读

	void write(char *a, int page, int point, int len);	///不定长写

private:
	const static int N = 1 << 6;	///栈的最大容量
	string name;
	int block_size;
	int stack_top;					///stack_top与[4, 7]字节处的栈内元素计数器保持同步

	char *p;			///动态类型指针，航神的骄傲，勿动

	void fput(int point, int len);	///文件修改（）
	
	void fget(int point, int len);

	int fend();

	int get_point(int page);

	int get_page(int point);

};
