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
const double eps = (1e-9);
int dcmp(long double x, long double y)
{
    if (abs(x - y) < eps)
        return 0;
    if (x > y)
        return 1;
    return -1;
}
int findSign(int x)
{
    if (x == 0)
        return 0;
    return x < 0 ? -1 : 1;
}

pair<int, int> handleFraction(int a, int b)
{
    if (b == 0)
        return {1, 0}; // DO YOU NEED SIGN HERE? In slopes -1, 0 is same as 1, 0
    if (a == 0)
        return {0, 1}; // Does it need findSign(b)?? is sloe {0, -1} same as slope {0, 1}?
    int div = __gcd(abs(a), abs(b));
    a /= div;
    b /= div;
    int sign = findSign(a) * findSign(b);
    return {sign * abs(a), abs(b)};
}
pair<int, int> getSlope(pair<int, int> a, pair<int, int> b)
{
    return {a.Y - b.Y, a.X - b.X};
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
    int tc;
    cin >> tc;
    cin.ignore();
    cin.ignore();
    while(tc--)
    {
        string input;
        vector<pair<int, int> > v;
        while(true)
        {
            getline(cin, input);
            if (input.empty())
                break;
            stringstream ss(input);
            v.push_back({});
            ss >> v.back().first;
            ss >> v.back().second;
//            cout << v.back().first << ' ' << v.back().second << endl;
        }

        int ans = 0;
        rep(i,0,sz(v))
        {
            map<pair<int, int>, int> freq;
            rep(j,0,sz(v))
            {
                if (i == j)
                    continue;
                pair<int, int> slope = getSlope(v[i], v[j]);
                slope = handleFraction(slope.first, slope.second);
                ans = max(ans, ++freq[slope] + 1);
            }
        }
        cout << ans << '\n';
        if (tc)
            cout << '\n';
    }

    return 0;
}