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