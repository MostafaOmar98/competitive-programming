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
const double eps = (1e-7);
int dcmp(long double x, long double y)
{
    if (abs(x - y) < eps)
        return 0;
    if (x > y)
        return 1;
    return -1;
}

int dp[202][202];
int calcDist(pii a, pii b)
{
    int diffX = a.first - b.first, diffY = a.second - b.second;
    return diffX * diffX + diffY * diffY;
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
    int n;
    int t = 1;
    while(cin >> n && n)
    {
        vector<pair<int, int> > v(n);
        rep(i, 0, n)
            cin >> v[i].first >> v[i].second;

        rep(i,0,n)
        {
            rep(j, i, n)
            {
                dp[j][i] = dp[i][j] = calcDist(v[i], v[j]);
            }
        }
        for (int k = 0; k < n; ++k)
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    dp[i][j] = min(dp[i][j], max(dp[i][k], dp[k][j]));

        cout << "Scenario #" << t++ << '\n';
        cout << "Frog Distance = " << fixed << setprecision(3) << sqrt(dp[0][1]) << '\n';
        cout << '\n';
    }
    return 0;
}