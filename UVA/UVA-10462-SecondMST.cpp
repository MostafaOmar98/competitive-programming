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

struct edge{
    int from, to, cost, id;
    edge(int f, int t, int c, int idx) : from(f), to(t), cost(c), id(idx) {}
    bool operator < (const edge& e) const{
        return cost < e.cost;
    }
};


struct UnionFind{
    vector<int> parent;
    vector<int> rank;
    UnionFind(int n)
    {
        parent.resize(n);
        rank.resize(n);
        rep(i,0,n)
        {
            parent[i] = i;
            rank[i] = 1;
        }
    }


    int find_parent(int x)
    {
        if (parent[x] == x)
            return x;
        return parent[x] = find_parent(parent[x]);
    }


    bool union_sets(int x, int y)
    {
        x = find_parent(x), y = find_parent(y);
        if (x == y)
            return false;
        if (rank[x] > rank[y])
            swap(x, y);
        parent[x] = y;
        if (rank[x] == rank[y])
            rank[y]++;
        return true;
    }

};


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
    for (int t = 1; t < tt + 1; ++t)
    {
        cout << "Case #" << t << " : ";
        int n, m;
        cin >> n >> m;
        vector<edge> edgeList;
        rep(i,0,m)
        {
            int x, y, c;
            cin >> x >> y >> c;
            --x; --y;
            edgeList.pb({x, y, c, i});
        }
        sort(all(edgeList));
        vector<edge> tree;
        UnionFind uf(n);
        int bestWay = 0;
        rep(i,0,m)
        {
            if (uf.union_sets(edgeList[i].from, edgeList[i].to))
            {
                tree.pb(edgeList[i]);
                bestWay += edgeList[i].cost;
            }
        }
        if (sz(tree) != n - 1)
        {
            cout << "No way\n";
            continue;
        }

        int ans = INT_MAX;
        rep(i,0,sz(tree)) // try to remove each edge
        {
            int secondBestWay = 0;
            UnionFind secondUF(n);
            rep(j,0,sz(tree))
            {
                if (j == i)
                    continue;
                secondUF.union_sets(tree[j].from, tree[j].to);
                secondBestWay += tree[j].cost;
            }
            bool found = 0;
            rep(j,0,m)
            {
                if (edgeList[j].id == tree[i].id)
                    continue;
                if (secondUF.union_sets(edgeList[j].from, edgeList[j].to))
                {
                    secondBestWay += edgeList[j].cost;
                    found = 1;
                    break;
                }
            }
            if (found)
                ans = min(ans, secondBestWay);
        }
        if (ans == INT_MAX)
            cout << "No second way\n";
        else
            cout << ans << '\n';

    }

    return  0;

}