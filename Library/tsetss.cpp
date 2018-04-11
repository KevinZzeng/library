#include "Dao.h"
#include "DaoDemo.h"
#include <set>
#include <string>
int main() {


//Table tab = Table("daodemo");
//vector<pair<int,char*> > a = tab.get_all();
//
//	char* s = a[0].second;
//	char f[20];
//	for (int j = 0; j < 20; j++)
//		f[j] = s[j+8];

	//printf("%d", b.size());


	char a[10];
	char b[10];
	string bb = "aa";
	string aa = "aa";
	strcpy(a, aa.c_str());
	memcpy(b, bb.c_str(), 10);
	printf("===aaaa===");
	for (int i = 0; i < 10; i++)
		printf("%d ", a[i]);
	printf("\n");

	printf("===bbb===");
	for (int i = 0; i < 10; i++)
		printf("%d ", b[i]);
	printf("\n");


	return 0;
}