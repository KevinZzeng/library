#include <vector>
#include <iostream>
#include <list>
#include <cstring>
#include <cstdio>

#include <algorithm>
#include <set>
#include "Utils.h"
#include <map>
using namespace std;




void add(const char *tableNmae, vector<pair<int, char *> > v) {
	char *begin = NULL;
	for (vector<pair<int, char *> >::iterator it = v.begin(); it != v.end(); ++it) {
		cout << it->first << "  " << it->second << endl;

	}


}


int main() {
	

	//set<int> a;
	//set<int> b;
	//a.insert(1);
	//a.insert(2);
	//a.insert(3);
	//a.insert(4);

	//b.insert(3);
	//b.insert(4);
	//Utils::setIntersection(a, b);
	//for (set<int>::iterator it = a.begin(); it != a.end(); ++it)
	//	cout << *it << endl;
	
	map<int, int> a;
	for (int i = 0; i < 5; i++) {
		a.insert(pair<int, int>(i - 1, i));
	}

	for (int i = 0; i < 5; i++)
		cout << a[i - 1];













	//h.b = 998244353;
	//h.c = 5.0;

	//
	//char *hhh;
	//char *ss = reinterpret_cast<char *>(&h.b);
	////strcpy(hhh,)
	////int bnn = 222;
	//for (int i = 0; i < 4; i++){
	//	printf("%d ", ss[i]);
	//}
	//cout << endl;



	return 0;
}