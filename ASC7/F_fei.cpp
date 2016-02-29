#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define S(a) ((a) * (a))
#define eps (1e-10)
using namespace std;

const double pi = acos(-1);

struct point {
	double x,y;
	point (double x = 0,double y = 0) : x(x) , y(y) {}
	void read() { scanf("%lf %lf",&x,&y); }
};

point  operator + (point a,point b) { return point(a.x + b.x, a.y + b.y); }
point  operator - (point a,point b) { return point(a.x - b.x, a.y - b.y); }
double operator * (point a,point b) { return (a.x * b.x + a.y * b.y); }
double operator / (point a,point b) { return (a.x * b.y - a.y * b.x); }
point  operator * (point a,double b) { return point(a.x * b,a.y * b); }
point  operator / (point a,double b) { return point(a.x / b,a.y / b); }

double length(point a) { return sqrt(a * a); }

double cut(point o,double r,point A,point B,point C) {
	point v = A - B;
	double dis = fabs(v / (o - B) / length(A - B));
	double ans = 0;
	if (dis > r + eps) return 0;
	double ang = acos(dis / r);
	double x = sqrt(S(r) - S(dis));
	ans = ang * r * r - dis * x;
	if (((o - B) / (A - B)) * ((A - B) / (C - B)) > 0) ans = r * r * pi - ans;
	return ans;
}

point get_point(double r,point A,point B) {
	point v = A - B;
	double sh = -(B * v / length(v));
	point M = B + v / length(v) * sh;
	if (length(M) > r + eps) return point(-100000000,-100000000);
	double x = sqrt(S(r) - M * M);
	M = M + v / length(v) * x;
	return M;
}

double rec(point o,double r,point A,point B,point C) {
	double ans = 0;
	A = A - o; B = B - o; C = C - o;
	if (length(A) > r + eps) return 0;
	point p1 = get_point(r,A,C);
	point p2 = get_point(r,A,B);
	double ang = acos(p1 * p2 / length(p1) / length(p2));
	if (p1 / p2 < 0) ang = -ang;
	ans += ang * r * r;
	ans += p2 / A + A / p1;
	return fabs(ans) / 2.0;
}

bool judge(point o,double r,point A,point B,point C) {
	A = A - o; B = B - o; C = C - o;
	if (length(A) < r - eps) return false;
	if (length(B) < r - eps) return false;
	if (length(C) < r - eps) return false;
	point p;
	p = get_point(r,A,B);
	if ((A - p) * (B - p) < eps) return false;
	p = get_point(r,A,C);
	if ((A - p) * (C - p) < eps) return false;
	p = get_point(r,B,C);
	if ((B - p) * (C - p) < eps) return false;
	if ((((B - A) / A) * ((C - B) / B) > eps)
		&& (((B - A) / A) * ((A - C) / C) > eps))
		return false;
	return true;
}

double solve(point o,double r,point A,point B,point C) {
	if (judge(o,r,A,B,C)) return 0; 
	//	return 0;
	double ans = r * r * pi;
	ans -= cut(o,r,A,B,C);
	ans -= cut(o,r,A,C,B);
	ans -= cut(o,r,B,C,A);
	ans += rec(o,r,A,B,C);
	ans += rec(o,r,B,A,C);
	ans += rec(o,r,C,A,B);
	return ans;
}

point o,A,B;
double r,ans;

int main() {
	freopen("mammoth.in","r",stdin);
	freopen("mammoth.out","w",stdout);
	o.read(); scanf("%lf",&r);
	A.read(); B.read();
	ans += solve(o,r,A,B,point(A.x,B.y));
	ans += solve(o,r,A,B,point(B.x,A.y));	
	printf("%.6lf\n",ans);
	return 0;	
}
