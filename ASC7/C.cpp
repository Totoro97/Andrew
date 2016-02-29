#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

const int Mo = 1000007;

int n,A[3010];

struct Hash {
	
	int e;
	int fst[1010000];
	int val[10100],nex[10100],num[10100];

	int make_hash(int a) { return ((a * 31 + 233) % Mo + Mo) % Mo; }

	int find(int a) {
		for (int i = fst[make_hash(a)]; i; i = nex[i])
			if (val[i] == a) return i;
		return 0;
	}
	
	void add(int k,int a) {
		int u = find(a);
		int has = make_hash(a);
		if (!u) {
			u = ++e;
			nex[u] = fst[has]; fst[has] = u;
			val[u] = a; num[u] = k; 
		} else {
			num[u] = k;
		}
	}
} hash;

int u_,v_;
short f[3010][3010],nex[3010][3010];
short ans;

int main() {
	freopen("fibsubseq.in","r",stdin);
	freopen("fibsubseq.out","w",stdout);
	scanf("%d",&n);
	u_ = 1; v_ = 0;
	for (int i = 1; i <= n; i++) scanf("%d",&A[i]);
	ans = 1;
	for (int v = n; v >= 1; v--) {
		for (int u = v - 1; u >= 1; u--) {
			int js = hash.find(A[u] + A[v]);
			if (js) f[u][v] = f[v][hash.num[js]] + 1, nex[u][v] = hash.num[js];
			else f[u][v] = 2, nex[u][v] = 0;
			if (f[u][v] > ans) {
				ans = f[u][v];
				u_ = u;
				v_ = v;
			}
		}
		hash.add(v,A[v]);
	}
	
	printf("%d\n",ans);
	printf("%d ",A[u_]);
	for (; v_; ) {
		printf("%d ",A[v_]);
		int k = nex[u_][v_];
		u_ = v_; v_ = k;
	}
	return 0;
}
