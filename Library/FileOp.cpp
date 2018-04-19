#include "FileOp.h"

FileOp::FileOp()
{
	file = NULL;
}

bool FileOp::open(string file_name, int new_block_size)
{
	if (file != NULL)
		fclose(file);
	ofstream f(file_name.c_str());
	f.close();
	file = fopen(file_name.c_str(), "rb+");
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

bool FileOp::open(string file_name)
{
	if (file != NULL)
		fclose(file);
	file = fopen(file_name.c_str(), "rb+");
	if (file == NULL)
		return false;
	name = file_name;
	p = reinterpret_cast<char*> (&block_size);
	fget(0, 4);	///获取
	p = reinterpret_cast<char*> (&stack_top);
	fget(4, 4);	///获取
	return true;
}
bool FileOp::if_open()
{
	if (file == NULL)
		return false;
	else
		return true;
}
void FileOp::close()
{
	fclose(file);
	file = NULL;
}

void FileOp::destroy()
{
	remove(name.c_str());
}

int FileOp::length()
{
	return get_page(fend());
}

bool FileOp::exist(int page)
{

	if (0 <= page&&page<length())
	{
		char s;
		p = &s;
		fget(get_point(page), 1);
		if (s)
			return false;
		else
			return true;
	}
	else
		return false;
}

int FileOp::add(char * info)
{
	int page;
	int point;

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

bool FileOp::del(int page)
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

bool FileOp::get(char * a, int page)
{
	if (!exist(page))
		return false;
	p = a;
	fget(get_point(page) + 1, block_size);
	return true;
}

int FileOp::get_num()
{
	return get_page(fend()) - stack_top;
}

void FileOp::read(char * a, int page, int point, int len)
{
	len = min(len, block_size);
	p = a;
	point += get_point(page) + 1;
	fget(point, len);
}

void FileOp::write(char * a, int page, int point, int len)
{
	len = min(len, block_size);
	p = a;
	point += get_point(page) + 1;
	fput(point, len);
}
void FileOp::fput(int point, int len)
{
	fseek(file, point, 0);
	fwrite(p, len, 1, file);
}

void FileOp::fget(int point, int len)
{
	fseek(file, point, 0);
	fread(p, len, 1, file);
}

int FileOp::fend()
{
	fseek(file, 0, 2);
	return ftell(file);
}

int FileOp::get_point(int page)
{
	return N + page * (block_size + 1);
}

int FileOp::get_page(int point)
{
	return (point - N) / (block_size + 1);
}
