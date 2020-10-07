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


struct Line{
    // a * y + b * x + c = 0
    // slope is -b/a
    // in this line we maintain a = 1 unless it's vertical. For integral line you dont have to maintain this but other functions will get more complicated
    ll a, b, c;
    Line(pair<int, int> p1, pair<int, int> p2)
    {
        ll dy = p2.Y - p1.Y, dx = p2.X - p1.X;
        a = dx;
        b = -dy;
        c = p1.X * dy - p1.Y * dx;
        int sgn = 1;
        if (a < 0 || (a == 0 && b < 0))
            sgn = -1;
        int d = __gcd(abs(a), __gcd(abs(b), abs(c)));
        if (d)
        {
            a /= d;
            b /= d;
            c /= d;
        }
        a *= sgn;
        b *= sgn;
        c *= sgn;
    }
    bool operator<(const Line &other) const{
        if (a != other.a)
            return a < other.a;
        if (b != other.b)
            return b < other.b;
        return c < other.c;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("AC.txt", "w", stdout);
#endif
    int x, y;
    while(cin >> x >> y && (x || y))
    {
        vector<pair<int, int> > pts(1, {x, y});
        while(cin >> x >> y && (x || y))
            pts.push_back({x, y});

        map<Line, vector<int> > mp;
        rep(i,0,sz(pts))
        {
            rep(j,0,sz(pts))
            {
                if (pts[i] == pts[j])
                    continue;
                mp[Line(pts[i], pts[j])].push_back(i);
            }
        }
        vector<vector<pair<int, int> > > ans;
        for (auto &item : mp)
        {
            vector<int> &v = item.second;
            if (sz(v) >= 3)
            {
                ans.push_back({});
                for (int i : v)
                    ans.back().push_back({pts[i].first, pts[i].second});
                sort(all(ans.back()));
                ans.back().resize(unique(all(ans.back())) - ans.back().begin());
            }
        }
        if (ans.empty())
        {
            printf("No lines were found\n");
        }
        else
        {
            printf("The following lines were found:\n");
            sort(all(ans));
            ans.resize(unique(all(ans)) - ans.begin());
            for (auto &v : ans)
            {
                for (auto &p : v)
                    printf("(%4d,%4d)", p.X, p.Y);
                printf("\n");
            }
        }
    }

}