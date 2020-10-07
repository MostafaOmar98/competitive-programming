#include<bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp> // Common file
//#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

using namespace std;
//using namespace __gnu_pbds;
//typedef tree<
//        pair<long long, int>, // change type
//        null_type,
//        less<pair<long long, int> >, // change type
//        rb_tree_tag,
//        tree_order_statistics_node_update>
//        ordered_set;
//template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

typedef long long ll;
#define rep(i, start, end) for(int i = start; i < end; ++i)
#define sz(x) (int)(x).size()
#define pb push_back
#define X first
#define Y second
#define all(x) x.begin(), x.end()
#define clr(d, v) memset(d, v, sizeof(d))
#define pii pair<int, int>
#define debug(x) cerr << #x << " : " << (x) << endl
const double PI = 3.14159265358979323846;
const double eps = (1e-9);
inline int isGreater(long double x, long double y)
{
    if (abs(x - y) < eps)
        return 0;
    if (x > y)
        return 1;
    return -1;
}

int n, outIdx;
string s;
long double r, minDiff;

struct state{
    int a, l;
    long double v;
    state(int _a = 0,int _l = 0)
    {
        a = _a;
        l = _l;
        v = 1.0 * a - r * l;
    }
    bool operator<(const state&other)const{
        return isGreater(v, other.v) == -1;
    }
};

int solve(state left, state right)
{
    assert(right.a >= left.a);
    assert(right.l > left.l);
    long double newDiff = fabs((1.0 * (right.a - left.a) / (right.l - left.l)) - r);
    long double temp = 1.0 * (right.a - left.a) / (right.l - left.l);
//    debug(temp);
    int ret = isGreater(newDiff, minDiff);
    if (isGreater(newDiff, minDiff) == -1)
        minDiff = newDiff;
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("facebook.txt", "w", stdout);
#endif
    int tc;
    cin >> tc;
    for (int tid = 1; tid <= tc; ++tid)
    {
        cin >> n >> r >> s;
        set<state> st;
        st.insert(state(0,0));
        minDiff = 1e30;
        outIdx = n;
        for (int i = 0, a = 0, l = 1; i < n; ++i, ++l)
        {
            a += s[i] == '1';
            state cur(a, l);
            auto it = st.lower_bound(cur);
            if (it != st.end())
            {
                int ans = solve(*it, cur);
                if (ans == -1)
                    outIdx = it->l;
                else if(ans == 0)
                    outIdx = min(outIdx, it->l);
            }
            it = st.upper_bound(cur);
            if (it != st.begin())
            {
                --it;
                int ans = solve(*it, cur);
                if (ans == -1)
                    outIdx = it->l;
                else if (ans == 0)
                    outIdx = min(outIdx, it->l);
            }
            it = st.find(cur);
            if (it == st.end())
                st.insert(cur);
        }
        assert(outIdx != n);
        cout << "Case #" << tid << ": " << outIdx << '\n';
//        cerr << endl;
    }
    return 0;
}