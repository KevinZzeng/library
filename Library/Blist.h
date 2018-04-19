#pragma once
#include "FileOp.h"
using namespace std;
class Blist
{
public:
	void build(string _name, vector<int> _len);///_lenΪÿ���������ļ������ݲ�֧�ֳ���64�ֽڵ�����
	bool open(string _name, int _n);
	void close();///�ر����ļ�����ϵ
	void update(int k, char* old_key, char* new_key, int value);
	void insert(vector<char*> key, int value);
	void del(vector<char*> key, int value);
	vector<int> search(int k, char* key);
	vector<int> fuzzy_search(int column, char* key);
protected:
	void del(char *key, int value, int block, int length);
	void find(int block, int length, char* key, vector<int>& value);///��ֹ�������ȳ���64��key,��ָ���ӱ�������
	void insert(char* key, int value, int block, int length);///����ָ�����ӿ��ز��루����ֵ��file�е�page���кţ�
	int get_blocksize(int block);
	int get_next(int block);
	void split(char* a, char* b, int length);///��ָ�
	int combine_next(char *a, int length);
private:
	const static int N = 1 << 16;///ÿ������ռ�Ĵ洢�ռ�
	int num;///����
	int n;///��Ԫ����
	vector<int> len;///ÿ�е�key��
	FileOp flist;
	bool S_T(char* a, char* b, int length);/// "<"
	bool S_E(char* a, char* b, int length);/// "<="
	bool E_Q(char* a, char* b, int length);/// "=="
	int get_start(char *s, char *key, int bsize, int length); ///���ڶ��ֶ�λ ,sΪ��һ��Ԫ�ص�ָ��
};