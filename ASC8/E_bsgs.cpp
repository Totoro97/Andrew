#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <iostream>
#define intl long long
using namespace std;
const int step = 100000;

intl Mo;

struct matrix {
	intl v[2][2];

	void operator *= (matrix b) {
		matrix a; memcpy(a.v,v,sizeof(v));
		memset(v,0,sizeof(v));
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				for (int k = 0; k < 2; k++)
					v[i][j] += a.v[i][k] * b.v[k][j], v[i][j] %= Mo;
	}

	bool judge() {
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				if (v[i][j] != (intl) (i == j)) return false;
		return true;
	}
} bg,ni,jp;

struct cmp {
	bool operator () (const matrix &a, const matrix &b) const {
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++) {
				if (a.v[i][j] < b.v[i][j]) return true;
				if (a.v[i][j] > b.v[i][j]) return false;
			}
		return false;
	}
};
	
map <matrix,int,cmp> st;

int main() {
	freopen("fibonacci.in","r",stdin);
	freopen("fibonacci_2.out","w",stdout);
	cin >> Mo;
	bg.v[0][1] = bg.v[1][0] = bg.v[1][1] = 1LL;
	jp = bg;
	for (int i = 1; i <= step; i++) {
		if (bg.judge()) { printf("%d",i); return 0; }
		st[bg] = i;
		bg *= jp;
	}
	ni.v[0][0] = Mo - 1LL; ni.v[1][0] = ni.v[0][1] = 1LL;
	bg = ni;
	for (int i = 1; i < step; i++) bg *= ni;
	ni = bg;
	for (int i = 1; i <= step; i++) {
		int k;
		if ((k = st[bg])) { cout << (intl) i * (intl) step + (intl) k; return 0; }
		bg *= ni;
	}
	printf("0");
	return 0;	
}
