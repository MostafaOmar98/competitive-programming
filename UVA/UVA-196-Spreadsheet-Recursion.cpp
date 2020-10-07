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

int n, m;
string grid[1005][20000];
int ans[1000][20000];


int power(int base, int exp)
{
    if (exp == 0)
        return 1;
    int sq = power(base, exp/2);
    sq = sq * sq;
    if (exp&1)
        sq = sq * base;
    return sq;
}

void fetch(int &r, int &c, string const &s)
{
    int i;
    string temp;
    for (i = sz(s) - 1; i >= 0 && isdigit(s[i]); --i)
    {
        temp += s[i];
    }
    reverse(all(temp));
    r = atoi(temp.c_str()) - 1;
    int sum = 0;
    for (int cnt = 0; i >= 0; --i, ++cnt)
    {
        sum = sum + power(26, cnt) * (s[i] - 'A' + 1);
    }
    c = sum - 1;
}

int process(int i, int j)
{
    if (grid[i][j][0] != '=')
        return atoi(grid[i][j].c_str());
    if (ans[i][j] != -1)
        return ans[i][j];

    int &sum = ans[i][j];
    sum = 0;
    string temp;
    for (int k = 1; k < sz(grid[i][j]); ++k)
    {
        while (k < sz(grid[i][j]) && grid[i][j][k] != '+')
        {
            temp += grid[i][j][k];
            ++k;
        }
        int r, c;
        fetch(r, c, temp);
        sum = sum + process(r, c);
        temp = "";
    }
    return sum;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("facebook.txt", "w", stdout);
#endif
    int T;
    cin >> T;
    while(T--)
    {
        clr(ans, -1);
        cin >> m >> n;
        rep(i,0,n)
        {
            rep(j,0,m)
            {
                cin >> grid[i][j];
            }
        }
        rep(i,0,n)
        {
            rep(j,0,m)
            {
                cout << process(i, j);
                if (j != m-1)
                    cout << ' ';
            }
            cout << '\n';
        }
    }
    return 0;
}