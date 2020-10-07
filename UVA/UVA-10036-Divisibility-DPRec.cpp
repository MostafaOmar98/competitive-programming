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
const double eps = (1e-8);

int n, k;

int mod(int x)
{
    return (x%k + k)%k;
}

vector<int> a;
int mem[10005][105];
void clear()
{
    clr(mem, -1);
    a.clear();
    a.resize(n);
}

bool solve(int i, int sum)
{
    if (i == n)
    {
        if (sum == 0)
            return 1;
        return 0;
    }
    int &ret = mem[i][sum];
    if (ret != -1)
        return ret;

    ret = 0;
    ret |= solve(i+1, mod(sum + a[i]));

    ret |= solve(i+1, mod(sum - a[i]));

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
        cin >> n >> k;
        clear();
        rep(i,0,n)
        {
            cin >> a[i];
            a[i] = a[i]%k;
        }
        if (solve(0,0))
            cout << "Divisible\n";
        else
            cout << "Not divisible\n";
    }
    return 0;
}