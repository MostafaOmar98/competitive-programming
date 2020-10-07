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
const double eps = (1e-8);

bool var[26];
bool mask[26][26]; // if 1 then i < j
bool visit[26];
int cntVar;
string cur;
vector<string> out;

void clear()
{
    clr(var, 0);
    clr(mask, 0);
    clr(visit, 0);
    cntVar = 0;
    cur.clear();
    out.clear();
}

void takeInput()
{
    string input;
    getline(cin, input);
    stringstream ss;
    ss << input;
    char c;
    while(ss >> c)
    {
        var[c - 'A'] = 1;
        cntVar++;
    }

    getline(cin, input);
    ss.clear();
    ss << input;
    while(ss >> input)
    {
        if (input[1] == '>')
            swap(input[0], input[2]);
        mask[input[0] - 'A'][input[2] - 'A'] = 1;
    }

}

bool ok(int c)
{
    for (int i = 0; i < sz(cur); ++i)
    {
        if (mask[c][cur[i] - 'A'])
            return 0;
    }
    return 1;
}

void solve()
{
    if (sz(cur) == cntVar)
    {
        out.pb(cur);
        return;
    }
    for (int i = 0; i < 26; ++i)
    {
        if (visit[i] || !var[i] || !ok(i))
            continue;
        cur += (char)(i + 'A');
        visit[i] = 1;
        solve();
        cur.pop_back();
        visit[i] = 0;
    }
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
    int tt;
    cin >> tt;
    cin.ignore(32767, '\n');
    while(tt--)
    {
        cin.ignore(32767, '\n');
        clear();
        takeInput();
        solve();
        if (out.empty())
            cout << "NO" << '\n';
        else
        {
            sort(out.begin(), out.end());
            for (auto &s : out)
            {
                rep(i,0,sz(s))
                {
                    cout << s[i];
                    if (i != sz(s) - 1)
                        cout << ' ';
                }
                cout << '\n';
            }
        }
        if(tt)
            cout << '\n';
    }
    return  0;

}