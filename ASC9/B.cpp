#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 1010
using namespace std;

int A[101000],B[101000],C[101000];
int d[maxn][maxn],mark[maxn][maxn],num[maxn][maxn];
int n,m,top,ans[101000],que[maxn],ord[maxn],du[maxn];

int main() {
	freopen("electricity.in","r",stdin);
	freopen("electricity.out","w",stdout);
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= m; i++) {
		int a,b,c;
		scanf("%d %d %d",&A[i],&B[i],&C[i]);
		a = A[i]; b = B[i]; c = C[i];
		if (d[a][b] && c) { printf("-1"); return 0; }
		d[a][b]++;
		du[b]++;
		mark[a][b] = i;
	}
	int L = 0, R = 0;
	for (int i = 1; i <= n; i++)
		if (!du[i]) que[++R] = i;
	while (L < R) {
		int u = que[++L];
		for (int v = 1; v <= n; v++) {
			if (!d[u][v]) continue;
			du[v] -= d[u][v];
			if (!du[v]) que[++R] = v;
		}
	}
	L = 0,R = 0;
	memset(d,0,sizeof(d));
	memset(du,0,sizeof(du));
	for (int i = 1; i <= m; i++) {
		int a,b,c; a = A[i]; b = B[i]; c = C[i];
		if (c) swap(a,b);
		d[a][b]++;
		du[b]++;
	}
	
	for (int i = 1; i <= n; i++)
		if (!du[i]) ord[++R] = i;
	while (L < R) {
		int u = ord[++L];
		for (int v = 1; v <= n; v++) {
			if (!d[u][v]) continue;
			du[v] -= d[u][v];
			if (!du[v]) ord[++R] = v;
		}
	}

	memset(d,0,sizeof(d));
	for (int i = 1; i <= m; i++) d[A[i]][B[i]]++;
	
	if (R < n) { printf("-1"); return 0; }
	for (int i = 1; i <= n; i++) {
		int u = ord[i]; int k;
		for (k = 1; que[k] != u; k++);
		for (; k > i; k--) {
			int a = que[k - 1], b = que[k];
			if (d[a][b] > 1) { printf("-1"); return 0; }
			if (mark[a][b]) ans[++top] = mark[a][b];
			swap(que[k - 1],que[k]);
		}
	}
	
	printf("%d\n",top);
	for (int i = 1; i <= top; i++) printf("%d ",ans[i]);
	return 0;
}
