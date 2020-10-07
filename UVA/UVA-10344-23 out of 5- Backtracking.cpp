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
const double PI = 3.14159265358979323846;
const double eps = (1e-8);

vector<int> a;
bool visitNum[5];


bool permNum(int cur, int res)
{
    if (cur == 5)
    {
        return (res == 23);
    }

    rep(i, 0, 5)
    {
        if (!visitNum[i])
        {
            visitNum[i] = 1;
            if (permNum(cur + 1, res + a[i]))
                return 1;
            if (cur > 0)
            {
                if (permNum(cur +1, res * a[i]))
                    return 1;
                if (permNum(cur + 1, res - a[i]))
                    return 1;
            }
            visitNum[i] = 0;
        }
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
//    freopen("facebook.txt", "w", stdout);
#endif
    a.resize(5);
    while (cin >> a[0] && a[0])
    {
        clr(visitNum, 0);
        rep(i, 1, 5)
        {
            cin >> a[i];
        }
        vector<int> perm;
        if (permNum(0,0))
            cout << "Possible";
        else
            cout << "Impossible";
        cout << '\n';
    }
    return 0;
}