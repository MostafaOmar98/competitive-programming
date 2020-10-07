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
int mem[1005][1005];
int nxt[1005];

int solve(int i, int prev)
{
    if (i == sz(a))
    {
        return 0;
    }
    int &ret = mem[i][prev];
    if (ret != -1)
        return ret;
    ret = INT_MIN;
    int choice1 = solve(i+1, prev);
    int choice2 = 0;
    if (prev == 1004 || a[i] > a[prev])
        choice2 = 1 + solve(i+1, i);

    if (choice2 > choice1)
        nxt[prev] = i;

    ret = max(choice1, choice2);
    return ret;
}
void print(int i)
{
    if (nxt[i] == -1)
        return;
    cout << a[nxt[i]] << '\n';
    print(nxt[i]);
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
    cin.ignore(32767, '\n');
    string inp;
    getline(cin, inp);
    while(T--)
    {
        a.clear();
        clr(mem, -1);
        clr(nxt, -1);
        while(getline(cin, inp) && sz(inp))
        {
            a.pb(atoi(inp.c_str()));
        }
        cout << "Max hits: " <<  solve(0,1004) << '\n';
        print(1004);
        if (T > 0)
            cout << '\n';
    }
    return 0;
}