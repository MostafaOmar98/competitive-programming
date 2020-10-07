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

typedef long long ll;
#define rep(i, start, end) for(int i = start; i < end; ++i)
#define sz(x) (int)(x).size()
#define pb push_back
#define row first
#define col second
#define all(x) x.begin(), x.end()
#define clr(d, v) memset(d, v, sizeof(d))
#define pii pair<int, int>
const double PI = 3.14159265358979323846;
const double eps = (1e-4);
int dcmp(long double x, long double y)
{
    if (abs(x - y) < eps)
        return 0;
    if (x > y)
        return 1;
    return -1;
}

struct state{
    int maxFreqVal, maxFreq;
    int leftFreqVal, leftFreq;
    int rightFreqVal, rightFreq;
};

int n;
vector<int> a;
const int MAX_N = 100005, MAX_K = 20;
state table[MAX_N][MAX_K];
int Log[MAX_N];


state getNewState(state s1, state s2)
{
    state newState;
    newState.leftFreqVal = s1.leftFreqVal, newState.leftFreq = s1.leftFreq;
    newState.rightFreqVal = s2.rightFreqVal, newState.rightFreq = s2.rightFreq;
    if (s1.rightFreqVal == s2.rightFreqVal)
        newState.rightFreq += s1.rightFreq;
    if (s1.leftFreqVal == s2.leftFreqVal)
        newState.leftFreq += s2.leftFreq;
    if (s1.rightFreqVal == s2.leftFreqVal && s1.rightFreq + s2.leftFreq >= max(s1.maxFreq, s2.maxFreq))
    {
        newState.maxFreq = s1.rightFreq + s2.leftFreq;
        newState.maxFreqVal = s1.rightFreqVal;
    }
    else if (s1.maxFreq >= s2.maxFreq)
    {
        newState.maxFreq = s1.maxFreq;
        newState.maxFreqVal = s1.maxFreqVal;
    }
    else if (s2.maxFreq >= s1.maxFreq)
    {
        newState.maxFreq = s2.maxFreq;
        newState.maxFreqVal = s2.maxFreqVal;
    }
    else
        assert(0);
    return newState;
}

void sparsePre()
{
    for (int i = 0; i < n; ++i)
        table[i][0] = {a[i], 1, a[i], 1, a[i], 1};

    for (int j = 1; (1<<j) <= n; ++j)
    {
        for (int i = 0; i + (1<<j) - 1 < n; ++i)
        {
            state s1 = table[i][j - 1], s2 = table[i + (1<<(j - 1))][j - 1];
            table[i][j] = getNewState(s1, s2);

        }
    }

}

int getMax(int st, int en)
{
    state ans;
    bool first = 1;
    for (int j = MAX_K; j >= 0; --j)
    {
        if (st + (1<<j) - 1 <= en)
        {
            if (first)
            {
                ans = table[st][j];
                first = 0;
            }
            else
                ans = getNewState(ans, table[st][j]);
            st += (1<<j);
        }
    }
    return ans.maxFreq;
}


void clear()
{
    a.clear();
    a.resize(n);
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
    Log[1] = 0;
    for (int size = 2; size <= n; ++size)
        Log[size] = Log[size/2] + 1;
    while (cin >> n && n)
    {
        clear();
        int q;
        cin >> q;
        for (int i = 0; i < n; ++i)
            cin >> a[i];
        sparsePre();
        while(q--)
        {
            int st, en;
            cin >> st >> en;
            --st; --en;
            cout << getMax(st, en) << '\n';
        }
    }

    return 0;
}