
#define INF 0x7F7F7F7F
struct edge
{
    int to, cap, cost; // long long cap?
};

const int MAX_N = 200 + 2 + 5; // make sure src and snk are included
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
    for (int i = 0; i < totalNodes; ++i)
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

int augment(int u, int mn) // long long?
{
    if (parent[u] == -1)
        return 1e9; // greater than 1e9?
    auto &e = edgeList[parent[u]], &re = edgeList[parent[u] ^ 1];
    mn = min(e.cap, mn);
    mn = min(mn, augment(re.to, mn));
    e.cap -= mn;
    re.cap += mn;
    return mn;
}

int minCostMaxFlow()
{
    int ret = 0, flow = 0; // long long?
    while(bellman())
    {
        flow = augment(snk, 1e9); // greater than 1e9?
        ret += dist[snk] * flow;
    }
    return ret;
}