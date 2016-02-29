#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#define intl long long
using namespace std;
const int step = 1000000;

intl Mo,ans,M;

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

void ksm(intl a) {
	bg.v[0][0] = bg.v[1][1] = 1; bg.v[1][0] = bg.v[0][1] = 0;
	jp.v[0][0] = 0; jp.v[1][1] = jp.v[1][0] = jp.v[0][1] = 1;
	for (; a; a >>= 1) {
		if (a & 1LL) bg *= jp;
		jp *= jp;
	}
}

intl gcd(intl a,intl b) { return b ? gcd(b, a % b) : a; }

intl lcm(intl a,intl b) { return a * b / gcd(a,b); }

intl solve(intl k) {
	if (Mo == 5LL) return 20LL * k;
	intl p;
	if (Mo % 5LL == 1 || Mo % 5LL == 4) p = Mo - 1;
	else p = 2LL * Mo + 2LL;
	intl ans = 1LL << 63 - 1LL;
	for (intl i = 1; i * i <= p; i++) {
		if (p % i) continue;
		ksm(i); if (bg.judge()) ans = min(ans,i);
		ksm(p / i); if (bg.judge()) ans = min(ans,p / i);
	}
	return ans * k;
}

int main() {
	freopen("fibonacci.in","r",stdin);
	freopen("fibonacci.out","w",stdout);
	cin >> M;
	ans = 1LL;
	for (int i = 2; (intl)i * (intl) i <= M; i++) {
		if (M % (intl) i != 0LL) continue;
		Mo = (intl) i; intl k = 1LL;
		while (!(M % (intl) i)) M /= (intl) i, k *= (intl) i;		
		ans = lcm(ans,solve(k / (intl) i));
	}
	if (M != 1LL) {
		Mo = (intl) M;
		ans = lcm(ans,solve(1LL));		
	}
	cout << ans << endl;
	return 0;	
}
