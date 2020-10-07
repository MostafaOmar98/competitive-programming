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
ll mem[63][63];
/*
 * 3 choices
 * Delete left
 * Delete right
 * These 2 cases handle Delete both and actually is double counted
 * KEEP left and right can only be done when s[i] == s[j]
 */
ll solve(int i, int j)
{
    /*
     * base case like this because
     * 1 character is counted as palindrome
     * Empty string is not counted as a palindrome
     * Pain in the ass to handle these in transitions, add case of 2 characters to base case.
     */
    if (i == j)
        return 1;
    if (i + 1 == j)
        return 2 + (s[i] == s[j]);
    ll &ret = mem[i][j];
    if (~ret)
        return ret;
    ret = 0;
    if (s[i] == s[j]) // I can keep both characters
        ret += solve(i + 1, j - 1) + 1; // + 1 cuz s[i]..solve(i+1,j-1) amount of palindromes..s[j] are palindromes but s[i]s[j] when container is empty mat7sabtesh
    // delete left or delete right
    ret += solve(i + 1, j);
    ret += solve(i ,j - 1);
    ret -= solve(i + 1, j - 1);
    return ret;
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
    int t;
    cin >> t;
    while(t--)
    {
        cin >> s;
        clr(mem, -1);
        cout << solve(0, sz(s) - 1) << '\n';
    }
    return 0;
}