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

const int MAX_N = 27;
vector<int> adj[MAX_N];
int n, m;
int dfsTime[MAX_N], low[MAX_N], comp[MAX_N], curTime, compNum;
stack<int> st;
void dfs(int u)
{
    dfsTime[u] = low[u] = ++curTime;
    st.push(u);
    for (auto v : adj[u])
    {
        if (!dfsTime[v])
        {
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
        else if (!comp[v])
        {
            low[u] = min(low[u], dfsTime[v]);
        }
    }
    if (dfsTime[u] == low[u])
    {
        ++compNum;
        while(true)
        {
            int tp = st.top();
            st.pop();
            comp[tp] = compNum;
            if (tp == u)
                break;
        }
    }
}

void SCC()
{
    clr(comp, 0);
    clr(dfsTime, 0);
    curTime = 0;
    compNum = 0;
    for (int i = 0; i < n; ++i)
    {
        if (!comp[i])
            dfs(i);
    }
}

map<string, int> getID;
map<int, string> getName;
int id = 0;

void clear()
{
    getID.clear();
    getName.clear();
    for (int i = 0; i < n; ++i)
        adj[i].clear();
    id = 0;
}

int get(const string &s)
{
    auto it = getID.find(s);
    if (it != getID.end())
        return it->second;
    getID[s] = id;
    getName[id] = s;
    id++;
    return id - 1;
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
    int tid = 0;
    while(cin >> n >> m && (n || m))
    {
        if (tid)
            cout << '\n';
        clear();
        for (int i = 0; i < m; ++i)
        {
            string s, t;
            cin >> s >> t;
            int u, v;
            u = get(s);
            v = get(t);
            adj[u].pb(v);
        }
        SCC();
        vector<vector<string> > ans(compNum + 1);
        cout << "Calling circles for data set " << ++tid << ":\n";
        for (int u = 0; u < n; ++u)
            ans[comp[u]].pb(getName[u]);
        for (int i = 1; i < sz(ans); ++i)
        {
            for (int j = 0; j < sz(ans[i]); ++j)
            {
                cout << ans[i][j];
                if (j != sz(ans[i]) - 1)
                    cout << ", ";
            }
            cout << '\n';
        }
    }
    return 0;
}