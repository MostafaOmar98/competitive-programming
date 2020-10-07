#include <bits/stdc++.h>

using namespace std;

typedef complex<int> point;
#define dp(a, b) ((conj(a) * b).real())
#define vec(a, b) (b - a)
#define cp(a, b) ((conj(a) * b).imag())
#define angle(a) (atan2(a.imag(), a.real()))
#define rotate0(a, angle) (a * exp(point(0, angle)))
#define length(a) (hypot(a.imag(), a.real()))
#define rotateAr(a, angle, around) (rotate0(((a) - (around)),(angle)) + around)
#define reflect(a, m) (conj((a)/(m)) * (m))
#define normalize(a) ((a) / length(a));
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
#define pii pair<int, int>
const double PI = 3.14159265358979323846;
const double eps = (1e-6);

vector<int> a;
int mem[105][50005];
int total;

int solve(int i, int sum)
{
    if (i == sz(a))
    {
        return abs(2 * sum - total);
    }
    int &ret = mem[i][sum];
    if (ret != -1)
        return ret;
    int choice1 = solve(i+1, sum+a[i]);
    int choice2 = solve(i+1, sum);

    ret = min(choice1, choice2);
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
//    freopen("facebook.txt", "w", stdout);
#endif
    int T;
    cin >> T;
    while(T--)
    {
        a.clear();
        clr(mem, -1);
        total = 0;
        int n;
        cin >> n;
        rep(i,0,n)
        {
            int x;
            cin >> x;
            total += x;
            a.pb(x);
        }
        cout << solve(0,0) << '\n';
    }
    return 0;
}