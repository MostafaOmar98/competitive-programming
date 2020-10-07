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
enum {LESS, EQUAL, GREATER};
int dcmp(ld x, ld y)
{
    if (fabs(x - y) <= eps)
        return EQUAL;
    return x > y ? GREATER : LESS;
}

struct Point{
    int x, y;
    Point operator-(Point other) const{
        return {x - other.x, y - other.y};
    }

    int cross(Point other) const {
        return x * other.y - y * other.x;
    }

    int dot(Point other) const{
        return x * other.x + y * other.y;
    }

    friend istream& operator>>(istream &in, Point &p){
        cin >> p.x >> p.y;
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
};

struct LineSegment{
    Point st, en;

    bool onLine(Point p) const
    {
        return Line(st, en).f(p) == 0;
    }

    bool onDisk(Point p) const{
        Point ca = st - p, cb = en - p;
        return ca.dot(cb) <= 0;
    }
    bool onSegment(Point p) const {
        return onLine(p) && onDisk(p);
    }

    bool intersect(LineSegment other) const{
        bool ok = orient(st, en, other.st) * orient(st, en, other.en) < 0;
        ok &= orient(other.st, other.en, st) * orient(other.st, other.en, en) < 0;
        ok |= onSegment(other.st) || onSegment(other.en) || other.onSegment(st) || other.onSegment(en);
        return ok;
    }
};

const int MAX_N = 15;
bool adj[MAX_N][MAX_N];
int n;
int vis[MAX_N], vid;
bool dfs(int cur, int target)
{
    if (cur == target)
        return true;
    if (vis[cur] == vid)
        return false;
    vis[cur] = vid;
    bool ret = false;
    for (int i = 0; i < n; ++i)
        if (adj[cur][i])
            ret |= dfs(i, target);
    return ret;
}
void myMain()
{
    cin >> n;
    vector<LineSegment> segs(n);
    rep(i,0,n)
        cin >> segs[i].st >> segs[i].en;
    clr(adj, false);
    rep(i,0,n)
    {
        rep(j,0,n)
        {
            if (segs[i].intersect(segs[j]))
                adj[i][j] = true;
        }
    }

    int i, j;
    while(cin >> i >> j && (i && j))
    {
        --i;
        --j;
        ++vid;
        if (dfs(i, j))
            cout << "CONNECTED\n";
        else
            cout << "NOT CONNECTED\n";
    }
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
    {
        myMain();
        if(tc)
            cout << "\n";
    }

}