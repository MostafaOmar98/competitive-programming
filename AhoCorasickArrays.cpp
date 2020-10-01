// Careful of multiple testcases and creating AhoCorasick each testcase will allocate MAX_NODES memory each testcase
struct AhoCorasick{
    // Asasy
    // ch is in [0, k)
    int parent[MAX_NODES], link[MAX_NODES], nxt[MAX_NODES][K], go[MAX_NODES][K], ch[MAX_NODES], cnt;
    // collective information
    int msk[MAX_NODES];

    int addNode(int parentID, char c, int m)
    {
        // asasy
        parent[cnt] = parentID;
        ch[cnt] = c;
        link[cnt] = -1;
        memset(nxt[cnt], -1, sizeof(nxt[cnt]));
        memset(go[cnt], -1, sizeof(go[cnt]));

        // collective
        msk[cnt] = m;

        return cnt++;
    }

    void init(const vector<string> &strs)
    {
        cnt = 0;
        addNode(0,0,0);

        for (int i = 0; i < strs.size(); ++i)
            insert(strs[i], (1<<i)); // insert(string, One node information)

        // must calculate the collective information here
        // I use get_link as a dp to calculate it, this bfs is just a topological sorting of states
        queue<int> q;
        q.push(0);
        while(!q.empty())
        {
            int cur = q.front();
            q.pop();
            get_link(cur);
            for (int c = 0; c < 26; ++c)
                if (nxt[cur][c] != -1)
                    q.push(nxt[cur][c]);
        }
    }

    void insert(const string &s, int m)
    {
        int cur = 0;
        for (char c : s)
        {
            c -= 'a';
            if (nxt[cur][c] == -1)
                nxt[cur][c] = addNode(cur, c, 0);
            cur = nxt[cur][c];
        }
        // Careful if duplicate strings are allowed. Make sure to add to collective, not just initialize
        msk[cur] |= m;
    }

    // returns maximum prefix in the trie that is a proper suffix of node cur
    // behaves also as a dp to calculate the collective info. Dependencies must be calculated first
    int get_link(int cur)
    {
        if (!cur || !parent[cur])
            return 0;
        int &ret = link[cur];
        if (~ret)
            return ret;
        ret = match(get_link(parent[cur]), ch[cur]);
        // update collective
        msk[cur] |= msk[ret];

        return ret;
    }

    // c is in [0, K)
    // returns maximum prefix in the trie that is also a suffix of cur with c appended to it
    int match(int cur, char c)
    {
        if (nxt[cur][c] != -1)
            return nxt[cur][c];
        if (!cur)
            return 0;
        int &ret = go[cur][c];
        if (~ret)
            return ret;
        return match(get_link(cur), c);
    }
};