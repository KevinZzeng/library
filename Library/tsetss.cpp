#include "Dao.h"
#include "DaoDemo.h"
#include <set>
int main() {


Table tab = Table("daodemo");
vector<pair<int,char*> > a = tab.get_all();

	char* s = a[0].second;
	char f[20];
	for (int j = 0; j < 20; j++)
		f[j] = s[j+8];

	//printf("%d", b.size());

	return 0;
}