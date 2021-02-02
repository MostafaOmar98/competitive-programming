#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

using namespace std;
using namespace __gnu_pbds;

template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#ifdef LOCAL
#define debug(...) debug_out(vec_splitter(#__VA_ARGS__), 0, __LINE__, __VA_ARGS__)
#else
#define debug(...) ;
#endif

vector<string> vec_splitter(string s)
{
    s += ',';
    vector<string> res;
    while (!s.empty())
    {
        res.push_back(s.substr(0, s.find(',')));
        s = s.substr(s.find(',') + 1);
    }
    return res;
}

void debug_out(
        vector<string> __attribute__ ((unused)) args,
        __attribute__ ((unused)) int idx,
        __attribute__ ((unused)) int LINE_NUM)
{
    cerr << endl;
}

template<typename Head, typename... Tail>
void debug_out(vector<string> args, int idx, int LINE_NUM, Head H, Tail... T)
{
    if (idx > 0)
        cerr << ", ";
    else
        cerr << "Line(" << LINE_NUM << ") ";
    stringstream ss;
    ss << H;
    cerr << args[idx] << " = " << ss.str();
    debug_out(args, idx + 1, LINE_NUM, T...);
}

typedef long long ll;
typedef long double ld;
#define rep(i, start, end) for(int i = start; i < end; ++i)
#define sz(x) (int)((x).size())
#define pb push_back
#define all(x) x.begin(), x.end()
#define clr(d, v) memset(d, v, sizeof(d))
#define pii pair<int, int>
#define X first
#define Y second
//#define debug(x) cerr << #x << " : " << (x) << " "
const long double PI = 3.14159265358979323846;
const long double eps = (1e-15);
enum
{
    LESS, EQUAL, GREATER
};

int dcmp(ld x, ld y, ld EPS = eps)
{
    if (fabs(x - y) <= EPS)
        return EQUAL;
    return x > y ? GREATER : LESS;
}
int nMales, nFemales;
const int MAX_N = 1500 + 5;
vector<int> adj[MAX_N]; // adj[male] -> female

int husband[MAX_N]; // husband[female] -> male
int vis[MAX_N], vid; // vis[male] -> vid;
int wife[MAX_N];
int foundMatch(int male)
{
    if (vis[male] == vid)
        return 0;
    vis[male] = vid;
    for (int v : adj[male])
    {
        if (husband[v] == -1)
        {
            husband[v] = male;
            wife[male] = v;
            return 1;
        }
    }


    for (int v : adj[male])
    {
        if (foundMatch(husband[v]))
        {
            husband[v] = male;
            wife[male] = v;
            return 1;
        }
    }
    return 0;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int tempHusband[MAX_N];
int maximumMatching()
{
    memset(husband, -1, nFemales * sizeof(husband[0]));
    memset(wife, -1, nMales * sizeof(wife[0]));

    for (int i = 0; i < nMales; ++i)
        shuffle(all(adj[i]), rng);

    vector<int> maleIDs;
    maleIDs.resize(nMales);
    iota(maleIDs.begin(), maleIDs.end(), 0);
    shuffle(maleIDs.begin(), maleIDs.end(), rng);

    int ok = 1;
    while(ok--)
    {
        ++vid;
        for (int male : maleIDs)
            if (wife[male] == -1)
                ok |= foundMatch(male);
    }

    int ans = 0;
    for (int male : maleIDs)
        ans += wife[male] != -1;

    // Regular algo finished
    // start adding extras
    // This is okay because:
    // 1- The algorithm doesn't start visiting/traversing the male nodes in foundMatch until it has been called atleast once
    // from outside
    // 2- The algorithm finds an arbitrary maximum matching. Thus, it can continue from any arbitrary maximum matching.
    // 3- The algorithm never messes an old matching. I.e. if we call foundMatch on a new male, the matching without this
    // male stays maximum. i.e. call foundMatch(male) so it changes some links then decrement ans and remove the new match,
    // the rest of the matches will be the maximum for the rest of the graph.

    wife[nMales++] = -1;
    wife[nMales++] = -1;
    int best = ans;
    for (int i = 0; i < nMales - 2; ++i)
    {
        int tempAns = ans;
        // --------------------- WAY 1
//        adj[nMales - 2] = adj[i];
//        adj[nMales - 1] = adj[i];
//
//        // In this point we found maximum matching for males in range [0, nMales - 2)
//        // Now we start calling on nMales-2 and nMales-1 as if by chance they were at the end of the maleIDs vector.
//
//        ++vid;
//        ans += foundMatch(nMales - 2);
//        ++vid;
//        ans += foundMatch(nMales - 1);
//        // undoing the effect of last 2 nodes so that the arbitrary maximum matching stays for males in range [0, nMales - 2)
//        if (wife[nMales - 1] != -1)
//            husband[wife[nMales - 1]] = -1;
//        if (wife[nMales - 2] != -1)
//            husband[wife[nMales - 2]] = -1;


        // ------------ WAY 2

        // another way to do this instead of copying adj is to do
        // ans += foundMatch(i) twice, this will add new match from some female to i if possible
        // but you will have to copy the checkpoint husband state every time in the loop to undo the wives attached to i
//        memcpy(tempHusband, husband, nFemales * sizeof(husband[0]));
//        ++vid;
//        ans += foundMatch(i);
//        ++vid;
//        ans += foundMatch(i);
//        memcpy(husband, tempHusband, nFemales * sizeof(husband[0]));


        // ------------ WAY 3
        // Since any arbitrary match is okay, you just need to undo the new wives attached to i
        vector<int> newWives;
        ++vid;
        ans += foundMatch(i);
        newWives.push_back(wife[i]);
        ++vid;
        ans += foundMatch(i);
        newWives.push_back(wife[i]);

        if (ans != tempAns)
        {
            for (int w : newWives)
                husband[w] = -1;
        }


        best = max(best, ans);

        ans = tempAns;
    }

    return best;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
#endif
    int m;
    cin >> nMales >> nFemales >> m;
    rep(i,0,m)
    {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].push_back(v);
    }

    cout << maximumMatching() << '\n';
}