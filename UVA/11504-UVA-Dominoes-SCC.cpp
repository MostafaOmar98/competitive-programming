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


const int MAX_N = 100005 + 3; // assign
vector<int> adj[MAX_N];
int n, m, totalNodes; // CAREFUL overwriting in main
// for printing valid assignment
int comp[MAX_N], dfsTime[MAX_N], lowLink[MAX_N], curTime, compNum;
stack<int> st;

void dfs(int u)
{
    ++curTime;
    dfsTime[u] = lowLink[u] = curTime;
    st.push(u);
    for (auto v : adj[u])
    {
        if (comp[v] != -1) // black node
            continue;
        if (dfsTime[v] == -1) // white node
        {
            dfs(v);
            lowLink[u] = min(lowLink[u], lowLink[v]);
        }
        else // grey node
            lowLink[u] = min(lowLink[u], dfsTime[v]);
    }
    if (lowLink[u] == dfsTime[u]) // component head
    {
        while(!st.empty())
        {
            int cur = st.top();
            st.pop();
            comp[cur] = compNum;
            if (cur == u)
                break;
        }
        ++compNum;
    }
}

void SCC()
{
    curTime = -1;
    compNum = 0;
    memset(comp, -1, totalNodes * sizeof(comp[0]));
    memset(dfsTime, -1, totalNodes * sizeof(dfsTime[0]));
    // in the end compNum should have number of components
    // components in [0, compNum - 1)
    for (int i = 0; i < totalNodes; ++i) // totalNodes correct?
    {
        if (dfsTime[i] == -1)
            dfs(i);
    }
}

void clear()
{
    rep(i,0,totalNodes)
        adj[i].clear();
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("facebook.txt", "w", stdout);
#endif
    int t;
    cin >> t;
    while(t--)
    {
        cin >> n >> m;
        totalNodes = n;
        clear();
        vector<pair<int, int> > edgeList;
        while(m--)
        {
            int u, v;
            cin >> u >> v;
            adj[--u].pb(--v);
            edgeList.pb({u, v});
        }
        SCC();
        vector<int> inDeg(compNum);
        for (auto &e : edgeList)
        {
            int u = e.first, v = e.second;
            if (comp[u] != comp[v])
                inDeg[comp[v]]++;
        }
        int ans = 0;
        rep(i,0,compNum)
            ans += inDeg[i] == 0;
        cout << ans << '\n';
    }
    return 0;
}