#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 201000
#define intl long long
using namespace std;

struct str { int a,b,num; intl c; } edge[maxn];

int fa[maxn],mark[maxn],ans[maxn];
int n,m,top;
intl al;

bool cmp(const str &a, const str &b) {
	return (a.c > b.c);
}

int find(int a) { return (fa[a] == a ? a : (fa[a] = find(fa[a]))); }

int main() {
	freopen("oil.in","r",stdin);
	freopen("oil.out","w",stdout);
	scanf("%d %d %lld",&n,&m,&al);
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %lld",&edge[i].a,&edge[i].b,&edge[i].c);
		edge[i].num = i;
	}
	sort(edge + 1, edge + m + 1, cmp);
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= m; i++) {
		int a = edge[i].a, b = edge[i].b;
		if (find(a) == find(b)) continue;
		fa[fa[a]] = fa[b];
		mark[i] = 1;
	}
	for (int i = m; i >= 1; i--) {
		if (mark[i]) continue;
		if (al >= edge[i].c) ans[++top] = edge[i].num, al -= edge[i].c;
	}
	printf("%d\n",top);
	for (int i = 1; i <= top; i++) printf("%d ",ans[i]);
	return 0;
}
