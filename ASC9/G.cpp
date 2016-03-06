#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#define maxn 4010
using namespace std;

map <int,int> st;
int num[maxn],mark[maxn][4];
int A[maxn],ans[maxn][5];
int n,top;

int main() {
	freopen("rhymes.in","r",stdin);
	freopen("rhymes.out","w",stdout);
	scanf("%d",&n);
	for (int i = 1; i <= n; i++) scanf("%d",&A[i]), st[A[i]] = 1;
	for (map <int,int> :: iterator p = st.begin(); p != st.end(); p++)
		p -> second = ++top;
	for (int i = 1; i <= n; i++) A[i] = st[A[i]];
	top = 0;
	int L,R;
	for (L = 1; L <= n; L = R) {
		int k = 0,p = 0;
		for (R = L; R <= n && k < 2 && p < 1; R++) {
			if (++num[A[R]] == 2) k++;
			if (num[A[R]] == 4) p++;
		}
		if (k == 2) {
			top++; int t = 0;
			for (int i = L; i < R; i++) {
				if (num[A[i]] == 3) num[A[i]] = 2;
				else if (num[A[i]] == 2) ans[top][++t] = i;
			}
		} else if (p == 1) {
			top++; int t = 0;
			for (int i = L; i < R; i++) {
				if (num[A[i]] == 4) ans[top][++t] = i;
			}
		}
		for (int i = L; i < R; i++) num[A[i]] = 0;		
	}
	printf("%d\n",top);
	for (int i = 1; i <= top; i++)  {
		for (int j = 1; j <= 4; j++) printf("%d ",ans[i][j]);
		putchar('\n');
	}
	return 0;
}
