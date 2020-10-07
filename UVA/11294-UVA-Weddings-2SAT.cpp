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

const int MAX_N = 30 * 4 + 5;
vector<int> adj[MAX_N];
int n, m, totalNodes;


int dfsTime[MAX_N], comp[MAX_N], lowLink[MAX_N], curTime, compNum;
stack<int> st;

int inDeg[MAX_N];
vector<int> compAdj[MAX_N];
void clear()
{
    rep(i,0,totalNodes)
        adj[i].clear();
    rep(i,0,compNum)
        compAdj[i].clear();
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

int compRoot[MAX_N];
vector<int> compList;
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
        compRoot[compNum] = u;
        compList.push_back(compNum);
        ++compNum;
    }
}

void SCC()
{
    curTime = -1;
    compNum = 0;
    compList.clear();
    memset(comp, -1,  sizeof(comp));
    memset(dfsTime, -1, sizeof(dfsTime));
    for (int i = 0; i < totalNodes; ++i)
    {
        if (dfsTime[i] == -1)
            dfs(i);
    }
}


bool TwoSAT()
{
    SCC();
    for (int i = 0; i < n; ++i)
    {
        int w = NODE(i), h = NOT(w);
        if (comp[NODE(w)] == comp[NOT(NODE(w))])
            return false;
        if (comp[NODE(h)] == comp[NOT(NODE(h))])
            return false;
    }
    return true;
}

int ans[MAX_N];
void topSort()
{
    clr(ans, -1);
    for (auto c : compList)
    {
        int root = compRoot[c];
        if (ans[c] == -1)
        {
            ans[c] = 1;
            ans[comp[NOT(root)]] = 0;
        }
    }
}


int process (string &s)
{
    char c = s.back();
    s.pop_back();
    int i = stoi(s.c_str());
    int w = NODE(i), h = NOT(w);
    if (c == 'w')
        return NODE(w);
    else
        return NODE(h);

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
    while(cin >> n >> m && (n || m))
    {
        clear();
        totalNodes = 4 * n;
        // couple cant be on same side
        rep(i,0,n)
        {
            int w = NODE(i), h = NOT(w);
            addXOR(NODE(w), NODE(h));
            if (i == 0)
            {
                addOR(NODE(w), NODE(w));
                addOR(NOT(NODE(h)), NOT(NODE(h)));
            }
        }
        // wife's side will be true
        rep(i,0,m)
        {
            string s1, s2;
            cin >> s1 >> s2;
            int u = process(s1), v = process(s2);
            addOR(u, v);
        }
        if (!TwoSAT())
            cout << "bad luck\n";
        else
        {
            topSort();
            bool first = 1;
            for (int i = 1; i < n; ++i)
            {
                int w = NODE(i), h = NOT(w);
                if (first)
                    first = 0;
                else
                    cout << ' ';
                if (ans[comp[NODE(w)]])
                    cout << i << 'w';
                if (ans[comp[NODE(h)]])
                    cout << i << 'h';
            }
            cout << '\n';
        }

    }
    return 0;
}