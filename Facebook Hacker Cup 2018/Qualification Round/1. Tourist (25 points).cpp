#include <bits/stdc++.h>

using namespace std;


typedef long long ll;
#define rep(i, start, end) for(int i = start; i < end; ++i)
#define per(i, start, end) for(int i = (int)start-1; i >= end; --i)
#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define clr(d, v) memset(d, v, sizeof(d))
const double PI = 3.14159265358979323846;
const double eps = (1e-12);
const int MOD = 1000000007;

int dcmp(double x, double y)
{
    return fabs(x - y) <= eps ? 0 : x > y ? -1 : 1;
}



int main()
{
    ios_base::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("tourist.txt", "r", stdin);
    freopen("facebook.txt", "w", stdout);
#endif
    int test;
    cin >> test;
    rep(t,1,test+1)
    {
        int k, n;
        ll v;
        cin >> n >> k >> v;
        int st = ((v-1)*k)%n;
        vector<string> s(n);
        rep(i,0,n)
            cin >> s[i];
        set<string> output;
        for (int i = st, j = 0; j < k; ++j, ++i)
        {
            int cur = i % n;
            output.insert(s[cur]);
        }
        cout << "Case #" << t << ": ";
        rep(i,0,n)
        {
            if (output.find(s[i]) != output.end())
            {
                cout << s[i];
                output.erase(s[i]);
                if (!output.empty())
                    cout << " ";
            }
        }
        cout << endl;
    }
    return 0;
}