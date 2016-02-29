#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 20100
using namespace std;

int n,ans,M,Mnum,tot;
int w[maxn];
char s[maxn];

struct node {
	node *f,*nex[39];
	int ml,mark,vis;	
	node () { mark = vis = ml = 0; }
} pool[maxn],*tail, *head;

void add(int ch,int len) {
	node *p = tail, *np = &pool[++tot];
	np -> ml = len;
	for (; p && !p -> nex[ch]; p = p -> f) p -> nex[ch] = np;
	tail = np;
	if (!p) np -> f = head;
	else {
		if (p -> nex[ch] -> ml == p -> ml + 1) np -> f = p -> nex[ch];
		else {
			node *q = p -> nex[ch], *just = &pool[++tot];
			*just = *q;
			just -> ml = p -> ml + 1;
			q -> f = np -> f = just;
			for (; p && p -> nex[ch] == q; p = p -> f) p -> nex[ch] = just;
		}
	}
}

void dfs(node *u) {
	int flag = 0;
	u -> vis = 1;
	for (int i = 0; i < 38; i++) if (u -> nex[i]) flag++;
	if ((flag > 1) && u != head) {
		ans++; //printf("%d\n",u -> ml);
		if (u -> ml > M) M = u -> ml, Mnum = 1;
		else if (u -> ml == M) Mnum++;
	}
	
	for (int i = 0; i < 36; i++)
		if (u -> nex[i] && !u -> nex[i] -> vis)
			dfs(u -> nex[i]);
}

int main() {
	freopen("dna.in","r",stdin);
	freopen("dna.out","w",stdout);
	for (int i = 0; i < 10; i++) w['0' + i] = i;
	for (int i = 0; i < 26; i++) w['A' + i] = i + 10;
	s[1] = '%';
	scanf("%s",s + 2); n = strlen(s + 1);
	s[++n] = '#';
	w['%'] = 36; w['#'] = 37;
	head = tail = &pool[++tot];
	for (int i = 1; i <= n; i++) add(w[s[i]],i);
	for (node *js = tail; js; js = js -> f) js -> mark = 1;
	dfs(head);
	printf("%d\n%d\n%d\n",ans,M,Mnum);
	return 0;
}
