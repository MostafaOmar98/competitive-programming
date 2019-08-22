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


const int MAX_N = 2005 * 2; // assign
vector<int> adj[MAX_N];
int n, m, totalNodes; // CAREFUL overwriting in main
// for printing valid assignment
vector<int> compList;
int compRoot[MAX_N];
void clear()
{
    rep(i,0,totalNodes)
        adj[i].clear();

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
        compList.push_back(compNum);
        compRoot[compNum] = u;
        ++compNum;
    }
}

void SCC()
{
    curTime = -1;
    compNum = 0;
    memset(comp, -1, totalNodes * sizeof(comp[0]));
    memset(dfsTime, -1, totalNodes * sizeof(dfsTime[0]));
    compList.clear();
    // in the end compNum should have number of components
    // components in [0, compNum - 1)
    for (int i = 0; i < totalNodes; ++i) // totalNodes correct?
    {
        if (dfsTime[i] == -1)
            dfs(i);
    }
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
void addXNOR(int u, int v)
{
    addOR(u, NOT(v));
    addOR(NOT(u), v);
}


bool TwoSAT()
{
    SCC();
    for (int i = 0; i < n; ++i) // Loop over n??
    {
        int u = NODE(i);
        if (comp[u] == comp[NOT(u)])
            return false;
    }
    return true;
}

int ans[MAX_N]; // ans[c] means answer for comp c. to get answer for NODE(i) do ans[comp[NODE(i)]]
void topSort()
{
    clr(ans, -1);
    for (auto c : compList) // compList contains the component nodes in reverse topological order
    {
        int root = compRoot[c];
        if (ans[c] == -1)
        {
            ans[c] = 1;
            ans[comp[NOT(root)]] = 0;
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
    int t;
    cin >> t;
    for (int tid = 1; tid <= t; ++tid)
    {
        clear();
        cin >> n >> m;
        totalNodes = 2 * n;
        rep(i,0,m)
        {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            addXOR(NODE(u), NODE(v));
        }
        cout << "Scenario #" << tid << ":\n";
        if (TwoSAT())
            cout << "No suspicious bugs found!\n";
        else
            cout << "Suspicious bugs found!\n";
    }
    return 0;
}