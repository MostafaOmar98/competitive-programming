#include <bits/stdc++.h>
using namespace std;

const int S = 550; // MAX_N/sqrt(MAX_Q)
const int MAX_N = 3e5 + 5, MAX_Q = 3e5 + 5; // CHANGE

int n, Q;
// Making an array out of tree stuff
vector<int> adj[MAX_N];
int T; // time, also represents number of values in flat array after dfs is over
int flat[2 * MAX_N]; // flat[i] = value that was in node u with st[u] = i or en[u] = i. You can also modify it to make it hold the node index itself instead of value
int st[MAX_N], en[MAX_N]; // st[u] or en[u] --> index in flat array
int val[MAX_N]; // val[u] --> value stored in node u

// LCA Stuff
const int MAX_K = 19; // 2^MAX_K > MAX_N
int up[MAX_N][MAX_K];
int depth[MAX_N];

// LCA Functions
void init()
{
    depth[n] = -1;
    for (int i = 0; i < MAX_K; ++i)
        up[n][i] = n;
}
void dfs(int u, int p)
{
    st[u] = T;
    flat[T++] = val[u]; // could be 'u' instead of 'val[u]' if you need
    up[u][0] = p;
    depth[u] = depth[p] + 1;
    for (int j = 1; j < MAX_K; ++j)
        up[u][j] = up[up[u][j - 1]][j - 1];

    for (int v : adj[u])
    {
        if (v != p)
            dfs(v, u);
    }

    en[u] = T;
    flat[T++] = val[u]; // could be 'u' instead of 'val[u]' if you need
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

// Query stuff
struct Query{
    int l, r, idx; // l, r indices in the flat array
    int extra; // extra index to check for (index of lca in flat array)

    Query(){}

    Query(int u, int v, int idx) {
        this->idx = idx;
        if (st[u] > st[v])
            swap(u, v);

        int lca = getLCA(u, v);
        if (lca == u)
        {
            l = st[u];
            r = st[v];
            extra = -1;
        }
        else
        {
            l = en[u];
            r = st[v];
            extra = st[lca];
        }
    }

    inline pair<int, int> toPair() const
    {
        return make_pair(l/S, (l/S) & 1 ? -r : r);
    }

    bool operator < (const Query &other) const
    {
        return this->toPair() < other.toPair();
    }
};

Query vq[MAX_Q];
int ans[MAX_Q];

void add(int i)
{
    // add flat[i] logic
}

void rmv(int i)
{
    // remove flat[i] logic
}

void mo()
{
    sort(vq, vq + Q); // modify indices before sorting
    int cl = 0, cr = -1; // 1 based?
    for (int i = 0; i < Q; ++i)
    {
        int l = vq[i].l, r = vq[i].r, idx = vq[i].idx;
        while (cl > l)
            add(--cl);
        while(cr < r)
            add(++cr);
        while (cl < l)
            rmv(cl++);
        while(cr > r)
            rmv(cr--);

        if (vq[i].extra != -1)
            add(vq[i].extra);

        ans[idx] = ; // answer query

        if (vq[i].extra != -1)
            rmv(vq[i].extra);
    }
}

// https://codeforces.com/contest/1479/submission/106942554 for a solved problem
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
#endif
    cin >> n >> Q;
    // input node values
    for (int i = 0; i < n; ++i)
    {
        cin >> val[i];
        --val[i];
    }
    // input tree
    for (int i = 0; i < n - 1; ++i)
    {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // LCA prepare
    init();
    // flat array
    dfs(0, n);


    for (int i = 0; i < Q; ++i)
    {
        int u, v;
        cin >> u >> v;
        --u; --v;
        vq[i] = Query(u, v, i);
    }

    mo();

    for (int i = 0; i < Q; ++i)
        cout << ans[i] << '\n';
}