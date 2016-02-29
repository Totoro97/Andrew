b#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int L,R,size,bg,res,ans,num,n;

int main() {
	freopen("perm.in","r",stdin);
	freopen("perm.out","w",stdout);
	scanf("%d",&n);
	for (ans = 1; ans * ans < n; ans++);
	size = ans;
	num = n / size; 
	if ((n % size)) {
		num++;
		bg = n % size;
	}
	else bg = size;
	res = min(size - num,bg);	
	for (int i = 1; i <= res; i++) printf("%d ",i);
	for (int i = res + 1; i <= bg; i++) printf("%d ",bg - i + res + 1);
	L = bg + 1; R = L + size - 1;
	for (; R <= n; L += size, R += size) {
		for (int i = R; i >= L; i--) printf("%d ",i);
	}
	return 0;
}
