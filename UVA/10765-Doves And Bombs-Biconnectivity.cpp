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

const int MAX_N = 10005;
vector <int> adj[MAX_N];
int n;
int dfsTime[MAX_N], low[MAX_N], curTime, src, rootChild;
int biCnt[MAX_N];


void clear()
{
    clr(dfsTime, 0);
    clr(biCnt, 0);
    rep(i,0,n)
        adj[i].clear();
    curTime = 0;
}



void dfs(int u, int p)
{
    dfsTime[u] = low[u] = ++curTime;
    for (auto v : adj[u])
    {
        if (!dfsTime[v])
        {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (u == src)
                rootChild++;
            else if (dfsTime[u] <= low[v])
                biCnt[u]++;
        }
        else if (v != p)
            low[u] = min(low[u], dfsTime[v]);
    }
}

bool cmp(const pair<int, int> &p1, const pair<int, int> &p2)
{
    if (p1.second != p2.second)
        return p1.second > p2.second;
    return p1.first < p2.first;
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
    int ansSize;
    bool first = true;
    while(cin >> n >> ansSize && (n || ansSize))
    {
        clear();
        int u, v;
        while(cin >> u >> v && u != -1)
        {
            adj[u].pb(v);
            adj[v].pb(u);
        }
        src = 0;
        rootChild = 0;
        dfs(src, -1);
        biCnt[src] = rootChild - 1;
        vector<pair<int, int> > ans;
        rep(i,0,n)
        {
            ans.pb({i, biCnt[i] + 1});
        }
        sort(all(ans), cmp);
        rep(i,0,ansSize)
            cout << ans[i].first<< ' ' << ans[i].second << '\n';
        cout << '\n';
    }
    return 0;
}