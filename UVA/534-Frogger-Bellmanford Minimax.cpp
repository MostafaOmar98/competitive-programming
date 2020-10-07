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
const double eps = (1e-7);
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
    int diffX = a.first - b.first, diffY = a.second - b.second;
    return diffX * diffX + diffY * diffY;
}
int dist[202];
bool inQ[202];
int n;
vector<pair<int, int> > p(n);

int bellman(int src)
{
    clr(dist, 0x7F);
    clr(inQ, 0);

    queue<int> q;
    q.push(src);
    dist[src] = 0;
    inQ[0] = 1;

    for (int cnt = 0; cnt < n; ++cnt)
    {
        int size = sz(q);
        while(size--)
        {
            int u = q.front();
            q.pop();
            for (int v = 0; v < n; ++v)
            {
                int d = max(dist[u], calcDist(p[u], p[v]));
                if (dist[v] > d)
                {
                    dist[v] = d;
                    if (!inQ[v])
                    {
                        q.push(v);
                        inQ[v] = 1;
                    }
                }
            }
        }
        if (!sz(q))
            break;
        if (cnt == n - 1 && sz(q)); // Negative Cycle, nth iteration and still something got relaxed
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
    int t = 1;
    while(cin >> n && n)
    {
        p.clear();
        p.resize(n);
        rep(i, 0, n)
            cin >> p[i].first >> p[i].second;


        bellman(0);
        cout << "Scenario #" << t++ << '\n';
        cout << "Frog Distance = " << fixed << setprecision(3) << sqrt(dist[1]) << '\n';
        cout << '\n';
    }
    return 0;
}