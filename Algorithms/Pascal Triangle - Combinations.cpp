#include <bits/stdc++.h>

using namespace std;

typedef complex<int> point;
#define dp(a, b) ((conj(a) * b).real())
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


ll C[N][N];
void genComb()
{
    C[0][0] = 1;
    for (int r = 1; r < N; ++r)
    {
        C[r][0] = 1;
        C[r][r] = 1;
        for (int j = 1; j < r; ++j)
        {
            C[r][j] = C[r-1][j] + C[r-1][j-1];
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
//    freopen("facebook.txt", "w", stdout);
#endif

    return 0;
}