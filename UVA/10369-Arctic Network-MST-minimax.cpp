#include <bits/stdc++.h>

using namespace std;

typedef complex<int> point;
#define dp(a, b) ((conj(a) * b).real())
#define vec(a, b) (b - a)
#define cp(a, b) ((conj(a) * b).imag())
#define angle(a) (atan2(a.imag(), a.real()))
#define rotate0(a, angle) (a * exp(point(0, angle)))
#define length(a) (hypot(a.imag(), a.real()))
#define rotateAr(a, angle, around) (rotate0(((a) - (around)),(angle)) + around)
#define reflect(a, m) (conj((a)/(m)) * (m))
#define normalize(a) ((a) / length(a));
typedef long long ll;
#define rep(i, start, end) for(int i = start; i < end; ++i)
#define per(i, start, end) for(int i = (int)start-1; i >= end; --i)
#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define clr(d, v) memset(d, v, sizeof(d))
#define pii pair<int, int>
const double PI = 3.14159265358979323846;
const double eps = (1e-6);

int dcmp(double x, double y)
{
    // -1 means left is bigger
    return fabs(x - y) <= eps ? 0 : x > y ? -1 : 1;
}

typedef struct edge
{
    int from, to, cost;

    edge(int from, int to, int cost) : from(from), to(to), cost(cost)
    {
    };

    bool operator<(const edge &e) const
    {
        return cost < e.cost;
    }

    bool operator>(const edge &e) const
    {
        return cost > e.cost;
    }

    bool operator==(const edge &e)
    {
        return (e.from == from && e.to == to && e.cost == cost);
    }

} edge;

struct UnionFind // disjoint set data structure
{
    vector<int> parent;
    vector<int> rank; // height of tree i guess? Only valid when talking about biggest parent, for child nodes it doesn't mean much.
    int forests;

    UnionFind(int n) // initilization, can be same name as struct cuz no typedef
    {
        parent.resize(n);
        rank.resize(n);
        forests = n;
        for (int i = 0; i < n; ++i)
        {
            parent[i] = i;
            rank[i] = 1;
        }
    }

    int find_parent(int x) // finding parent while path compressing
    {
        if (x == parent[x])
            return x;
        return parent[x] = find_parent(parent[x]);
    }

    void link(int x, int y) // linking 2 trees. x & y are both parents
    {
        if (rank[x] > rank[y])
            swap(x, y); // x is the smaller rank

        parent[x] = parent[y]; // el so3'ayra fel kbera

        if (rank[x] == rank[y]) // I don't understand this bit
            rank[y]++;
    }

    bool union_sets(int x, int y)
    {
        // we only care about parents
        x = find_parent(x);
        y = find_parent(y);

        if (x != y)
        {
            link(x, y);
            forests--;
        }

        return x != y;
    }


    // There are more applications like finding connected components dynamically and other shit
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
//    freopen("facebook.txt", "w", stdout);
#endif
    int T;
    cin >> T;
    while(T--)
    {
        int s, p;
        cin >> s >> p;
        vector<edge> q;
        vector<point> a;
        rep(i,0,p)
        {
            int x, y;
            cin >> x >> y;
            a.pb({x, y});
        }
        rep(i,0,sz(a))
        {
            rep(j,i+1,sz(a))
            {
                q.pb({i, j, dp(vec(a[i], a[j]), vec(a[i], a[j]))});
            }
        }
        int cnt = 0;
        sort(all(q));
        int ans;
        UnionFind UF(p);
        rep(i,0,sz(q))
        {
            if (UF.union_sets(q[i].to, q[i].from))
            {
                cnt++;
                if (cnt == p - s)
                {
                    ans = q[i].cost;
                }
            }
        }
        cout << fixed << setprecision(2) << sqrt(1.0 * ans) << '\n';
    }
    return 0;
}