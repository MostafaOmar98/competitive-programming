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
    int maxFreq, leftFreq, rightFreq;
};

int n;
vector<int> a;
const int MAX_N = 100005;
state tree[4 * MAX_N];

state getNewState(int p, int l, int r)
{
    int c = 2 * p;
    int mid = (l+r)/2;
    state ret;
    ret.maxFreq = max(tree[c].maxFreq, tree[c + 1].maxFreq);

    ret.leftFreq = tree[c].leftFreq;
    ret.rightFreq = tree[c + 1].rightFreq;
    if (a[r] == a[mid])
        ret.rightFreq += tree[c].rightFreq;
    if (a[l] == a[mid + 1])
        ret.leftFreq += tree[c + 1].leftFreq;

    if (a[mid] == a[mid + 1])
        ret.maxFreq = max(ret.maxFreq, tree[c].rightFreq + tree[c + 1].leftFreq);
    return ret;
}

void update(int i,int p = 1, int l = 0,int  r = n - 1)
{
    if (l == r)
    {
        tree[p] = {1, 1, 1};
        return;
    }
    int c = 2 * p, mid = (l+r)/2;
    update(i, c, l, mid);
    update(i, c + 1, mid + 1, r);
    tree[p] = getNewState(p, l, r);
}

state get(int st, int en, int p = 1, int l = 0, int r = n -1)
{
    if (r < st || l > en)
        return {0, 0, 0};
    if (l >= st && r <= en)
        return tree[p];
    int c = 2 * p, mid = (l+r)/2;
    state s1 = get(st, en, c, l, mid), s2 = get(st, en, c + 1, mid + 1, r);
    state ret;
    ret.maxFreq = max(s1.maxFreq, s2.maxFreq);

    ret.leftFreq = s1.leftFreq, ret.rightFreq = s2.rightFreq;
    if (a[mid] == a[r])
        ret.rightFreq += s1.rightFreq;
    if (a[mid + 1] == a[l])
        ret.leftFreq += s2.leftFreq;

    if (a[mid] == a[mid + 1])
        ret.maxFreq = max(ret.maxFreq, s1.rightFreq + s2.leftFreq);

    return ret;

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
    while (cin >> n && n)
    {
        clear();
        int q;
        cin >> q;
        for (int i = 0; i < n; ++i)
        {
            cin >> a[i];
//            update(i);
        }
        update(0);
        while(q--)
        {
            int st, en;
            cin >> st >> en;
            --st; --en;
            cout << get(st, en).maxFreq << '\n';
        }
    }

    return 0;
}