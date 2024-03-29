/*
 * Minimum spanning tree code
 * Kruskal algorithm
 * disjoint set data structure
 */

#include <bits/stdc++.h>

using namespace std;

typedef complex<double> point;
#define dp(a, b) ((conj(a) * b).real())
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
const double PI = 3.14159265358979323846;
const double eps = (1e-8);

int dcmp(double x, double y)
{
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

    bool operator==(const edge &e)
    {
        return (e.from == from && e.to == to && e.cost == cost);
    }

} edge;

struct UnionFind // disjoint set data structure
{
    vector<int> parent;
    vector<int> rank; // height of tree i guess?
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
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("facebook.txt", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--)
    {
        int N;
        cin >> N;
        vector<point> town(N);
        rep(i,0,N)
        {
            int x, y;
            cin >> x >> y;
            town[i] = {x, y};
        }
        vector<edge> adj;
        rep(i,0,N)
        {
            rep(j, i+1, N)
            {
                point VEC = town[i] - town[j];
                adj.pb({i, j, dp(VEC, VEC)});
            }
        }
        int M;
        cin >> M;
        vector<edge> tree;
        rep(i,0,M)
        {
            int a, b;
            cin >> a >> b;
            a--;
            b--;
            point VEC = town[a] - town[b];
            tree.pb({a, b, dp(VEC, VEC)});
        }
        UnionFind uf(N);
        rep(i,0,M)
        {
            edge cur = tree[i];
            uf.union_sets(cur.from, cur.to);
        }

        sort(all(adj));
        rep(i,0,sz(adj))
        {
            edge cur = adj[i];
            if (uf.union_sets(cur.from, cur.to))
            {
                tree.pb({cur.from, cur.to, cur.cost});
            }
        }
        if (sz(tree) == M)
            cout << "No new highways need" << endl;
        else
        {
            rep(i,M,sz(tree))
            {
                edge cur = tree[i];
                cout << cur.from + 1 << " " << cur.to + 1 << endl;
            }
        }
        if (T > 0)
            cout << endl;
    }

    return 0;
}