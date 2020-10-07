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
    while(tt--)
    {
        int a, b;
        cin >> a >> b;
        int ansX, ansN = INT_MIN;
//        int op = 0;
        for (int X = a; X <= b; ++X)
        {
            int temp = 1;
            int x = X;
            for (int i = 2; i <= x/i; i += 1 + (i&1))
            {
                int cnt = 0;
                while(x%i == 0)
                {
//                    ++op;
                    x /= i;
                    ++cnt;
                }
                if (cnt)
                    temp *= (cnt + 1);
            }
            if (x > 1)
            {
                temp *= 2;
            }
            if (temp > ansN)
            {
                ansN = temp;
                ansX = X;
            }
        }
        printf("Between %d and %d, %d has a maximum of %d divisors.\n", a, b, ansX, ansN);
//        printf("%d\n", op);
    }
    return  0;

}