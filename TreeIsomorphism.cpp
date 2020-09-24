#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

using namespace std;
using namespace __gnu_pbds;
//typedef tree<
//        pair<long long, int>, // change type
//        null_type,
//        less<pair<long long, int> >, // change type
//        rb_tree_tag,
//        tree_order_statistics_node_update>
//        ordered_set;

template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;


vector<string> vec_splitter(string s) {
    s += ',';
    vector<string> res;
    while(!s.empty()) {
        res.push_back(s.substr(0, s.find(',')));
        s = s.substr(s.find(',') + 1);
    }
    return res;
}
void debug_out(
        vector<string> __attribute__ ((unused)) args,
        __attribute__ ((unused)) int idx,
        __attribute__ ((unused)) int LINE_NUM) { cerr << endl; }
template <typename Head, typename... Tail>
void debug_out(vector<string> args, int idx, int LINE_NUM, Head H, Tail... T) {
    if(idx > 0) cerr << ", "; else cerr << "Line(" << LINE_NUM << ") ";
    stringstream ss; ss << H;
    cerr << args[idx] << " = " << ss.str();
    debug_out(args, idx + 1, LINE_NUM, T...);
}

#ifdef LOCAL
#define debug(...) debug_out(vec_splitter(#__VA_ARGS__), 0, __LINE__, __VA_ARGS__)
#else
#define debug(...) ;
#endif


typedef long long ll;
typedef long double ld;
#define rep(i, start, end) for(int i = start; i < end; ++i)
#define sz(x) (int)((x).size())
#define pb push_back
#define all(x) x.begin(), x.end()
#define clr(d, v) memset(d, v, sizeof(d))
#define pii pair<int, int>
#define X first
#define Y second
//#define debug(x) cerr << #x << " : " << (x) << " "
const double PI = 3.14159265358979323846;
const double eps = (1e-9);
//int isGreater(long double x, long double y)
//{
//    if (abs(x - y) < eps)
//        return 0;
//    if (x > y)
//        return 1;
//    return -1;
//}


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