#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int main() {
	int n;
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
	scanf("%d",&n);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == j) {
				if (i < n) printf("0 ");
				else printf("1000 ");
			}
			else printf("1 ");
		}
		putchar('\n');
	}
	return 0;
}
