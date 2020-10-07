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
vector<int> v;
void gcd(int a, int b)
{
    if (a == 0 || b == 0)
        return;
    if (a > b)
    {
        v.pb(a/b);
        gcd(a%b, b);
    }
    else
    {
        v.pb(b/a);
        gcd(a, b%a);
    }
}
bool optimal(int st, vector<int> const &v)
{
    bool odd = false;
    for (int i = st; i < sz(v) - 1; ++i)
    {
        if (v[i] != 1)
            break;
        odd = !odd;
    }
    return odd;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
//    freopen("facebook.txt", "w", stdout);
#endif
    int a, b;
    while (cin >> a >> b && a)
    {
        v.clear();
        gcd(a, b);
        int turn = 1;
        rep(i,0,sz(v) - 1)
        {
            if (v[i] == 1)
                turn = !turn;
            else
            {
                bool odd = optimal(i+1, v);
                if (v[i + 1] != 1)
                    continue;
                else if (v[i + 1] == 1 && !odd)
                    continue;
                else
                    turn = !turn;
            }
        }
        if (turn)
            cout << "Stan wins\n";
        else
            cout << "Ollie wins\n";
    }
    return 0;
}