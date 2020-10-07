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

#define INF 0x7F7F7F7F
struct edge
{
    int to, cap, cost; // long long cap?
};
int m, n;

const int MAX_N = 60 + 2 + 10; // make sure src and snk are included
vector<int> adj[MAX_N];
vector<edge> edgeList;
int  totalNodes; // assign this too
int src, snk; // assign those

void addAugEdge(int u, int v, int c, int cst) // long long cap?
{
    totalNodes = max(totalNodes, max(u, v) + 1);
    adj[u].push_back(sz(edgeList));
    edgeList.push_back({v, c, cst});
    adj[v].push_back(sz(edgeList));
    edgeList.push_back({u, 0, -1 * cst}); // c if undirected, if there is cost -1 * cost
}

void clear()
{
    edgeList.clear();
    for (int i = 0; i < MAX_N; ++i)
        adj[i].clear();
    totalNodes = 0;
}


int dist[MAX_N], parent[MAX_N]; // long long dist?
bool inQ[MAX_N];
bool bellman()
{
    memset(dist, 0x7F, totalNodes * sizeof(dist[0]));
    memset(parent, -1, totalNodes * sizeof(parent[0]));
    queue<int> q;
    q.push(src);
    dist[src] = 0;
    inQ[src] = 1;

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
                auto &e = edgeList[edgeIdx];
                int v = e.to, capacity = e.cap, cst = e.cost;
                if (!capacity || dist[v] <= dist[u] + cst) // dcmp for doubles?
                    continue;
                dist[v] = dist[u] + cst;
                parent[v] = edgeIdx;
                if (!inQ[v])
                {
                    q.push(v);
                    inQ[v] = 1;
                }
            }
        }
        if (!q.size())
            break;
    }
    return (dist[snk] != INF); // INF? 0x7F7F7F for int, 8 bytes for long long

}

int augment(int u, int mn)
{
    if (parent[u] == -1)
    {
//        cout << u << ' ';
        return 1e9; // greater than 1e9?
    }
    auto &e = edgeList[parent[u]], &re = edgeList[parent[u] ^ 1];
    mn = min(e.cap, mn);
    mn = min(mn, augment(re.to, mn));
//    cout << u << ' ';
    e.cap -= mn;
    re.cap += mn;
    return mn;
}

void update()
{
    auto &e = edgeList[parent[snk]], &re = edgeList[parent[snk] ^ 1];
    int memory = re.to;
    for (int i = 0; i < n; ++i)
    {
        for (int edgeIdx : adj[i])
        {
            auto &newE = edgeList[edgeIdx], &newRE = edgeList[edgeIdx ^ 1];
            if (newE.to == memory)
            {
                newE.cost += dist[memory];
            }
        }
    }
}

int minCostMaxFlow()
{
    int ret = 0, flow = 0; // long long?
    while(bellman())
    {
        flow = augment(snk, 1e9); // greater than 1e9?
        update();
        ret += dist[snk] * flow;
//        cout << ' ' << dist[snk] <<  '\n';
    }
    return ret;
}

/*
 * IDEA:
 * Match each program to some memory region, memory region can handle many programs
 * If it was time taken and not turnaround time, this would've been correct
 * if P(i1) goes to R(j1) with time T(i1) and P(i2) goes to R(j2) with T(i2) so depends on the order
 * your total turnaround time would either be T(i1) + T(i1) + T(i2) or T(i2) + T(i2) + T(i2)
 * i'm adding the cost to all edges when i match bas when i add the negative cost i get negative cycle so my idea seems wrong and
 * it gives TLE on uva i think it's infinite loop
 */


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
//    freopen("facebook.txt", "w", stdout);
#endif
    int tid = 0;
    while(cin >> m >> n && (n || m))
    {
        if (tid)
            cout << '\n';
        src = n + m, snk = src + 1, totalNodes = snk + 1;
        clear();
        vector<int> memSpace(m);
        rep(i,0,m)
        {
            cin >> memSpace[i];
            addAugEdge(i + n, snk, 1e9, 0);
        }
        vector<vector<int> > s(n), t(n);
        rep(i,0,n)
        {
            int k;
            cin >> k;
            s[i].resize(k), t[i].resize(k);
            rep(j,0,k)
                cin >> s[i][j] >> t[i][j];
            addAugEdge(src, i, 1, 0);
        }

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                int idx = upper_bound(s[j].begin(), s[j].end(), memSpace[i]) - s[j].begin();
                if (idx == 0)
                    continue;
                --idx;
                addAugEdge(j, i + n, 1, t[j][idx]);
            }
        }
        cout << "Case " << ++tid << '\n';
        cout << fixed << setprecision(2) << "Average turnaround time = " <<1.0 * minCostMaxFlow()/n << '\n';
        vector<vector<pair<int, int> > > memOutput(m); // for each memory it has vector of pairs (time taken, app)
        vector<pair<int, int> > appOutput(n);
        vector<int> appRegion(n);
        for (int i = 0; i < n; ++i)
        {
            for (int edgeIdx : adj[i])
            {
                auto &e = edgeList[edgeIdx], &re = edgeList[edgeIdx ^ 1];
                if (!e.cap)
                {
                    int memory = e.to - n;
                    int idx = upper_bound(s[i].begin(), s[i].end(), memSpace[memory]) - s[i].begin();
                    assert(idx > 0);
                    --idx;
                    memOutput[memory].push_back({t[i][idx], i});
                }
            }
        }
        for (int i = 0; i < m; ++i)
        {
            sort(all(memOutput[i]));
            int a = 0;
            for (int j = 0; j < sz(memOutput[i]); ++j)
            {
                int app = memOutput[i][j].second, tm = memOutput[i][j].first;
                appOutput[app] = {a, a + tm};
                appRegion[app] = i;
                a += tm;
            }
        }
        for (int i = 0; i < n; ++i)
        {

            cout << "Program " << i + 1 <<  " runs in region " << appRegion[i] + 1 << " from " << appOutput[i].first << " to " << appOutput[i].second << '\n';
        }
    }

    return 0;
}