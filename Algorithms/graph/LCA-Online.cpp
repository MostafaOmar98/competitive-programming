void init()
{
    depth[n] = -1;
    for (int i = 0; i < MAX_K; ++i)
        up[n][i] = n;
}

void update(int x)
{
    adj[up[x][0]].push_back(x);
    adj[x].push_back(up[x][0]);
    depth[x] = depth[up[x][0]] + 1;
    for (int j = 1; j < MAX_K; ++j)
        up[x][j] = up[up[x][j - 1]][j - 1];
}

int getLCA(int a, int b)
{
    if (a == b)
        return a;
    if (depth[a] < depth[b]) // a is deeper than b
        swap(a, b);
    // putting a, b on same depth
    for (int j = MAX_K - 1; j >= 0; --j)
    {
        int nxt = up[a][j];
        if (depth[nxt] >= depth[b])
            a = nxt;
    }
    // b is ancestor of a handling
    if (a == b)
        return a;
    // jumping them up until they are both children of LCA
    for (int j = MAX_K - 1; j >= 0; --j)
    {
        int nextA = up[a][j], nextB = up[b][j];
        if (nextA != nextB)
        {
            a = nextA;
            b = nextB;
        }
    }
    return up[a][0];
}