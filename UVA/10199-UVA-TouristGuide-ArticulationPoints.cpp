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
vector <int> adj[105];
int n, m;
int dfsTime[MAX_N], low[MAX_N], curTime, src, rootChild;
bool isArt[MAX_N];

map<string, int> getID;
map<int, string> getName;
int nameID;

void clear()
{
    clr(dfsTime, 0);
    clr(isArt, 0);
    rep(i,0,n)
        adj[i].clear();
    curTime = 0;
    nameID = 0;
    getID.clear();
    getName.clear();
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
                isArt[u] = 1;
        }
        else if (v != p)
            low[u] = min(low[u], dfsTime[v]);
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
    while (cin >> n && n)
    {
        clear();
        if (tid)
            puts("");
        rep(i,0,n)
        {
            string s;
            cin >> s;
            getID[s] = nameID;
            getName[nameID] = s;
            nameID++;
        }
        cin >> m;
        rep(i,0,m)
        {
            string s, t;
            cin >> s >> t;
            int u = getID[s], v = getID[t];
            adj[u].pb(v);
            adj[v].pb(u);
        }
        for (int i = 0; i < n; ++i)
        {
            if (!dfsTime[i])
            {
                rootChild = 0;
                src = i;
                dfs(i, -1);
                isArt[i] = rootChild > 1;
            }
        }
        vector<string> out;
        rep(i,0,n)
        {
            if (isArt[i])
                out.pb(getName[i]);
        }
        printf("City map #%d: %d camera(s) found\n", ++tid, sz(out));
        sort(all(out));
        for (auto it : out)
            printf("%s\n", it.c_str());
    }
    return 0;
}