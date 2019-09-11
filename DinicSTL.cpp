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

#define pb push_back
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define clr(d, v) memset(d, v, sizeof(d))
#define pii pair<int, int>
const double PI = 3.14159265358979323846;
const double eps = (1e-8);


// in case of node capacity
#define IN(x) ((x)<<1)
#define OUT(x) ((IN((x))) + 1)
#define NODE(x) ((x)/2)
#define NOT(x) ((x)^1)

#define sz(x) (int)(x).size()
struct edge
{
    int to, cap; // long long cap?
};

const int MAX_N = 256 + 3; // make sure src and snk are included
vector<int> adj[MAX_N];
vector<edge> edgeList;
int  totalNodes; // assign totalNodes after clear e7tyaty in case no edges
int src, snk; // assign those

void addAugEdge(int u, int v, int c) // long long cap?
{
    totalNodes = max(totalNodes, max(u, v) + 1);
    adj[u].push_back(sz(edgeList));
    edgeList.push_back({v, c});
    adj[v].push_back(sz(edgeList));
    edgeList.push_back({u, 0}); // c if undirected
}

void clear()
{
    edgeList.clear();
    for (int i = 0; i < totalNodes; ++i)
        adj[i].clear();
    totalNodes = 0;
}


int dist[MAX_N], p[MAX_N];


bool bfs()
{
    memset(dist, -1, totalNodes * sizeof(dist[0]));
    queue<int> q;
    dist[src] = 0;
    q.push(src);
    for (int size = sz(q); !q.empty(); size = sz(q))
    {
        while(size--)
        {
            int u = q.front();
            q.pop();
            for (int i = 0; i < sz(adj[u]); ++i)
            {
                int edgeIdx = adj[u][i];
                int v = edgeList[edgeIdx].to, c = edgeList[edgeIdx].cap; // long long?
                if (dist[v] != -1 || !c)
                    continue;
                dist[v] = dist[u] + 1;
                q.push(v);
                if (v == snk)
                    return 1;
            }
        }
    }
    return 0;
}

int dfs(int u, int mn) // long long? BOTH return value and mn
{
    if (u == snk || !mn)
        return mn;

    for (; p[u] < sz(adj[u]); ++p[u])
    {
        int idx = p[u], edgeIdx = adj[u][idx];
        edge &e = edgeList[edgeIdx];
        edge &re = edgeList[edgeIdx ^ 1];
        int c = e.cap, v = e.to; // long long?
        if (dist[v] != dist[u] + 1 || !c)
            continue;
        int flow = dfs(v, min(mn, c));// long long?
        if (flow)
        {
            e.cap -= flow;
            re.cap += flow;
            return flow;
        }
    }
    return 0;
}

int dinic() // long long?
{
    int ret = 0;
    int flow = 0;
    while(bfs())
    {
        memset(p, 0, totalNodes * sizeof(p[0]));
        do
        {
            flow = dfs(src, 2e9 + 5); // maximum is greater than 2e9 + 5?
            ret += flow;
        }while(flow);
    }
    return ret;
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
        int n;
        cin >> n;
        // src = whatever, snk = whatever + 1, totalNodes = snk + 1
        rep(i,0,n)
        {
            int ii, jj;
            cin >> ii >> jj;
            addAugEdge(ii, 120 + jj, 1e9);
        }
        src = 240, snk = 241;
        for (int i = 0; i < 120; ++i)
            addAugEdge(src, i, 1);
        for (int i = 120; i < 240; ++i)
            addAugEdge(i, snk, 1);
        cout << dinic() << '\n';
    }
    return 0;
}