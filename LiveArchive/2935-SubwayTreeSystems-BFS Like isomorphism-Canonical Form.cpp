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
#define X first
#define Y second
#define all(x) x.begin(), x.end()
#define clr(d, v) memset(d, v, sizeof(d))
#define pii pair<int, int>
const double PI = 3.14159265358979323846;
const double eps = (1e-10);
int dcmp(long double x, long double y)
{
    if (abs(x - y) < eps)
        return 0;
    if (x > y)
        return 1;
    return -1;
}
const int MAX_N = 3005;
vector<int> adj[2][MAX_N];
int parent[2][MAX_N];
int N[2];
void constructTree(int i,int u,  const string &s, int cnt, int id)
{
    N[id] = max(cnt, N[id]);
    if (i == sz(s))
    {
        return;
    }
    if (s[i] == '0')
    {
        adj[id][u].pb(cnt);
        adj[id][cnt].pb(u);
        parent[id][cnt] = u;
        constructTree(i + 1, cnt, s, cnt + 1, id);
    }
    else
        constructTree(i + 1, parent[id][u], s, cnt, id);
}

string constructCanonical(vector<string> &v)
{
    sort(all(v));
    string ret = "0";
    rep(i,0,sz(v))
        ret += v[i];
    ret += "1";
    return ret;
}

string getCanonical(int id)
{
    queue<int> q;
    vector<int> deg(N[id]);
    rep(i,0, N[id])
    {
        if (sz(adj[id][i]) <= 1)
            q.push(i);
        else
            deg[i] = sz(adj[id][i]);
    }

    int remNodes = N[id];
    vector<vector<string> > childCanonical(N[id]);
    while(remNodes > 2)
    {
        int size = sz(q);
        while(size--)
        {
            int leaf = q.front();
            q.pop();

            string leafCanonical = constructCanonical(childCanonical[leaf]);
            for (auto v : adj[id][leaf])
            {
                childCanonical[v].push_back(leafCanonical);
                --deg[v];
                if (deg[v] == 1)
                    q.push(v);
            }
            remNodes--;
        }
    }
    if (remNodes == 1)
    {
        int u = q.front();
        q.pop();
        return constructCanonical(childCanonical[u]);
    }
    else
    {
        int u = q.front();
        q.pop();
        int v = q.front();
        q.pop();

        string cu = constructCanonical(childCanonical[u]), cv = constructCanonical(childCanonical[v]);
        childCanonical[u].push_back(cv);
        childCanonical[v].push_back(cu);

        return min(constructCanonical(childCanonical[u]), constructCanonical(childCanonical[v]));

    }

}

string s[2];
void clear()
{
    rep(i,0,2)
    {
        rep(j,0,sz(s[i]))
            adj[i][j].clear();
    }
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
        clear();

        rep(i,0,2)
            cin >> s[i];

        constructTree(0, 0, s[0], 1, 0);
        constructTree(0, 0, s[1], 1, 1);

        string canonical[2];
        rep(i,0,2)
        {
            canonical[i] = getCanonical(i);
//            cout << canonical[i] << '\n';
        }
        if (canonical[0] == canonical[1])
            cout << "same\n";
        else
            cout << "different\n";
    }
    return 0;
}