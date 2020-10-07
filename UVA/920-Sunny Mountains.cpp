#include<bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#define debug(...) debug_out(vec_splitter(#__VA_ARGS__), 0, __LINE__, __VA_ARGS__)
#else
#define debug(...) ;
#endif
vector<string> vec_splitter(string s) {
    s += ',';
    vector<string> res;
    while(!s.empty()) {
        res.push_back(s.substr(0, s.find(',')));
        s = s.substr(s.find(',') + 1);
    }
    return res;
}
void debug_out(
        vector<string> __attribute__ ((unused)) args,
        __attribute__ ((unused)) int idx,
        __attribute__ ((unused)) int LINE_NUM) { cerr << endl; }
template <typename Head, typename... Tail>
void debug_out(vector<string> args, int idx, int LINE_NUM, Head H, Tail... T) {
    if(idx > 0) cerr << ", "; else cerr << "Line(" << LINE_NUM << ") ";
    stringstream ss; ss << H;
    cerr << args[idx] << " = " << ss.str();
    debug_out(args, idx + 1, LINE_NUM, T...);
}

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
enum {LESS, EQUAL, GREATER};
int dcmp(ld x, ld y)
{
    if (fabs(x - y) <= eps)
        return EQUAL;
    return x > y ? GREATER : LESS;
}
long double to_deg(ld angle)
{
    return angle * 180.0 / PI;
}

int sign(int x)
{
    if (!x)
        return 0;
    return x > 0 ? 1 : -1;
}

struct Point{
    int x, y;
    void normalize()
    {
        // (0, 0)?
        if (x == 0)
            y = sign(y); // sign matters?
        else if (y == 0)
            x = sign(x); // sign matters?
        else
        {
            int d = __gcd(abs(x), abs(y));
            x /= d;
            y /= d;
        }
    }
    Point operator-(Point other) const{
        return {x - other.x, y - other.y};
    }
    int getQuad() const {
        if (x >= 0)
            return y >= 0 ? 0 : 3;
        return y >= 0 ? 1 : 2;
    }
    int cross (Point other) const{
        return x * other.y - y * other.x;
    }
    int dot(Point other) const {
        return x * other.x + y * other.y;
    }
    int len2() const {
        return dot((*this));
    }
    bool operator<(const Point &other) const {
        return x < other.x;
    }
    bool operator == (const Point &other) const{
        return getQuad() == other.getQuad() && cross(other) == 0;
    }
    ld getAngleTo(Point other) const{
        ld ret = atan2(cross(other), dot(other));
        if (ret < 0)
            ret += 2 * PI;
        return to_deg(ret);
    }

    long double getDegrees() const{
        long double ret = atan2(y, x);
        if (ret < 0)
            ret += 2 * PI;
        return to_deg(ret);
    }
    friend istream& operator>>(istream& in, Point &p) {
        in >> p.x >> p.y;
        return in;
    }
};

int orient(Point a, Point b, Point c)
{
    Point ab = b - a, ac = c - a;
    return ab.cross(ac);
}

struct Line{
    int a, b, c;
    Line(Point p1, Point p2)
    {
        int dy = p1.y - p2.y, dx = p1.x - p2.x;
        a = dx;
        b = -dy;
        c = dy * p1.x - dx * p1.y;
    }

    int f(Point p) const
    {
        return a * p.y + b * p.x + c;
    }

    ld getX(int y) const{
        return 1.0 * (-c - a * y) / b;
    }
};

void myMain()
{
    int n;
    cin >> n;
    vector<Point> pts(n);
    rep(i,0,n)
        cin >> pts[i];
    sort(all(pts));
    long double ans = 0;
    int maxY = 0;
    for (int i = sz(pts) - 2; i >= 0; i -= 2)
    {
        Point a = pts[i], b = pts[i + 1];
        if (a.y < maxY)
            continue;
        ld x = Line(a, b).getX(maxY);
        ld dx = a.x - x, dy = a.y - maxY;
        ans += sqrt(dx * dx + dy * dy);
        maxY = a.y;
    }
    cout << fixed << setprecision(2) << ans << '\n';
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
    int tc;
    cin >> tc;
    while(tc--)
        myMain();
}