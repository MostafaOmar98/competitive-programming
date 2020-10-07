#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

using namespace std;
using namespace __gnu_pbds;
typedef tree<
        pair<int, int>, // change type
        null_type,
        less<pair<int, int> >, // change type
        rb_tree_tag,
        tree_order_statistics_node_update>
        ordered_set;

typedef long long ll;
#define rep(i, start, end) for(int i = start; i < end; ++i)
#define per(i, start, end) for(int i = (int)start-1; i >= end; --i)
#define sz(x) (int)(x).size()
#define pb push_back
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define clr(d, v) memset(d, v, sizeof(d))
#define pii pair<int, int>
const double PI = 3.14159265358979323846;
const double eps = (1e-8);

int n, m;
vector<int> primes;
const int N = 100005;
bool isPrime[N];


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("facebook.txt", "w", stdout);
#endif
    while(cin >> n >> m)
    {
        int outM = m;
        bool ok = 1;
        for (int i = 2; i <= m/i; ++i)
        {
            int cnt = 0;
            while(m%i == 0)
            {
                m /= i;
                ++cnt;
            }
            if (cnt)
            {
                int pFreq = 0;
                for (int j = i; j <= n && pFreq < cnt; j += i) // will either excceed n quickly or excceed cnt quickly since pFreq won't be > 30
                {
                    int num = j;
                    while(num%i == 0)
                    {
                        pFreq++;
                        num /= i;
                    }
                }
                if (cnt > pFreq)
                {
                    ok = 0;
                    break;
                }
            }
        }
        if (m > 1)
        {
            if (m > n)
                ok = false;
        }
        if (!ok)
            cout << outM << " does not divide " << n << "!\n";
        else
            cout << outM << " divides " << n << "!\n";
    }
    return 0;
}