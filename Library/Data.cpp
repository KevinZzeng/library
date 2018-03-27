#include "Data.h"

Table Data::create_table(string name, int num, int len[], bool ifsearch[])
{
	return Table(name, num, len, ifsearch);
}

void Data::delete_table(string name)
{
	remove(name.c_str());
	remove((name + ".pag").c_str());
}

Table Data::get_table(string name)
{
	return Table(name);
}