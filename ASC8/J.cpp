#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define eps (1e-8)
#define maxn 101000
#define INF (1 << 30)
using namespace std;

const double pi = acos(-1);
const double tpi = 2.0 * pi;

struct point {
	double x,y;
	point (double x = 0,double y = 0) : x(x) , y(y) {}
	void read() { scanf("%lf %lf",&x,&y); }
} A[maxn],B[maxn],bg;

point  operator + (point a,point b) { return point(a.x + b.x, a.y + b.y); }
point  operator - (point a,point b) { return point(a.x - b.x, a.y - b.y); }
double operator * (point a,point b) { return (a.x * b.x + a.y * b.y); }
double operator / (point a,point b) { return (a.x * b.y - a.y * b.x); }
point  operator * (point a,double b) { return point(a.x * b,a.y * b); }
point  operator / (point a,double b) { return point(a.x / b,a.y / b); }

double length(point a) { return sqrt(a * a); }

double get_ang(point a) {
	double ans = acos(a * point(1,0) / length(a));
	if (a.y < 0) ans = 2.0 * pi - ans;
	return ans;
}


struct str { double L,R,d; } interA[maxn],interB[maxn];

int n,m,nt,mt;
char ch;

bool judge(double ang) {
	double disA = INF + 1, disB = INF;
	for (int i = 1; i <= n; i++) {
		double sing = get_ang(A[i]);
		sing = fabs(sing - ang);
		if (sing > pi) sing = tpi - sing;
		if (sing > pi / 2.0 - eps) continue;
		double dis = length(A[i]);
		double lea = dis * sin(sing);
		if (lea > 2.0) continue;
		disA = min(disA,dis * cos(sing) - sqrt(4.0 - lea * lea));
	}
	
	for (int i = 1; i <= m; i++) {
		double sing = get_ang(B[i]);
		sing = fabs(sing - ang);
		if (sing > pi) sing = tpi - sing;
		if (sing > pi / 2.0 - eps) continue;
		double dis = length(B[i]);
		double lea = dis * sin(sing);
		if (lea > 2.0) continue;
		disB = min(disB,dis * cos(sing) - sqrt(4.0 - lea * lea));
	}
	
	return (disA < disB + eps);
}

int main() {
	freopen("snooker.in","r",stdin);
	freopen("snooker.out","w",stdout);
	scanf("%d %d %c",&n,&m,&ch);
	bg.read();
	for (int i = 1; i <= n; i++) A[i].read(), A[i] = A[i] - bg;
	for (int i = 1; i <= m; i++) B[i].read(), B[i] = B[i] - bg;
	if (ch == 'C') {
		for (int i = 1; i <= max(n,m); i++) swap(A[i],B[i]);
		swap(n,m);
	}
	double step = tpi / 100000;
	for (double ang = 0; ang <= tpi + eps; ang += step) {
		if (judge(ang)) { printf("NO"); return 0; }
	}
	printf("YES");
	return 0;
}
