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
const double eps = (1e-8);
int dcmp(long double x, long double y)
{
    if (abs(x - y) < eps)
        return 0;
    if (x > y)
        return 1;
    return -1;
}

struct edge{
    int to, cap;
    long double cost;
};

const int MAX_N = 50 + 50 + 2 + 4;
vector<int> adj[MAX_N];
vector<edge> edgeList;
int totalNodes, pie, ice, src, snk;
int amount[MAX_N];
void addAugEdge(int u, int v, int cap, long double cst)
{
    totalNodes = max(totalNodes, max(u, v) + 1);
    adj[u].push_back(sz(edgeList));
    edgeList.push_back({v, cap, cst});
    adj[v].push_back(sz(edgeList));
    edgeList.push_back({u, 0, -1 * cst});
}

void clear()
{
    for (int i = 0; i < totalNodes; ++i)
        adj[i].clear();
    edgeList.clear();
    totalNodes = 0;
}

long double dist[MAX_N];
int parent[MAX_N];
bool inQ[MAX_N];
int flow[MAX_N];
int bellman()
{
    fill(dist, dist + totalNodes, 1e9);
    memset(parent, -1, totalNodes * sizeof(parent[0]));
    memset(flow, 0x7F, sizeof(flow));
    clr(inQ, 0);
    queue<int> q;
    q.push(src);
    inQ[src] = 1;
    dist[src] = 0;
    for (int i = 0; i < totalNodes; ++i)
    {
        int size = sz(q);
        while(size--)
        {
            int u = q.front();
            q.pop();
            inQ[u] = 0;
            for (auto edgeIdx : adj[u])
            {
                int v = edgeList[edgeIdx].to, c = edgeList[edgeIdx].cap;
                long double cst = edgeList[edgeIdx].cost;
                if (!c)
                    continue;
                if (dcmp(dist[v], cst + dist[u]) <= 0)
                    continue;
                dist[v] = cst + dist[u];
                parent[v] = edgeIdx;
                flow[v] = min(flow[u], c);
                if (!inQ[v])
                {
                    q.push(v);
                    inQ[v] = 1;
                }
            }
        }
        if (q.empty())
        {
            if (flow[snk] != 0x7F7F7F7F)
            {
                for (int u = snk; u != src; u = edgeList[parent[u] ^ 1].to)
                {
                    int e = parent[u];
                    edgeList[e].cap -= flow[snk];
                    edgeList[e ^ 1].cap += flow[snk];
                }
                return flow[snk];
            }
            return 0;
        }
    }
    return 0;
}

//int augment(int u, int mn)
//{
//    if (parent[u] == -1)
//        return 1e9;
//    int edgeIdx = parent[u];
//    mn = min(mn, edgeList[edgeIdx].cap);
//    mn = min(mn, augment(edgeList[edgeIdx ^ 1].to, mn));
//    edgeList[edgeIdx].cap -= mn;
//    edgeList[edgeIdx ^ 1].cap += mn;
//    return mn;
//}

//long double minCostMaxFlow()
//{
//    long double ret = 0;
//    int flow = 0;
//    while(bellman())
//    {
//        flow = augment(snk, 1e9);
//        ret += flow * dist[snk];
//    }
//    return ret;
//}

long double minCostMaxFlow()
{
    long double ret = 0;
    while(bellman())
    {
        ret += dist[snk] * flow[snk];
//        augment(snk);
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
    /*
     * Mashakel:
     * 2- flow shit
     */
    int t = 0;
    while(cin >> pie >> ice && (pie||ice))
    {
        clear();
        src = pie + ice, snk = src + 1;
        for (int i = 0; i < pie; ++i)
        {
            cin >> amount[i];
            addAugEdge(src, i, amount[i], 0);
        }
        for (int i = 0; i < ice; ++i)
        {
            cin >> amount[i + pie];
            addAugEdge(i + pie, snk, amount[i + pie], 0);
        }
        for (int i = 0; i < pie; ++i)
        {
            for (int j = 0; j < ice; ++j)
            {
                long double cst;
                cin >> cst;
                if (dcmp(cst, -1) == 1)
                    addAugEdge(i, j + pie, 1e9, cst);
            }
        }
        totalNodes = snk + 1;
        vector<edge> edgeListCopy(edgeList);
        cout << "Problem " << ++t << ": ";
        cout << fixed << setprecision(2) << minCostMaxFlow() << " to ";
        swap(edgeList, edgeListCopy); // swaps pointers
        for (int i = 0; i < sz(edgeList); ++i)
            edgeList[i].cost *= -1;
        cout << -1 * minCostMaxFlow() << '\n';
    }
    return 0;
}