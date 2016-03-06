#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int A[260],B[260],C[260],d[520][160],sou[260],ans[260];
int at,bt,ct,N,n,done[520];

bool solve() {
	for (int u = 0; u <= n; u++) {
		int v;
		for (v = 0; v <= n * 3 && (!d[v][u] || done[v]); v++);
		if (v > n * 3) { sou[u] = -1; continue; };
		done[v] = 1;
		sou[u] = v;
		for (int i = 0; i <= n * 3; i++) {
			if (i == v || !d[i][u]) continue;
			for (int j = 0; j <= n + 1; j++)
				d[i][j] ^= d[v][j];
		}
	}
	for (int i = 0; i <= n * 3; i++) {
		int flag = 0;
		for (int j = 0; j <= n; j++) flag |= d[i][j];
		if (!flag && d[i][n + 1]) return false;
	}
	N = -1;
	for (int i = 0; i <= n; i++) {
		if (sou[i] == -1) { continue; }
		ans[i] = d[sou[i]][n + 1];
		d[sou[i]][n + 1] ^= ans[i];
		if (ans[i]) N = i;
	}
	return true;
}

int main() {
	freopen("quadratic.in","r",stdin);
	freopen("quadratic.out","w",stdout);
	scanf("%d",&at);
	for (int i = at; i >= 0; i--) scanf("%d",&A[i]), A[i] = (A[i] % 2 + 2) % 2;
	scanf("%d",&bt);
	for (int i = bt; i >= 0; i--) scanf("%d",&B[i]), B[i] = (B[i] % 2 + 2) % 2;
	scanf("%d",&ct);
	for (int i = ct; i >= 0; i--) scanf("%d",&C[i]), C[i] = (C[i] % 2 + 2) % 2;
	n = 150;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= at; j++)
			if (A[j]) d[i * 2 + j][i] ^= 1;
		for (int j = 0; j <= bt; j++)
			if (B[j]) d[i + j][i] ^= 1;
	}
	for (int i = 0; i <= ct; i++) d[i][n + 1] = C[i];
	if (!solve()) { printf("no solution\n"); return 0; }	
	if (N == -1) { printf("-1\n"); return 0; }
	printf("%d  ",N);
	for (int i = N; i >= 0; i--) printf("%d ",ans[i]);
	putchar('\n');
	return 0;
}
