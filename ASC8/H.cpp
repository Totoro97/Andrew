#include <cstdio>
#include <cstring>
#include <algorithm>
#define INF (1 << 20)
using namespace std;
int n,m,d[110][110],size,L,R,ans;
int f[110][110],pas[110][110];
int main() {
	freopen("roads.in","r",stdin);
	freopen("roads.out","w",stdout);
	scanf("%d %d",&n,&m);
	size = n / (m - 1);
	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= m; j++)
			f[i][j] = INF;
	for (int j = 1; j <= m; j++) f[0][j] = INF;
	for (int i = 1; i <= n; i++) {
		for (int k = 1; k <= m - 1; k++)
			for (int j = i - 1; j >= 0; j--) {
				if (f[j][k - 1] + (i - j) * (i - j - 1) < f[i][k]) {
					f[i][k] = f[j][k - 1] + (i - j) * (i - j - 1);
					pas[i][k] = j;
				}
			}
	}

	for (R = n; R; R = pas[R][--m]) {
		L = pas[R][m - 1] + 1;
		for (int i = L; i <= R; i++)
			for (int j = L; j <= R; j++)
				d[i][j] = 1;
	}
	ans = 0;
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			if (!d[i][j]) ans++;
	printf("%d\n",ans);
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			if (!d[i][j]) printf("%d %d\n",i,j);
	return 0;
}
