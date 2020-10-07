#include<bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp> // Common file
//#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

using namespace std;
//using namespace __gnu_pbds;
//typedef tree<
//        pair<int, int>, // change type
//        null_type,
//        less<pair<int, int> >, // change type
//        rb_tree_tag,
//        tree_order_statistics_node_update>
//        ordered_set;

typedef long long ll;
#define rep(i, start, end) for(int i = start; i < end; ++i)
#define sz(x) (int)(x).size()
#define pb push_back
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define clr(d, v) memset(d, v, sizeof(d))
#define pii pair<int, int>
const double PI = 3.14159265358979323846;
const double eps = (1e-7);
int dcmp(long double x, long double y)
{
    if (abs(x - y) < eps)
        return 0;
    if (x > y)
        return 1;
    return -1;
}

const int MAX_N = 1005;
vector<int> adj[MAX_N];
int n, m;
int vis[MAX_N], vid; // must memset dfsTime if you don't wanna use visit
int dfsTime[MAX_N], low[MAX_N], curTime;
vector<pair<int, int> > ans;
void clear()
{
    ++vid;
    ans.clear();
    rep(i,0,n)
        adj[i].clear();
    curTime = 0;
}

void dfs(int u, int p)
{
    vis[u] = vid;
    dfsTime[u] = low[u] = ++curTime;
    for (auto v : adj[u])
    {

        if (vis[v] != vid)
        {
            ans.pb({u, v});
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (dfsTime[u] < low[v]) // if bridges then this will be < only and no need to check for src shit
                ans.pb({v, u});
        }
        else if (v != p)
        {
            low[u] = min(low[u], dfsTime[v]);
            if (dfsTime[v] < dfsTime[u]) // backEdge
                ans.pb({u, v});
        }
    }
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
    int tid = 0;
    while(cin >> n >> m && (n || m))
    {
        clear();
        while(m--)
        {
            int u, v;
            cin >> u >> v;
            --u; --v;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        dfs(0, -1);
//        cout << sz(ans) << '\n';
        cout << ++tid << "\n\n";
        for (auto item : ans)
            cout << item.first + 1 << ' ' << item.second + 1 << '\n';
        cout << "#\n";
    }
    return 0;
}