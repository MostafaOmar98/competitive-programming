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
const double PI = 3.14159265358979323846;
const double eps = (1e-9);




int dcmp(double x, double y)
{
    return fabs(x - y) <= eps ? 0 : x < y ? -1 : 1;
}

const int MOD = 1000000007;
ll mod(ll x)
{
    return (x%MOD + MOD)%MOD;
}

ll mult(ll x, ll y)
{
    return (x%MOD * y%MOD)%MOD;
}

ll add(ll x, ll y)
{
    return (x%MOD + y%MOD)%MOD;
}

ll power(ll base, int exp)
{
    ll ret = 1;
    while(exp)
    {
        if (exp&1)
            ret = mult(ret, base);
        base = mult(base, base);
        exp /= 2;
    }
    return ret;
}

ll modInverse(ll x)
{
    return power(x, MOD - 2);
}

ll div(ll x, ll y)
{
    return mult(x, modInverse(y));
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
        return {findSign(a), 0};
    if (a == 0)
        return {0, 1};
    int div = __gcd(abs(a), abs(b));
    a /= div;
    b /= div;
    int sign = findSign(a) * findSign(b);
    return {sign * abs(a), abs(b)};
}
// ax + by = gcd(a, b)
/*
 * solves modInverse as x from extended_euclid(a, m) is the modinverse of a under m (Valid only when gcd(a, m) == 1)
 */
ll extended_euclid(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    ll g = extended_euclid(b, a % b, y,x);
    y -= (a/b) * x;
    return g;
}

int main()
{
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<> uniform(0, n);
    return 0;
}