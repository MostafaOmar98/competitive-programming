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


long double power(long double base, int exp)
{
    long double ret = 1;
    while(exp)
    {
        if (exp&1)
            ret *= base;
        base *= base;
        exp >>= 1;
    }
    return ret;
}

int m, w, c;
long double p;
long double mem[105][2];
long double solve(int leftCandy, bool isEven)
{
    if (!leftCandy)
        return isEven;
    long double &ret = mem[leftCandy][isEven];
    if (ret == ret)
        return ret;
    ret = p * solve(leftCandy - 1, !isEven);
    ret += (1.0 - p) * solve(leftCandy - 1, isEven);
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
    while (cin >> m >> w >> c && (m || w))
    {
        clr(mem, -1);
        p = 1.0 * m/(m+w);
        cout << fixed << setprecision(7) << solve(c, 1) << '\n';
    }
    return  0;

}