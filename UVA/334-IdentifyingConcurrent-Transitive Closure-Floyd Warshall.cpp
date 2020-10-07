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


int id;
map<string, int> ID;
map<int, string> Name;

int getID(const string &s)
{
    auto it = ID.find(s);
    if (it == ID.end())
    {
        Name[id] = s;
        ID[s] = id++;
        return id - 1;
    }
    return it->second;
}
bool canReach[500][500];

void clear()
{
    id = 0;
    clr(canReach, 0);
    ID.clear();
    Name.clear();
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
    int n;
    int t = 1;
    while(cin >> n && n)
    {
        clear();
        for (int i = 0; i < n; ++i)
        {
            int k;
            cin >> k;
            int u;
            string s;
            cin >> s;
            u = getID(s);
            for (int j = 1; j < k; ++j)
            {
                cin >> s;
                int v = getID(s);
                canReach[u][v] = 1;
                u = v;
            }
        }

        int m;
        cin >> m;
        for (int i = 0; i < m; ++i)
        {
            string s1, s2;
            cin >> s1 >> s2;
            int u = getID(s1), v = getID(s2);
            canReach[u][v] = 1;
        }

        for (int i = 0; i < id; ++i)
            canReach[i][i] = 1;

        for (int k = 0; k < id; ++k)
        {
            for (int i = 0; i < id; ++i)
            {
                for (int j = 0; j < id; ++j)
                {
                    canReach[i][j] |= (canReach[i][k] & canReach[k][j]);
                }
            }
        }
        vector<pair<int, int> > ans;
        for (int i = 0; i < id; ++i)
        {
            for (int j = i + 1; j < id; ++j)
            {
                if (!canReach[i][j] && !canReach[j][i])
                {
                    ans.pb({i, j});
                }
            }
        }
        printf("Case %d, ", t++);
        if (!ans.empty())
            printf("%d concurrent events:\n", sz(ans));
        else
            printf("no concurrent events.");

        int end = min(2, sz(ans));
        for (int i = 0; i < end; ++i)
        {
            printf("(%s,%s) ", Name[ans[i].first].c_str(), Name[ans[i].second].c_str());
        }
        printf("\n");
    }
    return 0;
}