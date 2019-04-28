vector<pair<int, int> > adj[100005];
int n, m;

struct edge{
    int from, to, cost;
    bool operator < (const edge &e) const{
        return cost > e.cost;
    }
};


int dist[100005];
int dijkstra(int src, int dest)
{
    clr(dist, 0x3F);
    priority_queue<edge> pq;
    pq.push({-1, src, 0});
    dist[src] = 0;

    while(!pq.empty())
    {
        edge e = pq.top();
        int u = e.to, c = e.cost;
        pq.pop();

        if (dist[u] < c)
            continue;

        if (u == dest)
            return c;

        for (auto to : adj[u])
        {
            int v = to.first;
            c = to.second;
            if (dist[v] > dist[u] + c)
            {
                dist[v] = dist[u] + c;
                pq.push({u, v, dist[v]});
            }
        }
    }
    return -1;
}

int main()
{
    return 0;
}