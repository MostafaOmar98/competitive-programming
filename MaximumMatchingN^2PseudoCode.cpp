
int husband[N];
bool foundMatch(int MID)
{
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