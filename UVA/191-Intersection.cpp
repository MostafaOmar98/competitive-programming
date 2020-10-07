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
struct Point{
    int x, y;
    Point(int x = 0, int y= 0)
    {
        this->x = x;
        this->y = y;
    }
    Point operator-(Point other) const{
        return Point(x - other.x, y - other.y);
    }
    int cross(Point other) const{
        return x * other.y - y * other.x;
    }
    int dot(Point other) const{
        return x * other.x + y * other.y;
    }
    friend istream& operator>>(istream& in, Point &p){
        in >> p.x >> p.y;
        return in;
    }
};
int sign(int x)
{
    if (!x)
        return x;
    return x > 0 ? 1 : - 1;
}
int orient(Point a, Point b, Point c)
{
    Point ab = b - a, ac = a - c;
    return sign(ab.cross(ac));
}

struct LineSegment{
    Point st, en;
    LineSegment(Point st, Point en)
    {
        this->st = st;
        this->en = en;
    }

    bool onDisk(Point p) const
    {
        Point ca = st - p, cb = en - p;
        return ca.dot(cb) <= 0;
    }

    bool onSegment(Point p) const{
        return onDisk(p) && orient(st, en, p) == 0;
    }

    bool intersects(LineSegment other) const{
        if (orient(st, en, other.st) * orient(st, en, other.en) < 0 && orient(other.st, other.en, st) * orient(other.st, other.en, en) < 0)
            return true;
        bool ok = onSegment(other.st) || onSegment(other.en) || other.onSegment(st) || other.onSegment(en);
        return ok;
    }
};

void myMain()
{
    Point u, v;
    cin >> u >> v;
    Point rin1, rin2;
    cin >> rin1 >> rin2;
    int x1 = min(rin1.x, rin2.x), x2 = max(rin1.x, rin2.x), y1 = min(rin1.y, rin2.y), y2 = max(rin1.y, rin2.y);
    Point a(x1, y1), b(x2, y1), c(x2, y2), d(x1, y2);
    if (orient(a, b, u) * orient(d, c, u) < 0 && orient(a, b, v) * orient(d, c, v) < 0 && orient(b, c, u) * orient(a, d, u) < 0 && orient(b, c, v) * orient(a, d, v) < 0)
    {
        cout << "T\n";
        return;
    }
    LineSegment seg(u, v), ab(a, b), bc(b, c), cd(c, d), ad(a, d);
    bool ok = seg.intersects(ab) || seg.intersects(bc) || seg.intersects(cd) || seg.intersects(ad);
    if (ok)
        cout << "T\n";
    else
        cout << "F\n";
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