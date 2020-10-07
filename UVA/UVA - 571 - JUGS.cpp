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

string qr[6];
int visit[1005][1005];
int vid;
int parent[1005][1005];
pii parentPair[1005][1005];
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
//    freopen("facebook.txt", "w", stdout);
#endif
    qr[0] = "fill A";
    qr[1] = "fill B";
    qr[2] = "empty A";
    qr[3] = "empty B";
    qr[4] = "pour A B";
    qr[5] = "pour B A";

    int n, a, b;
    while(cin >> a >> b >> n)
    {
        ++vid;
        clr(parent, -1);
        clr(parentPair, -1);
        queue<pii> q;
        visit[0][0] = vid;
        q.push({0, 0});
        int printA, printB = -1;
        for (int size = sz(q); !q.empty() && printB == -1; size = sz(q))
        {
            while(size--)
            {
                int curA = q.front().first, curB = q.front().second;
                q.pop();
                if (curB == n)
                {
                    printA = curA, printB = curB;
                    break;
                }
                int nA, nB;
                nA = a, nB = curB;
                if (visit[nA][nB] != vid)
                {
                    q.push({nA, nB});
                    visit[nA][nB] = vid;
                    parent[nA][nB] = 0;
                    parentPair[nA][nB] = {curA, curB};
                }

                nA = curA, nB = b;
                if (visit[nA][nB] != vid)
                {
                    q.push({nA, nB});
                    visit[nA][nB] = vid;
                    parent[nA][nB] = 1;
                    parentPair[nA][nB] = {curA, curB};
                }

                nA = 0, nB = curB;
                if (visit[nA][nB] != vid)
                {
                    q.push({nA, nB});
                    visit[nA][nB] = vid;
                    parent[nA][nB] = 2;
                    parentPair[nA][nB] = {curA, curB};
                }

                nA = curA, nB = 0;
                if (visit[nA][nB] != vid)
                {
                    q.push({nA, nB});
                    visit[nA][nB] = vid;
                    parent[nA][nB] = 3;
                    parentPair[nA][nB] = {curA, curB};
                }

                int pour = min(b - curB, curA);
                nA = curA - pour, nB = curB + pour;
                if (visit[nA][nB] != vid)
                {
                    q.push({nA, nB});
                    visit[nA][nB] = vid;
                    parent[nA][nB] = 4;
                    parentPair[nA][nB] = {curA, curB};
                }

                pour = min(a - curA, curB);
                nA = curA + pour, nB = curB - pour;
                if (visit[nA][nB] != vid)
                {
                    q.push({nA, nB});
                    visit[nA][nB] = vid;
                    parent[nA][nB] = 5;
                    parentPair[nA][nB] = {curA, curB};
                }
            }
        }

        vector<string> ans;
        while(parent[printA][printB] != -1)
        {
            ans.pb(qr[parent[printA][printB]]);
            pii temp = parentPair[printA][printB];
            printA = temp.first;
            printB = temp.second;
        }
        for (int i = sz(ans) - 1; i>= 0; --i)
            cout << ans[i] << '\n';
        cout << "success\n";
    }

    return  0;

}