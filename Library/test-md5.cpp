#include <cstring>
#include <string>
#include <cstdio>
#include "md5.h"  
#include <iostream>
#include "Utils.h"
using namespace std;
int main(int argc, char *argv[])
{
	string n = Utils::getNowTime();
	cout << MD5(n).toStr32() << endl;
	cout << MD5(n).toStr16() << endl;

	return 0;
}