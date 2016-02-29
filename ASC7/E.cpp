#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define intl long long
using namespace std;

const intl phi_[13] = { 0,1,1,2,2,4,2,6,4,6,4,10,4 };
intl p,n,N;

intl get_phi(intl a) {
	intl ans = 1LL;
	for (intl i = 2LL; i <= 12LL; i++) {
		int k = 0;
		while (!(a % i)) k++, a /= i;
		if (!k) continue;
		ans *= phi_[i];
		for (k--; k; k--) ans *= i;
	}
	return ans;
}

intl ksm(intl a,intl b,intl N) {
	if (!a) return 0;
	intl ans = 1;
	for (; b; b >>= 1) {
		if (b & 1LL) ans *= a, ans %= N;
		a *= a; a %= N;		
	}
	return ans;
}

intl solve(intl a,intl n) {
	if (n == 1) { return 0LL; }
	intl p = get_phi(n);
	return p + ksm(a,solve(a,p),n);
}

int main() {
	freopen("limit.in","r",stdin);
	freopen("limit.out","w",stdout);
	cin >> p >> n;
	N = 1LL;
	for (intl i = 1LL; i <= n; i++) N *= i;
	intl u = solve(p,N);
	cout << ksm(p,u,N) % N << endl;
	return 0;
}
