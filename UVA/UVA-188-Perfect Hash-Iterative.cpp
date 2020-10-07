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

vector<int> w;
set<int> words;

int base32(string const &s)
{
    int pw32 = 1;
    int ret = 0;
    for (int i = sz(s) - 1; i >= 0; --i)
    {
        ret = ret + (s[i] - 'a' + 1) * pw32;
        pw32 *= 32;
    }
    return ret;
}

void parse(string const &inp)
{
    stringstream ss;
    ss << inp;
    string s;
    while (ss >> s)
    {
        int x = base32(s);
        words.insert(x);
    }
    for (auto item : words)
    {
        w.pb(item);
    }
}

//int solve(int c)
//{
//    int n = sz(w);
//    map<int, int> conflict; // conflict mod to smallest possible next C
//    for (int i = 0; i < n; ++i)
//    {
//        int mod = (c / w[i]) % n;
//        int nextC = ((c / w[i]) + 1) * w[i];
//        if (conflict.find(mod) == conflict.end())
//            conflict[mod] = nextC;
//        else
//            conflict[mod] = min(conflict[mod], nextC);
//    }
//    if (sz(conflict) == n)
//        return c;
//    int nextC = INT_MIN;
//    for (auto item : conflict)
//    {
//        nextC = max(item.S, nextC);
//    }
//    return solve(nextC);
//}
int solve(int c)
{
    int n = sz(w);
    while(1)
    {
        int nextC = INT_MIN;
        rep(i, 0, n)
        {
            rep(j, i + 1, n)
            {
                if ((c / w[i]) % n == (c / w[j]) % n)
                {
                    nextC = max(nextC, min(((c / w[i]) + 1) * w[i], ((c / w[j]) + 1) * w[j]));
                }
            }
        }
        if(nextC == INT_MIN)
            break;
        c = nextC;
    }
    return c;
}

void clear()
{
    words.clear();
    w.clear();
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("facebook.txt", "w", stdout);
#endif
    string inp;
    while (getline(cin, inp))
    {
        clear();
        parse(inp);
        cout << inp << '\n';
        cout << solve(1) << '\n' << '\n';
    }
    return 0;
}