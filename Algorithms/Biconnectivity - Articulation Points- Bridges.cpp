
// easier version but memsets


const int MAX_N = 105;
vector <int> adj[105];
int n, m;
int dfsTime[MAX_N], low[MAX_N], curTime, src, rootChild;
bool isArt[MAX_N];


void clear()
{
    clr(dfsTime, 0);
    clr(isArt, 0);
    rep(i,0,n)
    adj[i].clear();
    curTime = 0;
}



void dfs(int u, int p)
{
    dfsTime[u] = low[u] = ++curTime;
    for (auto v : adj[u])
    {
        if (!dfsTime[v])
        {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (u == src)
                rootChild++;
            else if (dfsTime[u] <= low[v])
                isArt[u] = 1;
        }
        else if (v != p)
            low[u] = min(low[u], dfsTime[v]);
    }
}



for (int i = 0; i < n; ++i)
{
    if (!dfsTime[i])
    {
        rootChild = 0;
        src = i;
        dfs(i, -1);
        isArt[i] = rootChild > 1;
    }
}





const int MAX_N = 105;
vector<int> adj[MAX_N];
int n;
int ans;
int vis[MAX_N], vid; // must memset dfsTime if you don't wanna use visit
int dfsTime[MAX_N], low[MAX_N], curTime, rootChild, src; // set src, if graph is not connected, you need to set src at each time in for loop
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
