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

vector<int> pi;
void find_pre(const string &s)
{
    pi.clear();
    pi.resize(s.size(), 0);
    for (int i = 1; i < sz(s); ++i)
    {
        int len = pi[i - 1];
        while(len > 0 && s[i] != s[len])
        {
            // find greatest smaller prefix that matches a suffix of mine
            len = pi[len - 1];
        }
        pi[i] = len;
        if (s[i] == s[len])
            pi[i]++;
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
    int t;
    cin >> t;
    while(t--)
    {
        string s;
        cin >> s;
        find_pre(s);
        int ans;
        for (int len = 1; len <= sz(s); ++len)
        {
            if (sz(s)%len)
                continue;
            bool ok = 1;
            for (int i = 2 * len - 1, j = 1; i < sz(s); i += len, ++j)
            {
                if (pi[i] != j * len)
                {
                    ok = 0;
                    break;
                }
            }
            if (ok)
            {
                ans = len;
                break;
            }
        }
        cout << ans << '\n';
        if (t)
            cout << '\n';
    }
    return 0;
}