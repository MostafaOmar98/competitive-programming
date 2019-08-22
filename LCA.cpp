#include<bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp> // Common file
//#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

using namespace std;
//using namespace __gnu_pbds;
//typedef tree<
//        pair<long long, int>, // change type
//        null_type,
//        less<pair<long long, int> >, // change type
//        rb_tree_tag,
//        tree_order_statistics_node_update>
//        ordered_set;

typedef long long ll;
#define rep(i, start, end) for(int i = start; i < end; ++i)
#define sz(x) (int)(x).size()
#define pb push_back
#define row first
#define col second
#define all(x) x.begin(), x.end()
#define clr(d, v) memset(d, v, sizeof(d))
#define pii pair<int, int>
const double PI = 3.14159265358979323846;
const double eps = (1e-4);
int dcmp(long double x, long double y)
{
    if (abs(x - y) < eps)
        return 0;
    if (x > y)
        return 1;
    return -1;
}
const int MAX_N = 1005, MAX_K = 15;
int level[MAX_N], first[MAX_N];
vector<int> eulerGraph;
vector<int> adj[MAX_N];

void dfs(int u, int p = -1, int h = 0)
{
    first[u] = sz(eulerGraph);
    eulerGraph.pb(u);
    level[u] = h;

    for (int v : adj[u])
    {
        if (v != p)
        {
            dfs(v, u, h + 1);
            eulerGraph.pb(u);
        }
    }

}

pair<int, int> table[2 * MAX_N][MAX_K];
int Log2[2 * MAX_N];
void preTable()
{
    dfs(0);
    rep(i,0,sz(eulerGraph))
        table[i][0] = {level[eulerGraph[i]], eulerGraph[i]};

    for (int j = 1; (1<<j) <= sz(eulerGraph); ++j)
        for (int i = 0; i + (1<<j) - 1 < sz(eulerGraph); ++i)
            table[i][j] = min(table[i][j - 1], table[i + (1<<(j - 1))][j -1]);

}

int getMin(int l, int r)
{
    int j = Log2[r - l + 1];
    return min(table[l][j], table[r - (1<<j) + 1][j]).second;
}

int getLCA(int u, int v)
{
    if (first[u] > first[v])
        swap(u, v);
    return getMin(first[u], first[v]);
}

void clear(int n)
{
    rep(i,0,n)
        adj[i].clear();
    eulerGraph.clear();
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
//    freopen("facebook.txt", "w", stdout);
#endif
    int tc;
    cin >> tc;
    Log2[1] = 0;
    for (int i = 2; i < 2 * MAX_N; ++i)
        Log2[i] = Log2[i/2] + 1;
    for (int tid = 1; tid <= tc; ++tid)
    {
        int n;
        cin >> n;
        clear(n);
        rep(i,0,n)
        {
            int k;
            cin >> k;
            while(k--)
            {
                int v;
                cin >> v;
                --v;
                adj[i].pb(v);
                adj[v].pb(i);
            }
        }
        preTable();
        cout << "Case " << tid << ":\n";
        int q;
        cin >> q;
        while(q--)
        {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            cout << getLCA(u, v) + 1 << '\n';
        }
    }
    return 0;
}