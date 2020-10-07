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
void genPrimes()
{
    clr(isPrime, true);
    isPrime[0] = 0, isPrime[1] = 0;
    for (int i = 2; i < N; ++i)
    {
        if (isPrime[i])
        {
            primes.pb(i);
            for (int j = 2 * i; j < N; j += i)
            {
                isPrime[j] = 0;
            }
        }
    }
}

long long power(int base, int exp)
{
    if (exp == 0)
        return 1;
    long long sq = power(base, exp/ 2);
    sq = sq * sq;
    if (exp&1)
        sq *= base;
    return sq;
}

bool overflow(long double x)
{
    if (x > 1e9)
        return 1;
    return 0;
}

int pFreq[N];
int f(int pr) // Gets amount of prime pr in range [pr, n], stops once pr^ret overflows
{
    int ret = 0;
    for (int i = pr; i <= n && !overflow(power(pr, ret)); i += pr)
    {
        int num = i;
        while(num % pr == 0)
        {
            num /= pr;
            ++ret;
        }
    }
    return ret;
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
    genPrimes();
    while(cin >> n >> m)
    {
        for (auto item : primes) // amount of primes in n!, doesn't matter once excceeds overflow, primes less than sqrt(m) not important either
        {
            pFreq[item] = f(item);
        }

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
            if (cnt > pFreq[i])
            {
                ok = 0;
                break;
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