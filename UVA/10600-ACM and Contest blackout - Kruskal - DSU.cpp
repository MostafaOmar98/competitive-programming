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
        int N, M;
        cin >> N >> M;
        vector<edge> q;
        rep(i, 0, M)
        {
            int from, to, cost;
            cin >> from >> to >> cost;
            from--;
            to--;
            edge e(from, to, cost);
            q.pb(e);
        }
        sort(all(q));
        UnionFind uf(N);
        vector<edge> tree1;
        int minCost1 = 0;
        rep(i, 0, sz(q))
        {
            edge cur = q[i];
            if (uf.union_sets(cur.from, cur.to))
            {
                minCost1 += cur.cost;
                tree1.pb(cur);
            }
        }
        int minCost2 = INT_MAX;
        rep(i, 0, sz(tree1))
        {
            edge cant = tree1[i];
            int tempCost = 0;
            UnionFind uf2(N);
            vector<edge> tree2;
            rep(j, 0, sz(q))
            {
                edge cur = q[j];
                if (cur == cant)
                    continue;

                if (uf2.union_sets(cur.from, cur.to))
                {
                    tempCost += cur.cost;
                    tree2.pb(cur);
                }
            }
            if (sz(tree2) == N-1)
                minCost2 = min(minCost2, tempCost);
        }
        cout << minCost1 << " " << minCost2 << endl;
    }

    return 0;
}