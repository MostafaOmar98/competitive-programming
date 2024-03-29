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
#define X first
#define Y second
#define all(x) x.begin(), x.end()
#define clr(d, v) memset(d, v, sizeof(d))
#define pii pair<int, int>
const double PI = 3.14159265358979323846;
const double eps = (1e-9);
int dcmp(long double x, long double y)
{
    if (abs(x - y) < eps)
        return 0;
    if (x > y)
        return 1;
    return -1;
}

int calcDist(pii a, pii b)
{
    int diffX = a.X - b.X, diffY = a.Y - b.Y;
    return diffX * diffX + diffY * diffY;
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
    int tc;
    cin >> tc;
    for (int tid = 1; tid <= tc; ++tid)
    {
        int routers, queries;
        cin >> routers >> queries;
        vector<pair<int, int> > v(routers);
        vector<int> r(routers);
        rep(i,0,routers)
        {
            cin >> v[i].X >> v[i].Y;
            cin >> r[i];
        }

        cout << "Case " << tid << ":\n";
        while(queries--)
        {
            bool yes = 0;
            pair<int, int> pos;
            cin >> pos.X >> pos.Y;
            for (int i = 0; i < routers; ++i)
            {
                if (calcDist(pos, v[i]) <= r[i] * r[i])
                {
                    yes = 1;
                    break;
                }
            }
            if (yes)
                cout << "Yes";
            else
                cout << "No";
            cout << '\n';
        }
    }

    return 0;
}