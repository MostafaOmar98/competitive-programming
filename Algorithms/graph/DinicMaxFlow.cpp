
const int MAX_N = 242 + 2, MAX_M = 120 * 120 + 2 * 244 + 5;
int head[MAX_N], to[2 * MAX_M], nxt[2 * MAX_M], cap[2 * MAX_M], ne; // long long cap?
int  src, snk;
// int n, m;

void init()
{
    // memset(head, -1, n * sizeof(head[0]));
    memset(head, -1, sizeof(head));
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
    addEdge(t, f, 0); // bidirected?
}

int work[MAX_N], dist[MAX_N];

int dfs(int u, int mn) // long long?
{
    if (u == snk || !mn)
        return mn;

    for (int &k = work[u]; ~k; k = nxt[k])
    {
        int v = to[k], c = cap[k];
        if (!c || dist[v] != dist[u] + 1)
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
    memset(dist, 0x7F, sizeof(dist));
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
                int v = to[k], c = cap[k];
                if (dist[v] != 0x7F7F7F7F || !c) // change if long long
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


int dinic() // long long?
{
    int ret = 0, flow = 0;
    while(bfs())
    {
        // memcpy(work, head, n * sizeof(head[0]));
        memcpy(work, head, sizeof(head));
        do{
            flow = dfs(src, 2e9);
            ret += flow;
        }while(flow);
    }
    return ret;
}