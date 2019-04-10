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
