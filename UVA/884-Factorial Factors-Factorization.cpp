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
//
//const int MAX_N = 1000005;
//vector<int> primes;
//bool isPrime[MAX_N];
//void sieve()
//{
//    clr(isPrime, true);
//    isPrime[0] = isPrime[1] = 0;
//    for (int i = 2; i < MAX_N; ++i)
//    {
//        if (isPrime[i])
//        {
//            primes.push_back(i);
//            for (int j = 2 * i; j < MAX_N; j += i)
//                isPrime[j] = false;
//        }
//    }
//}

//for (auto p : primes)
//{
// if (p > n)
//break;
//ll r = p;
//while(n/r > 0)
//{
//ans += n/r;
//r *= p;
//}
//}

int ans[MAX_N], cntDiv[MAX_N];
bool visit[MAX_N];
void pre()
{
    for (int i = 2; i <= 1000000; ++i)
    {
        int x = i;
        bool done = 0;
        for (int j = 2; !done && j <= x/j; j += 1 + (j&1))
        {
            if (visit[x])
            {
                cntDiv[i] += cntDiv[x];
                done = 1;
                break;
            }
            while(x%j == 0)
            {
                cntDiv[i]++;
                x /= j;
                if (visit[x])
                {
                    cntDiv[i] += cntDiv[x];
                    done = 1;
                    break;
                }
            }
        }

        if (!done && x > 1)
            cntDiv[i]++;
        ans[i] = ans[i - 1] + cntDiv[i];
        visit[i] = 1;
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
    pre();
    int n;
    while(cin >> n)
    {
        cout << ans[n] << '\n';
    }

    return 0;
}



/*
 * EVEN faster version
 */

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

const int MAX_N = 1000005;
vector<int> primes;
bool isPrime[MAX_N];
void sieve()
{
    clr(isPrime, true);
    isPrime[0] = isPrime[1] = 0;
    for (int i = 2; i < MAX_N; ++i)
    {
        if (isPrime[i])
        {
            primes.push_back(i);
            for (int j = 2 * i; j < MAX_N; j += i)
                isPrime[j] = false;
        }
    }
}

//for (auto p : primes)
//{
// if (p > n)
//break;
//ll r = p;
//while(n/r > 0)
//{
//ans += n/r;
//r *= p;
//}
//}

int ans[MAX_N], cntDiv[MAX_N];
bool visit[MAX_N];
void pre()
{
    for (int i = 2; i <= 1000000; ++i)
    {
        int x = i;
        bool done = 0;
        for (auto j : primes)
        {
            if (isPrime[x] || done)
                break;
            if (visit[x])
            {
                cntDiv[i] += cntDiv[x];
                done = 1;
                break;
            }
            while(x%j == 0)
            {
                cntDiv[i]++;
                x /= j;
                if (visit[x])
                {
                    cntDiv[i] += cntDiv[x];
                    done = 1;
                    break;
                }
            }
        }

        if (!done && x > 1)
            cntDiv[i]++;
        ans[i] = ans[i - 1] + cntDiv[i];
        visit[i] = 1;
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
    sieve();
    pre();
    int n;
    while(cin >> n)
    {
        cout << ans[n] << '\n';
    }

    return 0;
}