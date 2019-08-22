const int MAX_N = 1002;
vector<pair<int, int> > adj[MAX_N];
int dist[MAX_N];
int n, m;

bool bellman(int src)
{
    clr(dist, 0x7F);
    dist[src] = 0;
    deque<int> dq;
    dq.push_back(src);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0, size = sz(dq); j < size; ++j)
        {
            int u = dq.front();
            dq.pop_front();
            for (auto e : adj[u])
            {
                int v = e.first, c = e.second;
                if (dist[v] > dist[u] + c)
                {
                    dq.push_back(v);
                    dist[v] = dist[u] + c;
                }
            }
        }
        if (!sz(dq))
            break;
        if (i == n - 1 && sz(dq))
            return 1;
    }
    return 0;
}




int dist[202];
bool inQ[202];
int n;

void bellman(int src)
{
    clr(dist, 0x7F);
    clr(inQ, 0);

    queue<int> q;
    q.push(src);
    dist[src] = 0;
    inQ[0] = 1;

    for (int cnt = 0; cnt < n; ++cnt)
    {
        int size = sz(q);
        while(size--)
        {
            int u = q.front();
            inQ[u] = 0;
            q.pop();
            for (auto v : adj[u])
            {
                // relax;
            }
        }
        if (!sz(q))
            break;
        if (cnt == n - 1 && sz(q)); // Negative Cycle, nth iteration and still something got relaxed
    }
}