#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;

///抛出-1表示数据表不存在
///抛出1表示对不可索引列做模糊查找
class FileOp
{
public:
	FileOp();
	bool open(string file_name, int new_block_size);	///新建文件 （文件名，块的大小）
	bool open(string file_name);				///打开
	bool if_open();
	void destroy();
	int length();
	bool exist(int page);
	int add(char *info);
	bool del(int page);
	bool get(char *a, int page);
	int get_num();
	void read(char *a, int page, int point, int len);	///不定长读
	void write(char *a, int page, int point, int len);	///不定长写
	void close();
private:
	const static int N = 1 << 16;	///栈的最大容量
	string name;
	int block_size;
	int stack_top;					///stack_top与[4, 7]字节处的栈内元素计数器保持同步
	char *p;			///动态类型指针，航神的骄傲，勿动
	void fput(int point, int len);	///文件修改（）
	void fget(int point, int len);
	int fend();
	int get_point(int page);
	int get_page(int point);
	FILE* file;
};