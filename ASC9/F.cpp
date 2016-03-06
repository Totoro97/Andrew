#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 1010
using namespace std;

int dna[maxn];
int d[maxn][maxn],d_origin[maxn][maxn],dep[maxn],fa[maxn],done[maxn],du[maxn];
int n,n_origin;

void make_dep(int u) {
	if (!fa[u]) dep[u] = 0;
	else if (dep[u]) return;
	else { make_dep(fa[u]); dep[u] = dep[fa[u]] + 1; }
}

int dis(int a,int b) {
	if (a == b) return 0;
	if (dep[a] > dep[b]) return dis(fa[a], b) + dna[a];
	else return dis(a, fa[b]) + dna[b];
}

int main() {
	freopen("restore.in","r",stdin);
	freopen("restore.out","w",stdout);
	scanf("%d",&n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d",&d[i][j]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			d_origin[i][j] = d[i][j];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (i != j && d[i][j] < 1) {
				printf("-1");
				return 0;
			}
	bool flag = true;
	n_origin = n;
	while (true) {
		int u = 0, D = -1;
		for (int i = 1; i <= n; i++) {
			if (done[i]) continue;
			int D_ = -1;
			for (int j = 1; j <= n; j++) {
				if (done[j] || i == j) continue;
				D_ = max(D_,d[i][j]);
			}
			if (D_ > D) u = i, D = D_;
		}
		if (!u || n > 500) break;
		int k = 0,v = 0; done[u] = 1;
		int ml = (1 << 30);
		for (int i = 1; i <= n; i++) {
			if (done[i] || i == u) continue;		
			for (int j = 1; j <= n; j++) {
				if (done[j] || j == u) continue;
				int js = (d[u][i] + d[u][j] + d[i][j]) / 2 - d[i][j];
				ml = min(ml,js);
			}
		}

		for (int i = 1; i <= n; i++) {
			if (done[i] || i == u) continue;
			if (d[u][i] == ml) k++, v = i;
		}
		
		if (ml <= 0 || k > 1) { flag = false; break; }		
		// bu yan ge;
		dna[u] = ml;
		if (k == 1) { fa[u] = v; }
		else {
			fa[u] = ++n;
			for (int i = 1; i < n; i++)
				d[i][n] = d[n][i] = d[u][i] - ml;
		}
	}
	
	if (!flag) { printf("-1"); return 0; }
	for (int i = 1; i <= n; i++) {
		if (fa[i]) { du[i]++; du[fa[i]]++; }
	}
	for (int i = 1; i <= n_origin; i++) {
		if (du[i] != 1) { printf("-1"); return 0; }
	}
	for (int i = 1; i <= n; i++)
		if (!dep[i]) make_dep(i);
	for (int i = 1; i <= n_origin; i++)
		for (int j = 1; j <= n_origin; j++) {
			if (dis(i,j) != d_origin[i][j]) { printf("-1"); return 0; }
		}
	int N = n;
	for (int i = 1; i <= n; i++)
		if (fa[i]) N += dna[i] - 1; 
	printf("%d\n",N);
	N = n;
	for (int i = 1; i <= n; i++) {
		if (fa[i]) {
			int u = i;
			for (int k = 1; k < dna[i]; k++) {
				printf("%d %d\n",u,++N);
				u = N;
			}
			printf("%d %d\n",u,fa[i]);
		}
	}
	return 0;
}
	
