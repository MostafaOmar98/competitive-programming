#include<bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp> // Common file
//#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

using namespace std;
//using namespace __gnu_pbds;
//typedef tree<
//        pair<int, int>, // change type
//        null_type,
//        less<pair<int, int> >, // change type
//        rb_tree_tag,
//        tree_order_statistics_node_update>
//        ordered_set;

typedef long long ll;
#define rep(i, start, end) for(int i = start; i < end; ++i)
#define sz(x) (int)(x).size()
#define pb push_back
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define clr(d, v) memset(d, v, sizeof(d))
#define pii pair<int, int>
const double PI = 3.14159265358979323846;
const double eps = (1e-8);

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

char g[505][505];
vector<int> adj[500 * 500 * 2 + 3];
int husband[500 * 500 * 2 + 3];
int vis[500 * 500 * 2 + 3], vid;
int idx[505][505];
int n, m, cntBlack, cntWhite;
void clear()
{
    for (int i = 0; i < cntBlack; ++i)
        adj[i].clear();
    cntBlack = 0;
    cntWhite = 0;
    clr(husband, -1);
    clr(idx, -1);
}

bool foundMatch(int u)
{
    vis[u] = vid;
    for (auto to : adj[u])
    {
        if (husband[to] == -1)
        {
            husband[to] = u;
            return 1;
        }
        else if (vis[husband[to]] != vid && foundMatch(husband[to]))
        {
            husband[to] = u;
            return 1;
        }
    }
    return 0;
}

bool valid(int i, int j)
{
    if (i < 0 || j < 0 || i >= n || j >=m || g[i][j] != 'W')
        return 0;
    return 1;
}

void addNode(int u, int i, int j)
{
    if (!valid(i, j))
        return;
    if (idx[i][j] == -1)
    {
        idx[i][j] = cntWhite;
        adj[u].push_back(cntWhite++);
    }
    else
        adj[u].push_back(idx[i][j]);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
//    freopen("facebook.txt", "w", stdout);
#endif
    int t;
    cin >> t;
    while(t--)
    {
        cin >> n >> m;
        clear();
        int totalWhite = 0;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                cin >> g[i][j];
            }
        }
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (g[i][j] == 'B')
                {
                    addNode(cntBlack, i, j - 1);
                    addNode(cntBlack, i, j + 1);
                    cntBlack++;
                    addNode(cntBlack, i - 1, j);
                    addNode(cntBlack, i + 1, j);
                    cntBlack++;
                }
                else if (g[i][j] == 'W')
                    totalWhite++;

            }
        }
        if (totalWhite != cntBlack)
        {
            cout << "NO\n";
            continue;
        }
        bool ok = 1;
        vector<int> vIndices(cntBlack);
        for (int i = 0; i < cntBlack; ++i)
            vIndices[i] = i;
        shuffle(vIndices.begin(), vIndices.end(), rng);
        for (int i = 0; i < cntBlack; ++i)
        {
            ++vid;
            int cur = vIndices[i];
            if (!foundMatch(cur))
            {
                ok = 0;
                break;
            }
        }
        if (ok)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}