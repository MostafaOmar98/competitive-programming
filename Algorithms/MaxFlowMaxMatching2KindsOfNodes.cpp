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

int cows, bulls, m;
const int MAX_N = 2 * 50000 + 2 + 3, MAX_M = 2 *(150000 + 10000) + 5;
int head[MAX_N], to[2 * MAX_M], nxt[2 * MAX_M], cap[2 * MAX_M], ne;

void init()
{
    memset(head, -1,  (cows + bulls + 2) * sizeof(head[0]));
    ne = 0;
}

void addEdge(int f, int t, int c)
{
    nxt[ne] = head[f];
    head[f] = ne;
    to[ne] = t;
    cap[ne] = c;
    ne++;
}

void addAugEdge(int f, int t, int c)
{
    addEdge(f, t, c);
    addEdge(t, f, 0);
}

int src, snk;
int work[MAX_N], dist[MAX_N];

int dfs(int u, int mn)
{
    if (u == snk)
        return mn;
    if (!mn)
        return 0;

    for (int &k = work[u]; ~k; k = nxt[k])
    {
        int v = to[k], c = cap[k];
        if (dist[v] != dist[u] + 1)
            continue;
        int flow = dfs(v, min(mn, c));
        if (flow)
        {
            cap[k] -= flow;
            cap[k ^ 1] += flow;
            return flow;
        }
    }
    return 0;
}

bool bfs()
{
    memset(dist, 0x7F,  (cows + bulls + 2) * sizeof(dist[0]));
    queue<int> q;
    q.push(src);
    dist[src] = 0;
    for (int size = sz(q); !q.empty(); size = sz(q))
    {
        while(size--)
        {
            int u = q.front();
            q.pop();
            for (int k = head[u]; ~k; k = nxt[k])
            {
                int v = to[k];
                if (!cap[k] || dist[v] != 2139062143)
                    continue;
                dist[v] = dist[u] + 1;
                if (v == snk)
                    return 1;
                q.push(v);
            }
        }
    }
    return 0;
}

int dinic()
{
    int ret = 0, flow = 0;
    while(bfs())
    {
        memcpy(work, head, (cows + bulls + 2) * sizeof(head[0]));
        do
        {
            flow = dfs(src, 1e9);
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
    cin >> cows >> bulls >> m;
    init();
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        --u; --v;
        addAugEdge(u, v + cows, 1);
    }

    src = cows + bulls, snk = cows + bulls + 1;
    for (int i = 0; i < cows; ++i)
        addAugEdge(src, i, 1);
    for (int i = cows; i < cows + bulls; ++i)
        addAugEdge(i, snk, 1);

    cout << dinic() << '\n';
    return 0;
}