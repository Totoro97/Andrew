#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 101000
using namespace std;
char A[maxn],B[maxn],A_[maxn],B_[maxn];
int p,m,n1,n2;
int d[30][30],val[30];

int main() {
	freopen("traces.in","r",stdin);
	freopen("traces.out","w",stdout);
	scanf("%d %d",&p,&m);
	for (int i = 1; i <= m; i++) {
		char a,b;
		do a = getchar(); while (a < 'a' || a > 'z');
		b = getchar();
		d[a - 'a'][b - 'a'] = 1; 
		d[b - 'a'][a - 'a'] = 1;
	}
	scanf("%s",A + 1); n1 = strlen(A + 1);
	scanf("%s",B + 1); n2 = strlen(B + 1);
	if (n1 != n2) {
		printf("NO"); return 0;
	}
	for (int i = 1; i <= n1; i++)
		val[A[i] - 'a']++;
	for (int i = 1; i <= n2; i++)
		val[B[i] - 'a']--;
	for (int i = 0; i < p; i++)
		if (val[i] != 0) { printf("NO"); return 0; }
	for (int a = 0; a < p; a++)
		for (int b = a + 1; b < p; b++) {
			int ta = 0,tb = 0;
			if (d[a][b]) continue;	
			for (int i = 1; i <= n1; i++)
				if (A[i] - 'a' == a || A[i] - 'a' == b) A_[++ta] = A[i];
			for (int i = 1; i <= n2; i++)
				if (B[i] - 'a' == a || B[i] - 'a' == b) B_[++tb] = B[i];
			if (ta != tb) { printf("NO"); return 0; }
			for (int i = 1; i <= ta; i++)
				if (A_[i] != B_[i]) {
					printf("NO");
					return 0;
				}
		}
	printf("YES");
	return 0;
}
