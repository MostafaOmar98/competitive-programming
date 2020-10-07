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
#define INF 0x7F7F7F7F // change to 8 bytes if long long
const double PI = 3.14159265358979323846;
const double eps = (1e-8);
int dcmp(long double x, long double y)
{
    if (abs(x - y) < eps)
        return 0;
    if (x > y)
        return 1;
    return -1;
}
struct edge
{
    int to;
    long long cap; // long long cap?
};

const int MAX_N = 100 + 2 + 5; // make sure src and snk are included
vector<int> adj[MAX_N];
vector<edge> edgeList;
long long nodeCap[MAX_N];
int  totalNodes; // assign totalNodes after clear e7tyaty in case no edges
int src, snk; // assign those
int n;
void addAugEdge(int u, int v, long long c) // long long cap?
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
            int u = q.back();
            q.pop();
            for (int i = 0; i < sz(adj[u]); ++i)
            {
                int edgeIdx = adj[u][i];
                int v = edgeList[edgeIdx].to;
                long long c = min(edgeList[edgeIdx].cap, nodeCap[v]);
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

long long dfs(int u, long long mn) // long long? BOTH return value and mn
{
    if (u == snk || !mn)
        return mn;

    for (; p[u] < sz(adj[u]); ++p[u])
    {
        int idx = p[u], edgeIdx = adj[u][idx];
        edge &e = edgeList[edgeIdx];
        edge &re = edgeList[edgeIdx ^ 1];
        int v = e.to;
        long long c = min(e.cap, nodeCap[v]);
        if (dist[v] != dist[u] + 1 || !c)
            continue;
        long long flow = dfs(v, min(mn, c));
        if (flow)
        {
            e.cap -= flow;
            re.cap += flow;
            if (edgeIdx&1)
                nodeCap[v] += flow;
            else
                nodeCap[v] -= flow;
            return flow;
        }
    }
    return 0;
}

long long dinic() // long long?
{
    long long ret = 0;
    long long flow = 0;
    while(bfs())
    {
        memset(p, 0, totalNodes * sizeof(p[0]));
        do
        {
            flow = dfs(src, (1LL<<50)); // maximum is greater than 2e9 + 5?
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
    while (cin >> n)
    {
        for (int i = 0; i < n; ++i)
            cin >> nodeCap[i];
        int m;
        cin >> m;
        for (int i = 0; i < m; ++i)
        {
            int u, v, c;
            cin >> u >> v  >> c;
            --u; --v;
            addAugEdge(u, v, c);
        }
        src = n, snk = src + 1, totalNodes = snk + 1;
        nodeCap[src] = (1LL<<50), nodeCap[snk] = (1LL<<50);
        int b, d;
        cin >> b >> d;
        for (int i = 0; i < b; ++i)
        {
            int u;
            cin >> u;
            --u;
            addAugEdge(src, u, (1LL<<50));
        }
        for (int i = 0; i < d; ++i)
        {
            int u;
            cin >> u;
            --u;
            addAugEdge(u, snk, (1LL<<50));
        }
        cout << dinic() << '\n';
    }
    return 0;
}