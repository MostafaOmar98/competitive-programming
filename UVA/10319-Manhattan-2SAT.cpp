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

const int MAX_N = 60 * 2 + 5; // assign
vector<int> adj[MAX_N];
int n, m, routes;
int totalNodes;
void clear()
{
    rep(i,0,totalNodes)
        adj[i].clear();

}

#define NODE(x) ((x)<<1)
#define NOT(x) ((x)^1)
#define OG(x) ((x)>>1)

void addImplication(int u, int v)
{
    adj[u].push_back(v);
    adj[NOT(v)].push_back(NOT(u));
}

void addOR(int u, int v)
{
    addImplication(NOT(u), v);
}

void addXOR(int u, int v)
{
    addOR(NOT(u), NOT(v));
    addOR(u, v);
}

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
    for (int i = 0; i < totalNodes; ++i)
    {
        if (dfsTime[i] == -1)
            dfs(i);
    }
}

bool TwoSAT()
{
    SCC();
    for (int i = 0; i < n + m; ++i)
    {
        int u = NODE(i);
        if (comp[u] == comp[NOT(u)])
            return false;
    }
    return true;
}

/*
 * true for s means east
 * true for a means south
 */
void process(int i1, int j1, int i2, int j2)
{
    j1 += n;
    j2 += n;
    if (i1 == i2 && j1 == j2)
        return;
    int s1 = NODE(i1), s2 = NODE(i2), a1 = NODE(j1), a2 = NODE(j2);
    if (j1 > j2)
    {
        s1 = NOT(s1);
        s2 = NOT(s2);
    }
    if (i1 > i2)
    {
        a1 = NOT(a1);
        a2 = NOT(a2);
    }
    if (i1 == i2)
        addOR(s1, s1);
    else if (j1 == j2)
        addOR(a1, a1);
    else
    {
        addOR(s1,s2);
        addOR(s1,a1);
        addOR(s2,a2);
        addOR(a1,a2);
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
    int t;
    cin >> t;
    while(t--)
    {
        clear();
        cin >> n >> m >> routes;
        totalNodes = (n + m) * 2;
        rep(i,0,routes)
        {
            int i1, j1, i2, j2;
            cin >> i1 >> j1 >> i2 >> j2;
            --i1; --j1; --i2; --j2;
            process(i1, j1, i2, j2);
        }
        if (TwoSAT())
            cout << "Yes";
        else
            cout << "No";
        cout << '\n';
    }

    return 0;
}