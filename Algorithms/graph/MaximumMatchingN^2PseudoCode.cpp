int husband[N];
int vis[N], vid; // vid for maximum matching increment
bool foundMatch(int MID)
{
    vis[MID] = vid;
    for (auto to : adj[MID])
    {
        if (husband[to] == -1)
        {
            husband[to] = MID;
            return 1;
        }
        else if (vis[husband[to]] != vid && foundMatch(husband[to]))
        {
            husband[to] = MID;
            return 1;
        }
    }
    return 0;
}

int maxMatch()
{
    int ans = 0;
    for (int i = 0; i < Males; ++i)
    {
        ++vid;
        ans += foundMatch(i);
    }
    return ans;
}


// EXAMPLE -- TLED on library checker but passed all of rest testcases

int nMales, nFemales;
const int MAX_N = 1e5 + 5;
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
int maximumMatching()
{
    memset(husband, -1, nFemales * sizeof(husband[0]));
    vector<int> maleIDs(nMales);
    iota(maleIDs.begin(), maleIDs.end(), 0);
    shuffle(maleIDs.begin(), maleIDs.end(), rng);

    for (int male : maleIDs)
        shuffle(adj[male].begin(), adj[male].end(), rng);

    int ans = 0;
    for (int male : maleIDs)
    {
        ++vid;
        ans += foundMatch(male);
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#else
    //    freopen("grand.in", "r", stdin);
//    freopen("grand.out", "w", stdout);
#endif
    cin >> nMales >> nFemales;
    int m;
    cin >> m;
    while(m--)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v); // edge from male to female
    }

    cout << maximumMatching() << '\n';
    for (int female = 0; female < nFemales; ++female)
    {
        if (husband[female] != -1)
            cout << husband[female] << " " << female << '\n';
    }
}