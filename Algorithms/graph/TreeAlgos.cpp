const int MAX_N = ?;
vector<int> adj[MAX_N];
int n;

pair<int, int> getCenters()
{
    vector<int> deg(n);
    queue<int> q;
    rep(i,0,n)
    {
        deg[i] = sz(adj[i]);
        if (deg[i] == 1)
            q.push(i);
    }

    int remNodes = n;
    while(remNodes > 2)
    {
        int s = sz(q);
        while(s--)
        {
            int u = q.front();
            q.pop();
            --remNodes;
            for (int v : adj[u])
            {
                if (deg[v] == 1) // either da5lny or base case
                    continue;
                --deg[v];
                if (deg[v] == 1)
                    q.push(v);
            }
        }
    }
    int u = q.front();
    q.pop();
    int v = INT_MAX;
    if (sz(q) == 1)
        v = q.front();
    return make_pair(u, v);
}