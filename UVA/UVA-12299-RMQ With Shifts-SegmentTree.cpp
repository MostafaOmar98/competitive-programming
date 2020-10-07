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


int n, q;
const int MAX_N = 100005;
int tree[4 * MAX_N];

void update(int idx, int v, int p = 1, int l = 0, int r = n - 1)
{
    if (l == r)
    {
        tree[p] = v;
        return;
    }
    int mid = (l+r)/2;
    if (idx <= mid)
        update(idx, v, 2 * p, l, mid);
    else
        update(idx, v, 2 * p + 1, mid + 1, r);
    tree[p] = min(tree[2 * p], tree[2 * p + 1]);
}

int get(int a, int b, int p = 1, int l = 0, int r = n - 1)
{
    if (l >= a && r <= b)
    {
        return tree[p];
    }

    if (r < a || l > b)
        return INT_MAX;
    return min(get(a, b, 2 * p, l, (l+r)/2), get(a, b, 2 * p + 1, (l+r)/2 + 1, r));
}

string what;
vector<int> v;
void parse(const string &qry)
{
    what.clear();
    v.clear();
    int i = 0;
    for (i = 0; i < sz(qry) && qry[i] != '('; ++i)
        what += qry[i];
    for (; i < sz(qry); ++i)
    {
        int idx = 0;
        while (i < sz(qry) && isdigit(qry[i]))
        {
            idx = idx * 10 + qry[i] - '0';
            ++i;
        }
        if (idx)
            v.pb(idx - 1);
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
    cin >> n >> q;
    vector<int> a(n);
    rep(i,0,n)
    {
        cin >> a[i];
        update(i, a[i]);
    }

    while(q--)
    {
        string qry;
        cin >> qry;
        parse(qry);
        if (what == "shift")
        {
            for (int i = 0; i < sz(v) - 1; ++i)
            {
                swap(a[v[i]], a[v[i+1]]);
            }
            for (int i = 0; i < sz(v); ++i)
                update(v[i], a[v[i]]);
        }
        else
        {
            cout << get(v[0], v[1]) << '\n';
        }
    }

    return 0;
}