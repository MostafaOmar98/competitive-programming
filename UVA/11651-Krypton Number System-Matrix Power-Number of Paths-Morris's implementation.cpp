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

typedef unsigned long long ll;
#define rep(i, start, end) for(int i = start; i < end; ++i)
#define sz(x) (int)(x).size()
#define pb push_back
#define X first
#define Y second
#define all(x) x.begin(), x.end()
#define clr(d, v) memset(d, v, sizeof(d))
#define pii pair<int, int>
const double PI = 3.14159265358979323846;
const double eps = (1e-10);
int dcmp(long double x, long double y)
{
    if (abs(x - y) < eps)
        return 0;
    if (x > y)
        return 1;
    return -1;
}
const unsigned long long mod = 1LLU<<32;
struct Matrix {
    unsigned long long v[200][200];
    int row, col; // row x col
    Matrix(int n, int m, long long a = 0) {
        memset(v, 0, sizeof(v));
        row = n, col = m;
        for(int i = 0; i < row && i < col; i++)
            v[i][i] = a;
    }
    Matrix operator*(const Matrix& x) const {
        Matrix ret(row, x.col);
        for(int i = 0; i < row; i++) {
            for(int k = 0; k < col; k++) {
                if (v[i][k])
                    for(int j = 0; j < x.col; j++) {
                        ret.v[i][j] += v[i][k] * x.v[k][j],
                                ret.v[i][j] %= mod;
                    }
            }
        }
        return ret;
    }
    Matrix operator^(const int& n) const {
        Matrix ret(row, col, 1), x = *this;
        int y = n;
        while(y) {
            if(y&1)	ret = ret * x;
            y = y>>1, x = x * x;
        }
        return ret;
    }
};
int b;
ll s;
vector<vector<int> > adj;

void addDummyNodes(int cnt, int last)
{
    rep(i,0,cnt)
    {
        if (i < cnt - 1)
        {
            adj.push_back({});
            adj.back().push_back(sz(adj));
        }
        else
        {
            adj.push_back({});
            adj.back().push_back(last);
        }
    }
}


void pre()
{
    adj.clear();

    adj.resize(b);
    rep(i,0,b)
    {
        rep(j,0,b)
        {
            int d = (i - j) * (i - j);
            if (d == 0)
                continue;
            else if (d == 1)
                adj[i].push_back(j);
            else
            {
                adj[i].push_back(sz(adj));
                addDummyNodes(d - 1, j);
            }
        }
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
    int T;
    cin >> T;
    int t = 1;
    while(T--)
    {
        cin >> b >> s;
        pre();
        Matrix adjMatrix(sz(adj), sz(adj), 0);
        for (int i = 0; i < sz(adj); ++i)
        {
            for (int to : adj[i])
                adjMatrix.v[i][to] = 1;
        }
        adjMatrix = (adjMatrix^s);
        ll ans = 0;
        rep(i,1,b)
        {
            rep(j,0,b)
            {
                ans += adjMatrix.v[i][j];
                ans %= mod;
            }
        }
        cout << "Case " << t++ << ": ";
        cout << ans << '\n';
    }
    return 0;
}