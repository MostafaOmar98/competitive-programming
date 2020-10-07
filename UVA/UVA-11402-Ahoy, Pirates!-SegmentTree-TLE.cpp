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

char inp[1000];
int n;
const int MAX_N = 1024005;
int a[(1<<21)];
int tree[(1<<21)], lazy[(1<<21)];

void apply(int p, int v)
{
    if (v == 1)
        lazy[p] = 1;
    else if (v == 0)
        lazy[p] = 0;
    else
    {
        if (lazy[p] == -1)
            lazy[p] = 2;
        else if (lazy[p] == 1)
            lazy[p] = 0;
        else if (lazy[p] == 0)
            lazy[p] = 1;
        else
            lazy[p] = -1;
    }

}

void check(int p, int l, int r)
{
    if (lazy[p] != -1)
    {
        if (lazy[p] == 0)
        {
            tree[p] = 0;
        }
        else if (lazy[p] == 1)
        {
            tree[p] = (r - l + 1);
        }
        else
        {
            tree[p] = (r - l + 1) - tree[p]; // complement
        }
        if (l!=r)
        {
            apply(2 *p, lazy[p]);
            apply(2 *p + 1, lazy[p]);
        }
        lazy[p] = -1;
    }
}

void update(int a, int b, int v, int p = 1, int l = 0, int r = n -1)
{
    if (l >= a && r <= b)
    {
        apply(p, v);
        check(p, l, r);
        return;
    }
    check(p,l,r);
    if (r < a || l > b)
        return;
    update(a, b, v, 2 * p, l, (l+r)/2);
    update(a, b, v, 2 * p + 1, (l+r)/2 + 1, r);
    tree[p] = tree[2 * p] + tree[2 * p + 1];
}

int get(int a, int b, int p = 1, int l = 0, int r = n -1)
{
    check(p, l, r);
    if (l >= a && r <= b)
        return tree[p];
    if (r < a || l > b)
        return 0;
    return get(a, b, 2 * p, l ,(l+r)/2) + get(a, b, 2 * p + 1, (l+r)/2 + 1, r);
}



int main()
{
//    ios_base::sync_with_stdio(false);
//    cin.tie(0);
//    cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("facebook.txt", "w", stdout);
#endif
    int tc;
    scanf(" %d", &tc);
    for (int tt = 1; tt <= tc; ++tt)
    {
        printf("Case %d:\n", tt);
        int m;
        scanf(" %d", &m);
        int k = 0;
        rep(i,0,m)
        {
            int times;
            scanf(" %d %s", &times, inp);
            while(times--)
            {
                for (int j = 0; inp[j]; ++j)
                {
//                    if (inp[j] != '0' && inp[j] != '1')
//                    {
//                        cout << "HEY" << endl;
//                    }
                    a[k++] = inp[j] - '0';
                }
            }
        }
        n = k;
        rep(i,0,n)
        {
//            cout << a[i];
            update(i,i,a[i]);
        }
//        cout << endl;

        int q;
        scanf("%d", &q);
        int questions = 0;
        while(q--)
        {
            char c;
            int l, r;
            scanf(" %c %d %d", &c, &l, &r);
            if (c == 'F')
                update(l, r, 1);
            else if (c == 'E')
                update(l, r, 0);
            else if (c == 'I')
                update(l,r, 2);
            else
            {
                printf("Q%d: %d\n", ++questions, get(l,r));
            }
        }
    }
    return 0;
}