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
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define clr(d, v) memset(d, v, sizeof(d))
#define pii pair<int, int>
const double PI = 3.14159265358979323846;
const double eps = (1e-7);
int dcmp(long double x, long double y)
{
    if (abs(x - y) < eps)
        return 0;
    if (x > y)
        return 1;
    return -1;
}

int n, t;
const int MAX_N = 27;
int iniFish[MAX_N], decreaseRate[MAX_N], timeToNext[MAX_N];
int mem[MAX_N][16 * 60 / 5 + 5];
int solve(int i, int remT)
{
    if (i == n || remT <= 0)
        return 0;
    int &ret = mem[i][remT];
    if (~ret)
        return ret;
    ret = solve(i + 1, remT - timeToNext[i]);
    int take = iniFish[i], totalTake = 0;
    for (int spent = 1; spent <= remT; ++spent)
    {
        totalTake += take;
        take -= decreaseRate[i];
        take = max(take, 0);
        ret = max(ret, totalTake + solve(i + 1, remT - spent - timeToNext[i]));
    }
    return ret;
}

vector<int> out;
void build(int i, int remT)
{
    if (i == n || remT <= 0)
        return;
    int ret = mem[i][remT];
    priority_queue<int> choices;
    if (ret == solve(i + 1, remT - timeToNext[i]))
        choices.push(0);
    int take = iniFish[i], totalTake = 0;
    for (int spent = 1; spent <= remT; ++spent)
    {
        totalTake += take;
        take -= decreaseRate[i];
        take = max(take, 0);
        if(ret == totalTake + solve(i + 1, remT - spent - timeToNext[i]))
            choices.push(spent);
    }
    out[i] = choices.top();
    build(i + 1, remT - out[i] - timeToNext[i]);
    return;
}

void clear()
{
    clr(mem, -1);
    out.clear();
    out.resize(n, 0);
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
    bool first = 1;
    while(cin >> n && n)
    {
        if (!first)
            cout << '\n';
        else
            first = 0;
        clear();
        cin >> t;
        t *= 60/5;
        rep(i,0,n)
            cin >> iniFish[i];
        rep(i,0,n)
            cin >> decreaseRate[i];
        rep(i,0,n - 1)
            cin >> timeToNext[i];
        solve(0, t);
        build(0, t);
        rep(i,0,sz(out))
        {
            cout << out[i] * 5;
            if (i != sz(out) - 1)
                cout << ", ";
        }
        cout << '\n';
        cout << "Number of fish expected: " << solve(0,t) << '\n';
    }
    return 0;
}