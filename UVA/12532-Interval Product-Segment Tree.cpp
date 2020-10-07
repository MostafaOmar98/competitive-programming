#include<bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp> // Common file
//#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

using namespace std;
//using namespace __gnu_pbds;
//typedef tree<
//        pair<long long, int>, // change type
//        null_type,
//        less<pair<long long, int> >, // change type
//        rb_tree_tag,
//        tree_order_statistics_node_update>
//        ordered_set;

typedef long long ll;
#define rep(i, start, end) for(int i = start; i < end; ++i)
#define sz(x) (int)(x).size()
#define pb push_back
#define row first
#define col second
#define all(x) x.begin(), x.end()
#define clr(d, v) memset(d, v, sizeof(d))
#define pii pair<int, int>
const double PI = 3.14159265358979323846;
const double eps = (1e-4);
int dcmp(long double x, long double y)
{
    if (abs(x - y) < eps)
        return 0;
    if (x > y)
        return 1;
    return -1;
}

int n, q;
const int MAX_N = 100005;
int tree[MAX_N * 4];

void update(int i, int v, int p = 1, int l = 0, int r = n - 1)
{
    if (l == r)
    {
        tree[p] = v;
        return;
    }
    int mid = (l + r)/2;
    if (i <= mid)
        update(i, v, 2 * p, l, mid);
    else
        update(i, v, 2 * p + 1, mid + 1, r);

    tree[p] = tree[2 * p] * tree[2 * p + 1];
}

int get(int stq, int enq, int p = 1, int l = 0, int r = n - 1)
{
    if (r < stq || l > enq)
        return 1;
    if (l >= stq && r <= enq)
        return tree[p];
    int mid = (l+r)/2;
    return get(stq, enq, 2 * p, l, mid) * get(stq, enq, 2 * p + 1, mid + 1, r);
}


void clear()
{
    clr(tree, 0);
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
    while(cin >> n >> q)
    {
        clear();
        rep(i,0,n)
        {
            int v;
            cin >> v;
            if (v > 0)
                v = 1;
            else if (v < 0)
                v = -1;
            else
                v = 0;
            update(i, v);
        }
        string out;
        while(q--)
        {
            char c;
            cin >> c;
            if (c == 'C')
            {
                int i, v;
                cin >> i >> v;
                --i;
                if (v > 0)
                    v = 1;
                else if (v < 0)
                    v = -1;
                else
                    v = 0;
                update(i, v);
            }
            else
            {
                int stq, enq;
                cin >> stq >> enq;
                stq--, enq--;
                int ans = get(stq, enq);
                if (ans == 1)
                    out += '+';
                else if (ans == -1)
                    out += '-';
                else
                    out += '0';
            }
        }
        cout << out << '\n';
    }

    return 0;
}