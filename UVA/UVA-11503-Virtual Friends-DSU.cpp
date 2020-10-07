/*
 * I prefer keeping rank and number of nodes in component different vectors
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
    vector<int> compN;
    vector<int> rank; // height of tree i guess?
    int forests;

    UnionFind(int n) // initilization, can be same name as struct cuz no typedef
    {
        parent.resize(n);
        rank.resize(n);
        compN.resize(n);
        forests = n;
        for (int i = 0; i < n; ++i)
        {
            parent[i] = i;
            rank[i] = 1;
            compN[i] = 1;
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
        if (rank[x] > rank[y])// x is the smaller rank
            swap(x, y);

        compN[y] += compN[x];
        parent[x] = parent[y]; // el so3'ayra fel kbera

        if (rank[x] == rank[y]) // I don't understand this bit
            rank[y]++;
    }

    int union_sets(int x, int y)
    {
        x = find_parent(x);
        y = find_parent(y);

        if (x != y)
        {
            link(x, y);
            forests--;
        }

        return max(compN[x], compN[y]);
    }
    // There are more applications like finding connected components dynamically and other shit
};
void hashFunc(string const &s1, map<string, int> &hash, int &hashID, UnionFind &uf)
{
    if (hash[s1] == 0)
    {
        hash[s1] = hashID;
        uf.parent.pb(hashID);
        uf.rank.pb(1);
        uf.compN.pb(1);
        hashID++;
    }
}
int main()
{
    ios_base::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
//    freopen("facebook.txt", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--)
    {
        int N;
        cin >> N;
        int hashID = 1;
        map<string, int> hash;
        UnionFind uf(1);
        while (N--)
        {
            string s1, s2;
            cin >> s1 >> s2;
            hashFunc(s1, hash, hashID, uf);
            hashFunc(s2, hash, hashID, uf);
            cout << uf.union_sets(hash[s1], hash[s2]) << endl;
        }
    }

    return 0;
}