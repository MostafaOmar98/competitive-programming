// Careful of multiple testcases and creating AhoCorasick each testcase will allocate MAX_NODES memory each testcase
// update MAX_NODES and alphabet size
const int MAX_NODES = 1002, K = 26;
struct AhoCorasick{
    // ch is in [0, K)
    int parent[MAX_NODES], link[MAX_NODES], nxt[MAX_NODES][K], go[MAX_NODES][K], ch[MAX_NODES], cnt;

    // update collective information ds
    int freq[MAX_NODES];

    vector<int> v;
    int addNode(int parentID, char c)
    {
        parent[cnt] = parentID;
        ch[cnt] = c;
        link[cnt] = -1;
        memset(nxt[cnt], -1, sizeof(nxt[cnt]));
        memset(go[cnt], -1, sizeof(go[cnt]));

        // update : clear collective
        freq[cnt] = 0;
        return cnt++;
    }

    void init(const vector<string> &strs)
    {
        cnt = 0;
        addNode(0,0);

        for (int i = 0; i < strs.size(); ++i)
            insert(strs[i]); // update : put colletive of one node information

        pull_info();
    }

    // update Alphabet indexing
    int getIndex(char c)
    {
        return c - 'a';
    }

    int insert(const string &s) // update : put collective of one node information
    {
        int cur = 0;
        for (char c : s)
        {
            c = getIndex(c);
            if (nxt[cur][c] == -1)
                nxt[cur][c] = addNode(cur, c);
            cur = nxt[cur][c];
        }
        // Careful if duplicate strings are allowed. Make sure to add to collective, not just initialize
        // update : collective
        freq[cur]++;
        return cur;
    }

    // returns maximum prefix in the trie that is a proper suffix of node cur
    int get_link(int cur)
    {
        if (!cur || !parent[cur])
            return 0;
        int &ret = link[cur];
        if (~ret)
            return ret;
        ret = match(get_link(parent[cur]), ch[cur]);
        return ret;
    }

    // update : remember input c is in [0, K)
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

    vector<int> topsort()
    {
        vector<int> q;
        q.push_back(0);
        for (int i = 0; i < sz(q); ++i)
        {
            int u = q[i];
            for (int c = 0; c < K; ++c)
                if (nxt[u][c] != -1)
                    q.push_back(nxt[u][c]);
        }
        return q;
    }

    // pulls info from the nodes in the sequence of suffix links
    void pull_info()
    {
        // clear collective ds?
        vector<int> q = topsort();
        for (int cur : q)
        {
            // update pull collective info from get_link(cur) to cur. Example: freq[cur] += freq[get_link(cur)]
            freq[cur] += freq[get_link(cur)];
        }
    }

    // pushes info to nodes in the sequence of suffix links
    void push_info()
    {
        vector<int> q = topsort();
        reverse(all(q));
        for (int cur : q)
        {
            // update push collective info from cur to get_link(cur). Example: freq[get_link(cur)] += freq[cur];
        }
    }
};