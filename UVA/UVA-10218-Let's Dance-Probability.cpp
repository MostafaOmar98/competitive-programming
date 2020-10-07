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
const double eps = (1e-9);

int m, w, c;

double power(double base, int exp)
{
    double ret = 1;
    while(exp)
    {
        if (exp&1)
            ret *= base;
        base *= base;
        exp /= 2;
    }
    return ret;
}
double C[1000][1000];
void genC()
{
    C[0][0] = 1;
    for (int i = 1; i <= 997; ++i)
    {
        C[i][0] = 1;
        for (int j = 1; j < i; ++j)
        {
            C[i][j] = C[i - 1][j] + C[i - 1][j-1];
        }
        C[i][i] = 1;
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
    genC();
    while(cin >> m >> w >> c)
    {
        if (!m && !w)
            break;
        double ans = 0;
        for (int tk = 0; tk <= c; tk += 2)
        {
            ans += C[c][tk] * power(1.0 * m/(m+w), tk) * power(1.0 - (1.0 * m/(m+w)), c - tk);
        }
        printf("%0.7lf\n", ans);
    }
    return  0;

}