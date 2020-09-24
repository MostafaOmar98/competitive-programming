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
    long long x, y;

    Point operator*(int scalar) const
    {
        return {x * scalar, y * scalar};
    }

    Point operator+(Point p) const{
        return {x + p.x, y + p.y};
    }
    Point operator-(Point p) const{
        return {x - p.x, y - p.y};
    }
    Point operator/(int scalar) const{
        return {x/scalar, y/scalar};
    }

    bool operator<(const Point &other) const{
        if (x != other.x)
            return x < other.x;
        return y < other.y;
    }

    friend istream& operator>>(istream& in, Point &p) {
        cin >> p.x >> p.y;
        return in;
    }
};

void myMain()
{
    int n;
    cin >> n;
    vector<Point> pt(n);
    Point s = {0, 0};

    set<Point> st;
    rep(i,0,n)
    {
        cin >> pt[i];
        pt[i] = pt[i] * 2;
        s = s + pt[i];
        st.insert(pt[i]);
    }
    if (s.x%n || s.y%n)
    {
        cout << "no\n";
        return;
    }
    s = s / n;
    rep(i,0,n)
    {
        Point to = s * 2 - pt[i];
        if (!st.count(to))
        {
            cout << "no\n";
            return;
        }
    }
    cout << "yes\n";
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