const int MAX_N = 1002;
vector<pair<int, int> > adj[MAX_N];
int dist[MAX_N];
int n, m;

int bellman(int src)
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
            q.pop();
            for (int v = 0; v < n; ++v)
            {
                for (auto e : adj[u])
                {
                    int v = e.first, c = e.second;
                    if (dist[v] > dist[u] + c)
                    {
                        dist[v] = dist[u] + c;
                        if (!inQ[v])
                        {
                            q.push(v);
                            inQ[v] = 1;
                        }
                    }
                }
            }
        }
        if (!sz(q))
            break;
        if (cnt == n - 1 && sz(q)); // Negative Cycle, nth iteration and still something got relaxed
    }
}