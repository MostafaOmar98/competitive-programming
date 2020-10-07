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

int n, r;
long double a[21];
long double get(int buyCount, int must)
{
    long double pr = 0;
    for (int msk = 0; msk < (1<<n); ++msk)
    {
        if (__builtin_popcount(msk) != buyCount)
            continue;
        if (must != n && !((1<<must)&msk) )
            continue;
        long double tempP = 1;
        for (int j = 0; j < n; ++j)
        {
            if (j == must)
                continue;
            if ((1<<j)&msk)
                tempP *= a[j];
            else
                tempP *= (1.0 - a[j]);
        }
        pr += tempP;
    }
    return pr;

}


/*
 * find p(b|r) = p(b.r)/p(r) -> (1)
 * p(r) can be found through bruteforce generating all possibilties and computing the ones with exactly r people buying (NOTE: r is the exact number of people who bought n-r
 *  bought nothing)
 *  p(r|b) = p(b.r)/p(b)
 *  p(r|b) is a subproblem. generate all possible cases in which this dude bought and find other r-1 people buying
 *  p(b.r) = p(b) * p(r|b)
 *  subsitute in (1) to get ur result ez
 */


/*
 * what I was missing is that r is the EXACT number of people who bought
 */
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
//    freopen("facebook.txt", "w", stdout);
#endif
    int cs = 0;
    while(cin >> n >> r)
    {
        if (!n && !r)
            break;
        cout << "Case " << ++cs << ":\n";
        rep(i,0,n)
            cin >> a[i];
        long double pr = get(r, n);
        rep(i,0,n)
        {
//            long double x = a[i] * get(r, i);
            cout << fixed << setprecision(6) << a[i] * get(r, i) / pr << '\n';
        }
    }
    return  0;

}