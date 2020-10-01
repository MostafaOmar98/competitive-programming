struct AhoCorasick{
    struct Node{
        int id, pId, msk, suffixLink;
        vector<int> nxt, t; // Doesn't work with arrays?
        char c; // [0, 26];
        Node(int id, int pId, int msk, char c) : id(id), pId(pId), msk(msk), c(c)
        {
//            memset(nxt, -1, sizeof(nxt));
//            memset(t, -1, sizeof(t));
            nxt.resize(26, -1);
            t.resize(26, -1);
            suffixLink = -1;
        }
    };
    AhoCorasick(const vector<string> &strs)
    {
        addNode(0, 0);
        int i = 0;
        for (const string &s : strs)
            insert(s, i++);
        queue<int> q;
        q.push(0);
        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            get_link(u);
            for (int c = 0; c < 26; ++c)
                if (v[u].nxt[c] != -1)
                    q.push(v[u].nxt[c]);
        }
    }
    vector<Node> v;
    int addNode(char c, int pId)
    {
        v.push_back(Node(sz(v), pId, 0, c));
        return (int)(v.size()) - 1;
    }

    void insert(const string &s, int i)
    {
        int cur = 0;
        for (char c : s)
        {
            c -= 'a';
            if (v[cur].nxt[c] == -1)
                v[cur].nxt[c] = addNode(c, cur);
            cur = v[cur].nxt[c];
        }
        v[cur].msk |= (1<<i);
    }

    int get_link(int cur)
    {
        if (!cur || !v[cur].pId)
            return 0;
        int &ret = v[cur].suffixLink;
        if (~ret)
            return ret;
        ret = match(get_link(v[cur].pId), v[cur].c);
        v[cur].msk |= v[ret].msk;
        return ret;
    }
    // char c is [0, 26]
    int match(int cur, char c)
    {
        if (v[cur].nxt[c] != -1)
            return v[cur].nxt[c];
        if (!cur)
            return 0;
        int &ret = v[cur].t[c];
        if (~ret)
            return ret;
        return match(get_link(cur), c);
    }
};