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
struct edge{
    int from, to, cost;
    bool operator < (const edge &e) const{
        return cost > e.cost;
    }
};

int n;
int dist[205];
vector<pair<int, int> > p;
int dijkstra(int src, int dest)
{
    clr(dist, 0x7F);
    priority_queue<edge> pq;
    pq.push({-1, src, 0});
    dist[src] = 0;

    while(!pq.empty())
    {
        edge e = pq.top();
        int u = e.to, c = e.cost;
        pq.pop();

        if (dist[u] < c)
            continue;

        if (u == dest)
            return c;

        for (int v = 0; v < n; ++v)
        {
            int d = max(dist[u], calcDist(p[u], p[v]));
            if (dist[v] > d)
            {
                dist[v] = d;
                pq.push({u, v, dist[v]});
            }
        }
    }
    return -1;
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


        cout << "Scenario #" << t++ << '\n';
        cout << "Frog Distance = " << fixed << setprecision(3) << sqrt(dijkstra(0, 1)) << '\n';
        cout << '\n';
    }
    return 0;
}