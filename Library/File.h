#pragma once
#include <algorithm>
#include <fstream>
using namespace std;

class File
{
public:
	/*
	��ʼ�ĸ��ֽ�Ϊһ�� int �ͣ�������Ĵ�С
	�������ĸ��ֽ�Ϊһ�� int �ͣ�����ջ��Ԫ�صĸ���
	������ N ���ֽڣ�Ϊջ
	������Ϊ�ļ�����
	*/
	bool open(string file_name, int new_block_size);	///�½��ļ� ���ļ�������Ĵ�С��
	
	bool open(string file_name);				///��
	
	void destroy();

	int length();

	bool exist(int page);
	
	int add(char *info);
	

	bool del(int page);
	

	bool get(char *a, int page);
	

	int get_num();

	///Ϊ���߼����������Լ�����������в�ȫ
	void read(char *a, int page, int point, int len);	///��������

	void write(char *a, int page, int point, int len);	///������д

private:
	const static int N = 1 << 6;	///ջ���������
	string name;
	int block_size;
	int stack_top;					///stack_top��[4, 7]�ֽڴ���ջ��Ԫ�ؼ���������ͬ��

	char *p;			///��̬����ָ�룬����Ľ�������

	void fput(int point, int len);	///�ļ��޸ģ���
	
	void fget(int point, int len);

	int fend();

	int get_point(int page);

	int get_page(int point);

};
