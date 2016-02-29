#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define intl long long
using namespace std;

intl f[10][20100];
int n,N;
intl ans;

void dfs(int k,int u,int st,int st_,int ts) {
	if (u > k * 2 + 1) {
		f[N][ts] += f[N - 1][st];
		return;
	}
	
	if (u & 1) {
		int js = u >> 1;
		js--;
		if (js >= 0 && !((st_ >> js) & 1)) dfs(k,u + 2,st,st_ | (1 << js),ts);	
		else {
			js++;
			if (js < k && !((st_ >> js) & 1)) dfs(k,u + 2,st,st_ | (1 << js),ts);
			dfs(k,u + 2,st,st,ts | (1 << js));
		}
	}
}

int main() {
	freopen("hex.in","r",stdin);
	freopen("hex.out","w",stdout);
	scanf("%d",&n);
	f[0][0] = 1;	
	for (int i = n; i < n * 2; i++) {
		N++;
		for (int st = 0; st < (1 << i); st++) {			
			dfs(i,1,st,st,0);
		}
	}
	for (int st = 0; st < (1 << (n * 2)); st++)
		ans += f[N][st] * f[N][st];
	cout << ans << endl;
	return 0;
}
