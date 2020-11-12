vector<vector<int> > v;
vector<bool> isEnd;
vector<int> visitCnt;
int addNode()
{
    v.push_back(vector<int>(26, -1)); // give 26 children
    isEnd.push_back(false); // mark its end
    visitCnt.push_back(1);
    return (int) v.size() - 1; // give this node a unique ID
}
void init() // clean initializing for multiple test cases
{
    v.clear();
    isEnd.clear();
    addNode();
    ans = 0;
}
void insert(string const &s)
{
    int cur = 0; // start from root
    for (int i = 0; i < (int) s.size(); ++i)
    {
        char to = s[i] - 'a'; // to is char index NOT node index
        int &nxt = v[cur][to];
        if (nxt == -1)
        {
            nxt = addNode();
        }
        else
            visitCnt[nxt]++;
// CAREFUL here cur = v[cur][to] NOT to, again to is just char index and NOT v.size(). maybe node exists
        cur = nxt;
    }
    isEnd[cur] = true; // last node is end
}
void remove(string const &s)
{
// Need to add visitCnt vector for removal and make vector<int> isEnd
/*
* vector<vector<int> > visitCnt
* in addNode: visitCnt.push_back(vector<int>(26, 0));
*/
    int cur = 0;
    for (int i = 0; i < sz(s); ++i)
    {
        char to = s[i] - 'a';
        int nxt = v[cur][to];
        visitCnt[cur][to]--;
        if (!visitCnt[cur][to])
            v[cur][to] = -1;
        cur = nxt;
    }
    isEnd[cur]--;
}
bool search(string const &s)
{
    int cur = 0;
    for (int i = 0; i < (int) s.size(); ++i)
    {
        char to = s[i] - 'a';
        if (v[cur][to] == -1)
        {
            return false;
        }
        cur = v[cur][to]; // AGAIN cur = v[cur][to] which is the node number not char index
    }
    return isEnd[cur];
}
// MUCH quicker no overhead in copying s
void printChildren(int cur, int len, char s[]) // takes node ID and prefix and continues printing in all possible paths
{
    if (isEnd[cur])
    {
        s[len] = 0; // don't forget to make s[len] = 0 in all character arrays
        cout << s << '\n';
    }
    for (int i = 0; i < (int) v[cur].size(); ++i)
    {
        if (v[cur][i] != -1)
        {
            s[len] = i + 'a';
            printChildren(v[cur][i], len + 1, s);
        }
    }
}