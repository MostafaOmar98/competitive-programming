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
const double eps = (1e-7);
int dcmp(long double x, long double y)
{
    if (abs(x - y) < eps)
        return 0;
    if (x > y)
        return 1;
    return -1;
}
int n, k;
vector<ll> a;
ll mem[207][207][32];
ll dist[207][207];

struct outline{
    int depotIdx, l, r;
};
vector<outline> out;

void clear()
{
    a.clear();
    a.resize(n);
    clr(mem, -1);
    clr(dist, 0);
    out.clear();
}

void preDist() // TODO find quick way to calc this
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = i; j < n; ++j)
        {
            for (int v = i; v <= j; ++v)
                dist[i][j] += a[j] - a[v];
        }
    }
}

ll solve(int i, int lastNonCovered, int remK)
{
    if (i == n)
    {
        if (lastNonCovered != n)
            return (1LL<<55);
        return 0;
    }
    ll &ret = mem[i][lastNonCovered][remK];
    if (~ret)
        return ret;
    ret = solve(i + 1, lastNonCovered, remK);
    if(remK)
    {
        for (int en = i; en < n; ++en)
        {
            ll temp = dist[lastNonCovered][i] + dist[i][en];
            ret = min(ret, temp + solve(en + 1, en + 1, remK - 1));
        }
    }
    return ret;
}

void build(int i, int lastNonCovered, int remK)
{
    if (i == n)
        return;
    ll ret = mem[i][lastNonCovered][remK];
    if (ret == solve(i + 1, lastNonCovered, remK))
    {
        build(i + 1, lastNonCovered, remK);
        return;
    }
    if(remK)
    {
        for (int en = i; en < n; ++en)
        {
            ll temp = dist[lastNonCovered][i] + dist[i][en];
            if (ret == temp + solve(en + 1, en + 1, remK - 1))
            {
                out.pb({i, lastNonCovered, en});
                build(en + 1, en + 1, remK - 1);
                return;
            }
        }
    }
    return;

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("facebook.txt", "w", stdout);
#endif
    int tid = 0;
    while(cin >> n >> k && (n || k))
    {
        clear();
        rep(i,0,n)
            cin >> a[i];
        preDist();
        solve(0,0,k);
        build(0,0,k);
        cout << "Chain " << ++tid << '\n';
        int cnt = 0;
        for(auto &item : out)
        {
            if (item.l != item.r)
                cout << "Depot " << ++cnt << " at restaurant " << item.depotIdx + 1 << " serves restaurants " << item.l + 1 << " to " << item.r + 1 << '\n';
            else
                cout << "Depot " << ++cnt << " at restaurant " << item.depotIdx + 1 << " serves restaurant " << item.l + 1 <<'\n';
        }
        cout << "Total distance sum = " << solve(0,0,k) << "\n\n";
    }
    return 0;
}