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

point get_point(double r,point A,point B) {
	point v = A - B;
	double sh = -(B * v / length(v));
	point M = B + v / length(v) * sh;
	//if (length(M) > r + eps) return point(-100000000,-100000000);
	double x = sqrt(S(r) - M * M);
	M = M + v / length(v) * x;
	return M;
}

bool inhere(point A,point B,point C) {
	return ((A - B) * (A - C) <= 0);
}

double add(double r,point A,point B) {
	point v = A - B;
	double dis = fabs(A / B / length(v));
	double ans = 0;
	if (dis > r - eps) {
		double ang = acos(A * B / length(A) / length(B));
		ans = ang * r * r;
	} else if (dis < eps) return 0;
	else {
		point p1 = get_point(r,A,B);
		point p2 = get_point(r,B,A);
		if (inhere(p1,A,B) && inhere(p2,A,B)) {
			double ang = acos(p1 * A / length(p1) / length(A));
			ang += acos(p2 * B / length(p2) / length(B));
			ans = fabs(p1 / p2) + ang * r * r; 
		}
		else if (!inhere(p1,A,B) && !inhere(p2,A,B)) {
			if (inhere(A,p1,p2) && inhere(B,p1,p2)) ans = fabs(A / B);
			else {
				double ang = acos(A * B / length(A) / length(B));
				ans = ang * r * r;
			}
		}
		else if (inhere(p1,A,B)) {
			double ang = acos(p1 * A / length(p1) / length(A));
			ans = fabs(p1 / B) + ang * r * r;
		} else {
			double ang = acos(p2 * B / length(p2) / length(B));
			ans = fabs(p2 / A) + ang * r * r;
		}
	}
	if ((A - B) / B > 0) return ans;
	else return -ans;
}

double solve(double r,point A,point B,point C,point D) {
	double ans = 0;
	ans += add(r,A,B);
	ans += add(r,B,C);
	ans += add(r,C,D);
	ans += add(r,D,A);
	return fabs(ans) / 2.0;
}

point A,B,o;
double ans,r;

int main() {
	freopen("mammoth.in","r",stdin);
	freopen("mammoth.out","w",stdout);
	o.read(); scanf("%lf",&r);
	A.read(); B.read();
	A = A - o; B = B - o;
	ans = solve(r,A,point(A.x,B.y),B,point(B.x,A.y));
	printf("%.10lf\n",ans);
	return 0;	
}
