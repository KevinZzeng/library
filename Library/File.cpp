#include "File.h"

bool File::open(string file_name, int new_block_size)
{
	ofstream f(file_name.c_str());
	f.close();
	block_size = new_block_size;
	stack_top = 0;
	name = file_name;
	char c[N] = { 0 };
	p = c;
	fput(0, N);		///人工构造栈(初始化)

	p = reinterpret_cast<char*> (&block_size);
	fput(0, 4);		///块的大小写入前四个字节
	return true;
}

bool File::open(string file_name)
{
	fstream f(file_name.c_str());
	if (!f)
		return false;
	f.close();
	name = file_name;
	p = reinterpret_cast<char*> (&block_size);
	fget(0, 4);	///获取
	p = reinterpret_cast<char*> (&stack_top);
	fget(4, 4);	///获取
	return true;
}

void File::destroy()
{
	remove(name.c_str());
}

int File::length()
{
	return get_page(fend());
}

bool File::exist(int page)
{
	char s;
	p = &s;
	fget(get_point(page), 1);
	if (s)
		return false;
	else
		return true;
}

int File::add(char * info)
{
	int page;
	int point;	///
	if (stack_top)
	{
		stack_top--;
		p = reinterpret_cast<char*> (&stack_top);
		fput(4, 4);	///修改位于[4, 7]的栈内计数器
		p = reinterpret_cast<char*> (&page);
		fget((stack_top + 2) * 4, 4);
		point = get_point(page);
	}
	else
	{
		point = fend();
		page = get_page(point);
	}
	char s = 0;
	p = &s;
	fput(point, 1);
	p = info;
	fput(point + 1, block_size);
	return page;
}

bool File::del(int page)
{
	if (!exist(page))
		return false;
	if (stack_top * 4 >= N - 8) 	///防止爆栈
		return false;
	stack_top++;
	p = reinterpret_cast<char*> (&stack_top);
	fput(4, 4); ///修改 [4, 7]
	p = reinterpret_cast<char*> (&page);
	fput((stack_top + 1) * 4, 4);   ///往栈顶加值
	char s = 1;
	p = &s;
	fput(get_point(page), 1);
	return true;
}

bool File::get(char * a, int page)
{
	if (!exist(page))
		return false;
	p = a;
	fget(get_point(page) + 1, block_size);
	return true;
}

int File::get_num()
{
	return get_page(fend()) - stack_top;
}

void File::read(char * a, int page, int point, int len)
{
	len = min(len, block_size);
	p = a;
	point += get_point(page) + 1;
	fget(point, len);
}

void File::write(char * a, int page, int point, int len)
{
	len = min(len, block_size);
	p = a;
	point += get_point(page) + 1;
	fput(point, len);
}

void File::fput(int point, int len)
{
	fstream f(name.c_str(), ios::in | ios::out | ios::binary);
	f.seekp(point);
	f.write(p, len);
	f.close();
}

void File::fget(int point, int len)
{
	ifstream f(name.c_str());
	f.seekg(point);
	f.read(p, len);
	f.close();
}

int File::fend()
{
	ifstream f(name.c_str());
	f.seekg(0, ios::end);
	int point = static_cast<int>(f.tellg());
	f.close();
	return point;
}

int File::get_point(int page)
{
	return N + page * (block_size + 1);
}

int File::get_page(int point)
{
	return (point - N) / (block_size + 1);
}