#pragma once
#include "FileOp.h"
using namespace std;
class Blist
{
public:
	void build(string _name, vector<int> _len);///_len为每个索引键的键长，暂不支持超过64字节的索引
	bool open(string _name, int _n);
	void close();///关闭与文件的联系
	void update(int k, char* old_key, char* new_key, int value);
	void insert(vector<char*> key, int value);
	void del(vector<char*> key, int value);
	vector<int> search(int k, char* key);
	vector<int> fuzzy_search(int column, char* key);
protected:
	void del(char *key, int value, int block, int length);
	void find(int block, int length, char* key, vector<int>& value);///禁止搜索长度超过64的key,在指定子表内搜索
	void insert(char* key, int value, int block, int length);///在所指向块的子块呢插入（键，值，file中的page，列号）
	int get_blocksize(int block);
	int get_next(int block);
	void split(char* a, char* b, int length);///块分割
	int combine_next(char *a, int length);
private:
	const static int N = 1 << 16;///每个块所占的存储空间
	int num;///列数
	int n;///总元素数
	vector<int> len;///每列的key长
	FileOp flist;
	bool S_T(char* a, char* b, int length);/// "<"
	bool S_E(char* a, char* b, int length);/// "<="
	bool E_Q(char* a, char* b, int length);/// "=="
	int get_start(char *s, char *key, int bsize, int length); ///块内二分定位 ,s为第一个元素的指针
};