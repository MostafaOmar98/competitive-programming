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

    // CAREFUL From here u use 'c' NOT 'u'
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
int level[MAX_N], info[MAX_N][MAX_K]; // info from u to kth parent in centroid tree. for example dist[u][3] is distance from u to 3rd parent in centroid tree

void getInfo(int u, int p, int l)
{
    // save info from u to lth parent
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

/*
 * There are some cases feha ask(u) beyo3od yetla3 3alla el parent nodes we yes2al el subtrees beta3thom, bas enta mesh 3ayez el subtree kolaha
 * 3ayez te-ignore el child ely enta gay menno. 5ally balak lazem te-remove el answer beta3et el child dah. Fa lazem tesave el answer beta3et
 * el child dah bas be values el parent. Here is an example:
 */
ll sum[MAX_N], sumWithParentValue[MAX_N], ans;
int cnt[MAX_N];

int getDist(int u, int v)
{
    return DIST[u][level[v]];
}

ll f(int dist, ll sumDist, int cntNodes)
{
    return 1LL * cntNodes * dist + sumDist;
}

void ask(int orig)
{
    ll ret = f(0, sum[orig], cnt[orig]);
    int cur = cParent[orig], last = orig;
    while(cur != n)
    {
        ret += f(getDist(orig, cur), sum[cur] - sumWithParentValue[last], cnt[cur] - cnt[last]); // bashel answer el child 'last'
        last = cur;
        cur = cParent[cur];
    }
    ans += ret;
    cout << ans << '\n';
}

void addNode(int orig)
{
    int cur = orig;
    while(cur != n)
    {
        sum[cur] += getDist(orig, cur);
        cnt[cur]++;
        int p = cParent[cur];
        if (p != n)
            sumWithParentValue[cur] += getDist(orig, p); // el sum beta3 el subtree of cur bas be value el parent
        cur = p;
    }
}