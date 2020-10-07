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


int MOD = 1000000007;
ll mod(ll a, ll m = MOD)
{
    return (a%m + m)%m;
}

ll mult(ll a, ll b, ll m = MOD)
{
    return mod(mod(a, m) * mod(b, m), m);
}

ll add(ll a, ll b, ll m = MOD)
{
    return mod(mod(a, m) + mod(b, m), m);
}

#define Matrix vector<vector<ll> >

Matrix makeMatrix(int r, int c)
{
    Matrix ret(r, vector<ll>(c));
    return ret;
}

Matrix makeIdentity(int r, int c)
{
    Matrix ret = makeMatrix(r, c);
    rep(i,0,r)
        ret[i][i] = 1;
    return ret;
}

Matrix addMatrix(const Matrix &a, const Matrix &b)
{
    assert(sz(a) && sz(a) == sz(b) && sz(a[0]) == sz(b[0])); // has atleast one row, and a.dimensions = b.dimensions
    Matrix ret = makeMatrix(sz(a), sz(a[0]));

    for (int i = 0; i < sz(ret); ++i)
        for (int j = 0; j < sz(ret[i]); ++j)
            ret[i][j] = add(a[i][j], b[i][j]);
}

Matrix multMatrix(const Matrix &a, const Matrix &b)
{
    assert(sz(a) && sz(a[0]) == sz(b)); // has atleast one row and a.col = b.row
    Matrix ret = makeMatrix(sz(a), sz(b[0]));

    for (int i = 0; i < sz(ret); ++i)
        for (int j = 0; j < sz(ret[i]); ++j)
            for (int k = 0; k < sz(b); ++k)
                ret[i][j] = add(ret[i][j], mult(a[i][k], b[k][j]));

    return ret;
}

Matrix powerMatrix(Matrix base, ll exp)
{
    assert(sz(base));
    Matrix ret = makeIdentity(sz(base), sz(base[0]));

    for (; exp; exp >>= 1)
    {
        if (exp&1)
            ret = multMatrix(ret, base);
        base = multMatrix(base, base);
    }
    return ret;
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
    ll n, m;
    Matrix base = makeMatrix(2, 1);
    base[0][0] = 1;
    base[1][0] = 0;
    while(cin >> n >> m)
    {
        if (n == 0)
            cout << 0;
        else if (n == 1)
            cout << 1;
        else
        {
            MOD = (1 << m);
            Matrix t = makeMatrix(2, 2);
            t[0][0] = t[0][1] = 1;
            t[1][0] = 1;

            t = powerMatrix(t, n - 1);
            Matrix res = multMatrix(t, base);
            cout << res[0][0];
        }
        cout << '\n';
    }
    return 0;
}