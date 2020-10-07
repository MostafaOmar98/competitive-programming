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

int n, m;
int g[12][102];
int mem[12][102];

int mod(int i)
{
    if (i >= n)
        i -= n;
    else if (i < 0)
        i += n;
    return i;
}

int solve(int i, int j)
{
    if (j == m)
        return 0;
    int &ret = mem[i][j];
    if (~ret)
        return ret;
    ret = g[i][j] + solve(mod(i - 1), j + 1);
    ret = min(ret, g[i][j] + solve(i, j + 1));
    ret = min(ret, g[i][j] + solve(mod(i + 1), j + 1));
    return ret;
}

vector<int> out;
void build(int i, int j)
{
    if (j == m)
        return;
    int &ret = mem[i][j];
    vector<pair<int, int> > v;
    v.pb({g[i][j] + solve(mod(i - 1), j + 1), mod(i - 1)});
    v.pb({g[i][j] + solve(i, j + 1), i});
    v.pb({g[i][j] + solve(mod(i + 1), j + 1), mod(i + 1)});
    sort(all(v));
    out.pb(i);
    build(v[0].second, j + 1);
    return;

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
    while(cin >> n >> m)
    {
        clr(mem, -1);
        out.clear();
        rep(i,0,n)
        {
            rep(j,0,m)
                cin >> g[i][j];
        }
        int ans = INT_MAX;
        for (int i = 0; i < n; ++i)
            ans = min(ans, solve(i, 0));
        for (int i = 0; i < n; ++i)
        {
            if (ans == solve(i, 0))
            {
                build(i, 0);
                break;
            }
        }
        for (int i = 0; i < sz(out); ++i)
        {
            cout << out[i] + 1;
            if (i != sz(out) - 1)
                cout << ' ';
        }
        cout << '\n' << ans << '\n';
    }
    return 0;
}