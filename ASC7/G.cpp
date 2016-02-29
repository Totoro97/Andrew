#include <cstdio>
#include <cstring>
#include <algorithm>
#define INF (1 << 30)
#define eps (1e-6)
#define maxn 101000
using namespace std;

struct str { int v,nex; double cap; } edge[maxn];

typedef int arr32[maxn];
arr32 ans,A,B,d,vis,que,fst,mark;
int top,e,s,t,n,m,cl,T;
double C[maxn],L,R,flow;
int js;

void make_edge(int a,int b,double cap) {
	edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b; edge[e].cap = cap;
	edge[++e].nex = fst[b]; fst[b] = e; edge[e].v = a; edge[e].cap = cap;
}

bool bfs() {
	int L = 0, R = 0;
	que[++R] = s; vis[s] = ++cl; d[s] = 0;
	while (L < R) {
		int u = que[++L];
		for (int i = fst[u]; i; i = edge[i].nex) {
			int v = edge[i].v;
			if (edge[i].cap > eps && vis[v] != cl) {
				vis[v] = cl;
				d[v] = d[u] + 1;
				que[++R] = v;
			}
		}
	}
	return (vis[t] == cl);
}

double dfs(int u,double ma) {
	//if (++js > 100000000) return 0;
	if (u == t || ma < eps) return ma;
	double flow = 0, f;
	for (int i = fst[u]; i; i = edge[i].nex) {
		int v = edge[i].v;
		if (d[v] == d[u] + 1 && ((f = dfs(v,min(edge[i].cap,ma))) > 0)) {
			flow += f; ma -= f;
			edge[i].cap -= f; edge[i ^ 1].cap += f;
			if (ma < eps) return flow;
		}
	}
	d[u] = INF;
	return flow;
}

void dinic() {
	js = 0;
	while (bfs())
		flow += dfs(s,INF);
}

int main() {
	freopen("network.in","r",stdin);
	freopen("network.out","w",stdout);
	scanf("%d %d",&n,&m);
	L = INF; R = -INF; s = 1; t = n;
	L = 0;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %lf",&A[i],&B[i],&C[i]);
		L = min(L,C[i]);
		R = max(R,C[i]);
	}

	while (R - L > eps || (!T)) {
		T++;
		double mid = (L + R) / 2.0; e = 1;
		flow = 0; top = 0;
		for (int i = 1; i <= n; i++) fst[i] = 0;
		for (int i = 1; i <= m; i++) {
			double cap = C[i] - mid;
			make_edge(A[i],B[i],cap);
			if (cap < eps) { flow += cap; ans[++top] = i; mark[i] = T; }
		}
		dinic();
		if (flow > 0) L = mid;
		else R = mid;
	}
	
	for (int i = 2; i <= e; i++)
		if (vis[edge[i].v] == cl && vis[edge[i ^ 1].v] != cl && mark[i / 2] != T) ans[++top] = i / 2;

	printf("%d\n",top);
	
	for (int i = 1; i <= top; i++) printf("%d ",ans[i]);
	return 0;
}
