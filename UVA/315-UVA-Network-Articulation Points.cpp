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

const int MAX_N = 105;
vector<int> adj[MAX_N];
int n;
int ans;
int vis[MAX_N], vid;
int dfsTime[MAX_N], low[MAX_N], curTime, rootChild, src;
int isArt[MAX_N];
void clear()
{
    ++vid;
    rep(i,0,n)
        adj[i].clear();
    ans = 0;
    curTime = 0;
    rootChild = 0;
}

void dfs(int u, int p)
{
    vis[u] = vid;
    dfsTime[u] = low[u] = ++curTime;
    for (auto v : adj[u])
    {
        if (vis[v] != vid)
        {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (u != src && dfsTime[u] <= low[v])
                isArt[u] = vid;
            else if (u == src)
                rootChild++;
        }
        else if (v != p)
        {
            low[u] = min(low[u], dfsTime[v]);
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
    while(cin >> n && n)
    {
        cin.ignore();
        clear();
        string in;
        while(getline(cin, in) && in[0] != '0')
        {
            stringstream ss(in);
            int u, v;
            ss >> u;
            --u;
            while(ss >> v)
            {
                --v;
                adj[u].pb(v);
                adj[v].pb(u);
            }
        }
        src = 0;
        dfs(src, -1);
        if (rootChild > 1)
            isArt[src] = vid;
        rep(i,0,n)
            ans += (isArt[i] == vid);
        cout << ans << '\n';
    }
    return 0;
}