#include<bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#define debug(...) debug_out(vec_splitter(#__VA_ARGS__), 0, __LINE__, __VA_ARGS__)
#else
#define debug(...) ;
#endif


typedef long long ll;
typedef long double ld;
#define rep(i, start, end) for(int i = start; i < end; ++i)
#define sz(x) (int)((x).size())
#define pb push_back
#define all(x) x.begin(), x.end()
#define clr(d, v) memset(d, v, sizeof(d))
#define pii pair<int, int>
#define X first
#define Y second
//#define debug(x) cerr << #x << " : " << (x) << " "
const double PI = 3.14159265358979323846;
const double eps = (1e-9);

struct Point{
    ld x, y;
    Point (ld x = 0, ld y = 0)
    {
        this->x = x;
        this->y = y;
    }
    Point operator+(Point p) const
    {
        return Point(x + p.x, y + p.y);
    }
    Point operator-(Point p) const
    {
        return Point(x - p.x, y - p.y);
    }
    Point operator*(ld scalar) const
    {
        return Point(scalar * x, scalar * y);
    }
    Point operator/(ld scalar) const
    {
        return Point(x/scalar, y/scalar);
    }
    ld dot(Point &p) const{
        return x * p.x + y * p.y;
    }
    ld len() const{
        return sqrt(x * x + y * y);
    }
    Point getVec(Point p) const{
        return p - *this;
    }
    ld dist(Point p) const{
        return getVec(p).len();
    }
    Point unit() const{
        return (*this)/len();
    }
    friend istream& operator>>(istream& in, Point &p){
        cin >> p.x >> p.y;
        return in;
    }
    friend ostream& operator<<(ostream& out, const Point &p) {
        out << p.x << " " << p.y;
        return out;
    }
};

bool onDisk(Point a, Point b, Point c)
{
    Point ca = a - c, cb = b - c;
    return ca.dot(cb) <= 0;
}
enum{LESS, GREATER, EQUAL};
int dcmp(ld x, ld y)
{
    if (fabs(x - y) <= eps)
        return EQUAL;
    if (x > y)
        return GREATER;
    return LESS;
}

struct Line{
    ld a, b, c;
    Line(Point a, Point b)
    {
        Point s = b - a;
        ld dx = s.x, dy = s.y;
        this->a = -dy;
        this->b = dx;
        this->c = -a.y * dx + a.x * dy;
    }
    ld f(Point p) const
    {
        return a * p.x + b * p.y + c;
    }
};

bool onLine(Point a, Point b, Point c)
{
    return dcmp(Line(a,b).f(c), 0) == EQUAL;
}

bool onSegment(Point a, Point b, Point c)
{
    return onDisk(a,b,c) && onLine(a, b, c);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
//    freopen("AC.txt", "w", stdout);
#endif
    cout << fixed << setprecision(4);
    Point m;
    while(cin >> m)
    {
        int n;
        cin >> n;
        n++;
        vector<Point> pt(n);
        rep(i,0,n)
            cin >> pt[i];

        long double minDist = 1e30;
        Point ans;
        rep(i,0,n - 1)
        {
            Point a = pt[i], b = pt[i + 1];
            Point dir = (b - a).unit(), am = m - a;
            Point proj = a + dir * dir.dot(am);
            ld d;
            if (onSegment(a, b, proj))
                d = m.dist(proj);
            else
            {
                d = m.dist(a);
                proj = a;
                if (m.dist(b) < d)
                {
                    d = m.dist(b);
                    proj = b;
                }
            }
            if (d < minDist)
            {
                minDist = d;
                ans = proj;
            }
        }
        cout << ans.x << '\n' << ans.y << '\n';
    }
}