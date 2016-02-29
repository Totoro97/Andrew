#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 150000
#define lk (u << 1)
#define rk ((u << 1) | 1)
#define midl ((L + R) >> 1)
#define midr (midl + 1)
using namespace std;

struct matrix {
	int v[2][2];
	void read() {
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				scanf("%d",&v[i][j]);
	}
} A[maxn],v[maxn];

int n,m,Mo;

matrix operator * (matrix A,matrix B) {
	matrix C;
	memset(C.v,0,sizeof(C.v));
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 2; k++)
				C.v[i][j] += A.v[i][k] * B.v[k][j];
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			C.v[i][j] %= Mo;
	return C;
}

void build(int u,int L,int R) {
	if (L == R) { v[u] = A[L]; return; }
	build(lk,L,midl);
	build(rk,midr,R);
	v[u] = v[lk] * v[rk];
	return;
}

matrix find(int u,int L,int R,int l,int r) {
	if (L == l && R == r) return v[u];
	if (r < midr) return find(lk,L,midl,l,r);
	else if (l > midl) return find(rk,midr,R,l,r);
	else {
		matrix A = find(lk,L,midl,l,midl);
		matrix B = find(rk,midr,R,midr,r);
		return A * B;
	}
}

int main() {
	freopen("crypto.in","r",stdin);
	freopen("crypto.out","w",stdout);
	scanf("%d %d %d",&Mo,&n,&m);
	for (int i = 1; i <= n; i++) A[i].read();
	build(1,1,n);
	for (int t = 1; t <= m; t++) {
		int a,b;
		scanf("%d %d",&a,&b);
		matrix ans = find(1,1,n,a,b);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) printf("%d ",ans.v[i][j]);
			putchar('\n');
		}
		if (t < m) putchar('\n');
	}
	return 0;
}
