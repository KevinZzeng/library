#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;

///�׳�-1��ʾ���ݱ�����
///�׳�1��ʾ�Բ�����������ģ������
class FileOp
{
public:
	FileOp();
	bool open(string file_name, int new_block_size);	///�½��ļ� ���ļ�������Ĵ�С��
	bool open(string file_name);				///��
	bool if_open();
	void destroy();
	int length();
	bool exist(int page);
	int add(char *info);
	bool del(int page);
	bool get(char *a, int page);
	int get_num();
	void read(char *a, int page, int point, int len);	///��������
	void write(char *a, int page, int point, int len);	///������д
	void close();
private:
	const static int N = 1 << 16;	///ջ���������
	string name;
	int block_size;
	int stack_top;					///stack_top��[4, 7]�ֽڴ���ջ��Ԫ�ؼ���������ͬ��
	char *p;			///��̬����ָ�룬����Ľ�������
	void fput(int point, int len);	///�ļ��޸ģ���
	void fget(int point, int len);
	int fend();
	int get_point(int page);
	int get_page(int point);
	FILE* file;
};