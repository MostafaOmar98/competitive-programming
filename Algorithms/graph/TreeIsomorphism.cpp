vector<int> getCenters(const vector<vector<int> > &adj)
{
    int n = sz(adj);
    vector<int> deg(n);
    queue<int> q;
    rep(i,0,n)
    {
        deg[i] = sz(adj[i]);
        if (deg[i] == 1)
            q.push(i);
    }

    int remNodes = n;
    vector<int> visit(n);
    while(remNodes > 2)
    {
        int s = sz(q);
        while(s--)
        {
            int u = q.front();
            q.pop();
            remNodes--;
            visit[u] = true;

            for (int v : adj[u])
            {
                if (visit[v])
                    continue;
                else
                {
                    --deg[v];
                    if (deg[v] == 1)
                        q.push(v);
                }
            }
        }
    }
    vector<int> ret;
    ret.push_back(q.front());
    q.pop();
    if (!q.empty())
        ret.push_back(q.front());
    return ret;
}
int gid;
map<vector<int>, int> getGID;
int solve(int u, const vector<vector<int> > &adj, int par)
{
    vector<int> sub;
    for (int v : adj[u])
    {
        if (v == par)
            continue;
        sub.push_back(solve(v, adj, u));
    }
    sort(all(sub));
    auto it = getGID.find(sub);
    if (it != getGID.end())
        return it->second;
    return getGID[sub] = gid++;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
//    freopen("AC.txt", "w", stdout);
#endif
    int tc;
    cin >> tc;
    while(tc--)
    {
        int n;
        cin >> n;
        vector<vector<int> > adj1(n);
        getGID.clear();
        gid = 0;
        rep(i,0, n - 1)
        {
            int u, v;
            cin >> u >> v;
            --u; --v;
            adj1[u].pb(v);
            adj1[v].pb(u);
        }
        vector<vector<int> > adj2(n);
        rep(i,0,n - 1)
        {
            int u, v;
            cin >> u >> v;
            --u; --v;
            adj2[u].pb(v);
            adj2[v].pb(u);
        }
        if (n <= 2)
        {
            cout << "YES\n";
            continue;
        }
        vector<int> centers1 = getCenters(adj1), centers2 = getCenters(adj2);
        if (sz(centers1) != sz(centers2))
        {
            cout << "NO\n";
            continue;
        }

        bool ok = false;
        int h1 = solve(centers1[0], adj1, n);
        for (int u : centers2)
            ok |= (h1 == solve(u, adj2, n));
        if (ok)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}