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

//template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

typedef long long ll;
#define rep(i, start, end) for(int i = start; i < end; ++i)
#define sz(x) (int)(x).size()
#define pb push_back
#define X first
#define Y second
#define all(x) x.begin(), x.end()
#define clr(d, v) memset(d, v, sizeof(d))
#define pii pair<int, int>
#define debug(x) cerr << #x << " : " << (x) << endl
const double PI = 3.14159265358979323846;
const double eps = (1e-5);
int isGreater(long double x, long double y)
{
    if (abs(x - y) < eps)
        return 0;
    if (x > y)
        return 1;
    return -1;
}

int n;
const int MAX_N = 2e5 + 5, MAX_V = 1e6 + 5;
bool isPrime[MAX_V];
vector<int> divs[2 * MAX_N];
void sieve(ll l, ll r)
{
    clr(isPrime, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i < MAX_V; ++i)
    {
        if (isPrime[i])
        {
            ll s = (l + i - 1)/i * i;
            for (ll x = s; x <= r; x += i) // 2n iterations
                divs[x - l].push_back(i);

            for (int j = 2 * i; j < MAX_V; j += i)
                isPrime[j] = false;
        }
    }
}

int main()
{
    sieve(l, r);

    vector<ll> primes;
    for (ll x = l; x <= r; ++x)
    {
        ll temp = x;
        for (int p : divs[x - l])
        {
            primes.push_back(p);
            while(temp%p == 0)
                temp /= p;
        }
        if (temp > 1)
            primes.push_back(temp);
    }

    sort(all(primes));
    primes.resize(unique(primes.begin(), primes.end()) - primes.begin());

    cout << solve(primes) << '\n';

    return 0;
}