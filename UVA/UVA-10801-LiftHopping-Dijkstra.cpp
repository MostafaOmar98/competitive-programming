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

int n, k;
int t[6];
bool elevatorInFloor[6][105];
int depth[6][105];


struct state{
    int e, f, c;
    bool operator< (const state &other) const{
        return c > other.c;
    }
};

int dijkstra(int goal)
{
    clr(depth, 0x7F);
    priority_queue<state> pq;
    for (int i = 0; i < n; ++i)
    {
        if (elevatorInFloor[i][0])
        {
            pq.push({i, 0, 0});
            depth[i][0] = 0;
        }
    }
    while(!pq.empty())
    {
        state cur = pq.top();
        pq.pop();
        if (cur.c > depth[cur.e][cur.f])
            continue;
        if (cur.f == goal)
            return cur.c;
        for (int flr = 0; flr < 100; ++flr) // switch floors
        {
            if (elevatorInFloor[cur.e][flr])
            {
                if (cur.c + abs(cur.f - flr) * t[cur.e] < depth[cur.e][flr])
                {
                    depth[cur.e][flr] = cur.c + abs(cur.f - flr) * t[cur.e];
                    pq.push({cur.e, flr, depth[cur.e][flr]});
                }
            }
        }
        for (int i = 0; i < n; ++i) // switch elevators
        {
            if (elevatorInFloor[i][cur.f])
            {
                if (cur.c + 60 < depth[i][cur.f])
                {
                    depth[i][cur.f] = cur.c + 60;
                    pq.push({i, cur.f, depth[i][cur.f]});
                }
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
    while(cin >> n >> k)
    {
        clr(elevatorInFloor, 0);
        rep(i, 0, n)
        {
            cin >> t[i];
        }

        string inFloors;
        cin.ignore(32767, '\n');
        rep(i, 0, n)
        {
            getline(cin, inFloors);
            stringstream ss;
            ss << inFloors;
            int f;
            while(ss >> f)
            {
                elevatorInFloor[i][f] = 1;
            }
        }
        int ans = dijkstra(k);
        if (~ans)
            cout << ans;
        else
            cout << "IMPOSSIBLE";
        cout << '\n';
    }
    return  0;

}