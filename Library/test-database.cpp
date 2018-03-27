#include "Dao.h"
#include <iostream>
using namespace std;
int main()
{
	string s = "dfsdf";
	char q[20] = { "4rtweer" };
	char p[20];
	int w[2] = { 5,3 };
	bool e[2] = { 1,0 };
	Table tab = Data::create_table(s, 2, w, e);
	int id = tab.add(q);
	int len = tab.size();
	bool t = tab.del(id);
	id = tab.add(q);
	vector<pair<int, char*> > a = tab.get_all();
	for (int i = 0; i < a.size(); i++) {
		cout << a[i].first << ' ' << a[i].second << endl;
		delete[] a[i].second;
	}
	return 0;
}