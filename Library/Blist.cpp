#include "Blist.h"


void Blist::build(string _name, vector<int> _len)///_len为每个索引键的键长，暂不支持超过64字节的索引
{
	flist.open(_name + ".bls", N);
	len = _len;
	num = len.size();
	n = 0;
	char for_write[N] = { 0 };
	int *p = (int*)for_write;
	p[0] = num;
	for (int i = 0; i < p[0]; i++)
		p[i + 1] = len[i];
	flist.add(for_write);
	memset(for_write, 0, N);
	for (int i = 0; i < num; i++)
		flist.add(for_write);
}
bool Blist::open(string _name, int _n)
{
	flist.open(_name + ".bls");
	n = _n;
	char con[N];
	flist.read((char*)&num, 0, 0, 4);
	flist.read(con, 0, 4, 4 * num);
	int *p = (int*)con;
	len.clear();
	for (int i = 0; i < num; i++)
		len.push_back(p[i]);
	return true;
}
void Blist::close()
{
	flist.close();
}
void Blist::update(int k, char* old_key, char* new_key, int value)
{
	n--;
	del(old_key, value, k + 1, len[k]);
	n++;
	insert(new_key, value, k + 1, len[k]);
}
void Blist::insert(vector<char*> key, int value)
{
	n++; ///信息总条数加一
	for (int i = 0; i < num; i++)///对该文件所管理的全部链表都进行插入操作
		insert(key[i], value, i + 1, len[i]);
}
void Blist::del(vector<char*> key, int value)
{
	n--; ///信息总条数加一
	for (int i = 0; i < num; i++)///对该文件所管理的全部链表都进行插入操作
		del(key[i], value, i + 1, len[i]);
}
vector<int> Blist::search(int k, char* key)
{
	vector<int> value;
	find(k + 1, len[k], key, value);
	return value;
}
vector<int> Blist::fuzzy_search(int column, char* key)
{
	vector<int> next, id;
	next.push_back(-1);
	int slen = strlen(key);
	int length = len[column];
	for (int i = 0, k = -1; i < slen - 1;)
	{
		if (k == -1 || key[i] == key[k])
			if (key[++i] != key[++k])
				next.push_back(k);
			else
				next.push_back(next[k]);
		else
			k = next[k];
	}
	int block = column + 1;
	while (block)
	{
		int bsize = get_blocksize(block);
		int next_block = get_next(block);
		char con[N];
		flist.read(con, block, 8, bsize*(length + 4));
		char *s = con;
		for (int i = 0; i < bsize; i++, s += length + 4)
		{
			int k = 0;
			for (int j = 0; k<slen && j<length;)
			{
				if (k == -1 || s[j] == key[k])
					k++, j++;
				else
					k = next[k];
			}
			if (k == slen)
				id.push_back(*(int*)(s + length));
		}
		block = next_block;
	}
	return id;
}
void Blist::del(char *key, int value, int block, int length)
{
	while (block)///如果元素不在该块中则搜索下一个块，直至链表结束
	{
		int bsize = get_blocksize(block);///块内有多少组键值对
		int next = get_next(block);///下一个块的指针
		char _key[64];
		char con[N];
		flist.read(_key, block, 8 + (bsize - 1)*(length + 4), length);///获取块尾元素
		if (S_T(key, _key, length)) ///如果<当前块的尾元素
		{
			flist.read(con, block, 0, 8 + bsize*(length + 4));///读入块
			int p = get_start(con + 8, key, bsize, length);///获取插入位置
			for (char* x = con + (p*(length + 4) + 8); E_Q(x, key, length); x += length + 4) ///将满足条件的元素加入
				if (value == *(int*)(x + length))///确认为应删除对象，则进行删除操作
				{
					for (char *e = con + (--(*(int*)con))*(length + 4) + 8; x<e; x++)///对该数据块进行修改
						*x = *(x + length + 4);
					flist.write(con, block, 0, combine_next(con, length + 4)*(length + 4) + 8);///尝试与下个数据块进行合并，并用内存中维护好的新数据块覆盖文件中的原数据
					break;
				}
			break;
		}
		else if (E_Q(_key, key, length)) ///如果==当前块的尾元素
		{
			flist.read(con, block, 0, 8 + bsize*(length + 4));///读入块
			int p = get_start(con + 8, key, bsize, length);///获取插入位置
			char* x = con + (p*(length + 4) + 8);
			for (int i = p; i<bsize; i++, x += length + 4) ///将满足条件的元素加入
				if (value == *(int*)(x + length))///确认为应删除对象，则进行删除操作
				{
					for (char *e = con + (--(*(int*)con))*(length + 4) + 8; x<e; x++)///对该数据块进行修改
						*x = *(x + length + 4);
					flist.write(con, block, 0, combine_next(con, length + 4)*(length + 4) + 8);///尝试与下个数据块进行合并，并用内存中维护好的新数据块覆盖文件中的原数据
					break;
				}
		}
		block = next;
	}
}
void Blist::find(int block, int length, char* key, vector<int>& value)///禁止搜索长度超过64的key,在指定子表内搜索
{
	while (block)///如果元素不在该块中则搜索下一个块，直至链表结束
	{
		int bsize = get_blocksize(block);///块内有多少组键值对
		int next = get_next(block);///下一个块的指针
		char _key[64];
		char con[N];
		flist.read(_key, block, 8 + (bsize - 1)*(length + 4), length);///获取块尾元素
		if (S_E(key, _key, length)) ///如果<当前块的尾元素
		{
			flist.read(con, block, 0, 8 + bsize*(length + 4));///读入块
			int p = get_start(con + 8, key, bsize, length);///获取位置
			for (char* x = con + (p*(length + 4) + 8); p<bsize&&E_Q(x, key, length); x += length + 4, p++) ///将满足条件的元素取出
				value.push_back(*(int*)(x + length));
			if (!E_Q(_key, key, length)) ///如果!=当前块的尾元素
				break;

		}
		block = next;
	}
}
void Blist::insert(char* key, int value, int block, int length)///在所指向块的子块呢插入（键，值，file中的page，列号）
{
	while (block)
	{
		int bsize = get_blocksize(block);///块内有多少组键值对
		int next = get_next(block);///下一个块的指针
		char con[N];
		flist.read(con, block, 8 + (bsize - 1)*(length + 4), length);///获取尾键值

		if (next == 0 || S_E(key, con, length)) ///如果是最后一个块或键在这个块的范围内
		{
			flist.read(con, block, 0, 8 + bsize*(length + 4));///获取块中内容
			*(int*)con += 1;///更新块元素数
			int p = get_start(con + 8, key, bsize++, length);///获取插入位置(并在最后一次利用bsize后修正其值）
			for (int l = length + 4, i = bsize*l + 7, e = (p + 1)*l + 7; e < i; i--)///移动尾部内容
				con[i] = con[i - l];
			for (int i = 0; i < length; i++)///在内存中维护插入后的数据块
				con[i + 8 + p*(length + 4)] = key[i];
			*(int*)(con + (8 + p*(length + 4) + length)) = value;
			if ((int)(2 * sqrt(n))<bsize || N < 8 + (bsize + 1)*(length + 4)) ///如果满足拆分条件，则拆分块，并向文件增添新生成的块
			{
				char _con[N] = { 0 };
				split(con, _con, length + 4);
				*(int*)(con + 4) = flist.add(_con);
			}
			flist.write(con, block, 0, 8 + bsize*(length + 4));///用内存中维护好的新数据块覆盖文件中的原数据
			break;
		}
		block = next;
	}
}
int Blist::get_blocksize(int block)
{
	int blocksize;
	flist.read((char*)&blocksize, block, 0, 4);
	return blocksize;
}
int Blist::get_next(int block)
{
	int next;
	flist.read((char*)&next, block, 4, 4);
	return next;
}
void Blist::split(char* a, char* b, int length)///块分割
{
	int&size_a = *(int*)a;
	int&size_b = *(int*)b;
	int&next_a = *(int*)(a + 4);
	int&next_b = *(int*)(b + 4);
	next_b = next_a;
	size_b = size_a / 2;
	size_a -= size_b;
	char *pa = a + (size_a*length + 8), *pb = b + 8;
	for (int i = 0, len = size_b*length; i < len; i++)
		pb[i] = pa[i];
}
int Blist::combine_next(char *a, int length)
{
	int&size_a = *(int*)a;
	int&next_a = *(int*)(a + 4);
	if (next_a&&size_a <= sqrt(n) / 2 && length*(size_a + get_blocksize(next_a) + 1) + 8 <= N)
	{
		char b[N];
		flist.get(b, next_a);
		int&size_b = *(int*)b;
		int&next_b = *(int*)(b + 4);
		char *pa = a + (size_a*length + 8), *pb = b + 8;
		for (int i = 0, len = size_b*length; i < len; i++)
			pa[i] = pb[i];
		size_a += size_b;
		flist.del(next_a);
		next_a = next_b;
	}
	return size_a;
}
bool Blist::S_T(char* a, char* b, int length)/// "<"
{
	for (int i = length - 1; 0 <= i; i--)
		//for(int i = 0; i < length; i++)
	{
		if (a[i] < b[i])
			return true;
		if (b[i] < a[i])
			return false;
	}
	return false;
}
bool Blist::S_E(char* a, char* b, int length)/// "<="
{
	return !S_T(b, a, length);
}
bool Blist::E_Q(char* a, char* b, int length)/// "=="
{
	for (int i = 0; i < length; i++)
		if (a[i] != b[i])
			return false;
	return true;
}
int Blist::get_start(char *s, char *key, int bsize, int length) ///块内二分定位 ,s为第一个元素的指针
{
	int l, r, m;
	for (l = 0, r = bsize - 1, m = (l + r) >> 1; l <= r; m = (l + r) >> 1)
	{
		if (S_T(s + (length + 4)*m, key, length))
			l = m + 1;
		else
			r = m - 1;
	}
	return l;
}

