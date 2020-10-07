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

string s;
int mem[1003][1003];


int solve(int i, int j)
{
    if (i >= j)
        return 0;
    int &ret = mem[i][j];
    if (~ret)
        return ret;
    ret = INT_MAX;
    if (s[i] == s[j])
        ret = min(ret, solve(i + 1, j - 1));
    ret = min(ret, 1 + solve(i + 1, j));
    ret = min(ret, 1 + solve(i, j - 1));
    return ret;
}
string memBuild[1002][1002];
bool visitBuild[1002][1002];
string build(int i, int j)
{

    if (i >= j)
    {
        string temp;
        if (i == j)
            temp += s[i];
        return temp;
    }
    int ret = mem[i][j];
    string &ans = memBuild[i][j];
    if (visitBuild[i][j])
        return memBuild[i][j];
    visitBuild[i][j] = 1;
    if (s[i] == s[j])
    {
        if (ret == solve(i + 1, j - 1))
        {
            ans = s[i] + build(i + 1, j - 1);
            return ans;
        }

    }
    if (solve(i + 1,j) == solve(i, j - 1))
    {
        ans = min(build(i + 1, j), build(i, j - 1));
        return ans;
    }
    if (ret == 1 + solve(i + 1, j))
    {
        ans = build(i + 1, j);
        return ans;
    }
    if (ret ==  1 + solve(i, j - 1))
    {
        ans = build(i, j -1);
        return ans;
    }
    return ans;

}

void clear()
{
    clr(mem, -1);
    clr(visitBuild, 0);
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
    while(cin >> s)
    {
        clear();
        int del = solve(0,sz(s) - 1);
        string ans = build(0, sz(s) - 1);
        string revAns = ans;
        if ((sz(s) - del)&1)
            revAns.pop_back();
        reverse(all(revAns));
        cout << ans + revAns << '\n';
    }
    return 0;
}