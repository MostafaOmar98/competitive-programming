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

int N;
vector<int> parent, child;
bool same_stack(int x, int y)
{
    if (x == y)
        return 1;
    int cur = x;
    while(parent[cur] != cur)
    {
        if (parent[cur] == y)
            return 1;
        cur = parent[cur];
    }
    cur = x;
    while(child[cur] != -1)
    {
        if (child[cur] == y)
            return 1;
        cur = child[cur];
    }
    return 0;
}
void link(int a, int b)
{
    int x = b;
    while(child[x] != -1)
        x = child[x];

    if (parent[a] != a)
        child[parent[a]] = -1;
    child[x] = a;
    parent[a] = x;
}
void delink(int x)
{
    int cur = child[x];
    child[x] = -1;
    vector<int> process;
    while (cur != -1)
    {
        process.pb(cur);
        cur = child[cur];
    }
    rep(i,0,sz(process))
    {
        parent[process[i]] = process[i];
        child[process[i]] = -1;
    }
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("facebook.txt", "w", stdout);
#endif
    cin >> N;
    string cA, cB;
    parent.resize(N);
    child.resize(N);
    rep(i,0,N)
    {
        parent[i] = i;
        child[i] = -1;
    }
    while(cin >> cA && cA != "quit")
    {
        int a, b;
        cin >> a >> cB >> b;
        if(!same_stack(a, b))
        {
            if (cA == "move")
                delink(a);
            if (cB == "onto")
                delink(b);
            link(a, b);
        }
    }
    vector<bool> visit(N);
    rep(i,0,N)
    {
        cout << i << ":";
        int cur = i;
        if (parent[i] == i)
        {
            cout << ' ';
            while (!visit[cur] && child[cur] != -1)
            {
                cout << cur << ' ';
                visit[cur] = 1;
                cur = child[cur];
            }
            if (!visit[cur])
            {
                cout << cur;
                visit[cur] = 1;
            }
        }
        cout << '\n';
    }
    return 0;
}