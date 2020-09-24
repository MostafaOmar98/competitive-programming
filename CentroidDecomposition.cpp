// usually paired with LCA with sparse table

int cParent[MAX_N], ssize[MAX_N];
bool cut[MAX_N]; // could be int with cid for multiple testcases

int updateSize(int u, int p)
{
    ssize[u] = 1;
    for (int v : adj[u])
        if (!cut[v] && v != p)
            ssize[u] += updateSize(v, u);
    return ssize[u];
}

int findCentroidNode(int u, int p, int total)
{
    for (int v : adj[u])
        if (v != p && !cut[v] && ssize[v] * 2 > total)
            return findCentroidNode(v, u, total);
    return u;
}

int centroid(int u)
{
    int c = findCentroidNode(u, n, updateSize(u, n));
    cut[c] = true;
    for (int v : adj[c])
        if (!cut[v])
            cParent[centroid(v)] = c;
    return c;
}

void mainCentroid(int randomNode = 0)
{
    cParent[centroid(randomNode)] = n;
}

void update(int u)
{
    int cur = u;
    while(cur != n)
    {
        // some stuff
        cur = cParent[cur];
    }
}

void ask(int u)
{
    int  cur = u;
    while(cur != n)
    {
        // some stuff
        cur = cParent[cur];
    }
}

//////////////////////
// can add getInfo
const int MAX_K = 18; // 2^MAX_K > N
int level[MAX_N], info[MAX_N][MAX_K];

void getInfo(int u, int p, int l)
{
    for (int v : adj[u])
        if (v != p && !cut[v])
            getInfo(v, u, l);
}

int centroid(int u, int l)
{
    int c = findCentroidNode(u, n, updateSize(u, n));
    cut[c] = true;
    level[c] = l;
    getInfo(c, n, l, 0);
    for (int v : adj[c])
        if (!cut[v])
            cParent[centroid(v, l + 1)] = c;
    return c;
}
// use info[u][l];
void update(int u)
{
    int cur = u, l = level[u];
    while(cur != n)
    {

        cur = cParent[cur];
        l--;
    }
}

void ask(int u)
{
    int cur = u, l = level[u];
    while(cur != n)
    {

        cur = cParent[cur];
        l--;
    }

}

