
const int MAX_N = 105;
vector<int> adj[MAX_N];
int n;
int ans;
int vis[MAX_N], vid; // must memset dfsTime if you don't wanna use visit
int dfsTime[MAX_N], low[MAX_N], curTime, rootChild, src; // set src
int isArt[MAX_N]; // SET isArt[src] in MAIN!!
void clear()
{
    ++vid;
    rep(i,0,n)
    adj[i].clear();
    ans = 0;
    curTime = 0;
    rootChild = 0;
}

void dfs(int u, int p)
{
    vis[u] = vid;
    dfsTime[u] = low[u] = ++curTime;
    for (auto v : adj[u])
    {
        if (vis[v] != vid)
        {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (u != src && dfsTime[u] <= low[v]) // if bridges then this will be < only and no need to check for src shit
                isArt[u] = vid;
            else if (u == src)
                rootChild++;
        }
        else if (v != p)
        {
            low[u] = min(low[u], dfsTime[v]);
        }
    }
}