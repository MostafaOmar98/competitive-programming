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
const double eps = (1e-8);int dcmp(long double x, long double y)
{
    if (abs(x - y) < eps)
        return 0;
    if (x > y)
        return 1;
    return -1;
}

const int MAX_N = 102 + 2, MAX_M = 50 * 50 + 2 * 50 + 5;
int head[MAX_N], to[2 * MAX_M], nxt[2 * MAX_M], cap1[2 * MAX_M], cap2[2 * MAX_M], ne;
long double cost1[2 * MAX_M], cost2[2 * MAX_M]; // long long cap?
int* capWork;
long double*costWork;
int  src, snk;
int pie, ice;

void init()
{
    // memset(head, -1, n * sizeof(head[0]));
    memset(head, -1, sizeof(head));
    ne = 0;
}

void addEdge(int f, int t, int c, long double cst)
{
    nxt[ne] = head[f];
    head[f] = ne;
    to[ne] = t;
    cap1[ne] = c;
    cap2[ne] = c;
    cost1[ne] = -cst;
    cost2[ne] = cst;
    ne++;
}

void addAugEdge(int f, int t, int c, long double cst)
{
    addEdge(f, t, c, cst);
    addEdge(t, f, 0, -cst); // bidirected?
}

long double dist[MAX_N];
int parent[MAX_N];
bool inQ[MAX_N];
int flow[MAX_N];
int bellman()
{
    clr(parent, -1);
    fill(dist, dist + MAX_N, (1<<30));
    memset(flow, 0x7F, sizeof(flow));
    queue<int> q;
    q.push(src);
    dist[src] = 0;
    inQ[src] = 1;
    for (int i = 0; i < pie + ice + 2; ++i)
    {
        int size = sz(q);
        while (size--)
        {
            int u = q.front();
            q.pop();
            inQ[u] = 0;
            for (auto k = head[u]; ~k; k = nxt[k])
            {
                int v = to[k], capacity = capWork[k];
                long double cst = costWork[k];
                if (!capacity)
                    continue;
                if (dcmp(dist[v], cst + dist[u]) <= 0)
                    continue;
                dist[v] = dist[u] + cst;
                flow[v] = min(flow[u], capacity);
                parent[v] = k;
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
                for (int u = snk; u != src; u = to[parent[u] ^ 1])
                {
                    int e = parent[u];
                    capWork[e] -= flow[snk];
                    capWork[e ^ 1] += flow[snk];
                }
                return flow[snk];
            }
            return 0;
        }
    }
    return 0;
}

//void augment(int u)
//{
//    if (u == src)
//        return;
//    int e = parent[u];
//    capWork[e] -= flow[snk];
//    capWork[e ^ 1] += flow[snk];
//}

long double minCostMaxFlow() // long long?
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
     * critical question:
     * minCostMaxflow, maximizes flow first then minimizes cost, the objective primarily here is minimizing the cost
     * why does minCost max flow work? is it because it is guaranteed that all pies and ice creams will be used? the max flow will always
     * be the same = summation of pies or summation of ice creams (guaranteed sums are equal)?
     */
    int t = 0;
    while(cin >> pie >> ice && (pie || ice))
    {
        ++t;
        init();
        src = pie + ice, snk = pie + ice + 1;
        for (int i = 0; i < pie; ++i)
        {
            int amount;
            cin >> amount;
            addAugEdge(src, i, amount, 0);
        }
        for (int i = 0; i < ice; ++i)
        {
            int amount;
            cin >> amount;
            addAugEdge(i + pie, snk, amount, 0);
        }
        for (int i = 0; i < pie; ++i)
        {
            for (int j = 0; j < ice; ++j)
            {
                long double cst;
                cin >> cst;
                if (cst > 0)
                    addAugEdge(i, pie + j, 1e9, cst);
            }
        }
        cout << "Problem " << t << ": ";
        costWork = cost2;
        capWork = cap1;
        cout << fixed << setprecision(2) <<  minCostMaxFlow() << " to ";
        costWork = cost1;
        capWork = cap2;
        cout << -1 * minCostMaxFlow() << '\n';
    }
    return 0;
}