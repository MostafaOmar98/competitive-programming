// update MAX_NODES and alphabet size
const int K = 63;

// update Alphabet indexing
inline int getIndex(char c)
{
    if (isalpha(c))
    {
        if (islower(c))
            c -= 'a';
        else
            c = c - 'A' + 26;
    }
    else if (c >= '0' && c <= '9')
        c = c - '0' + 52;
    else
        c = 62;
    return c;
}

struct AhoCorasick{
    struct Node{
        int link, go[K];

        // update collective
        int countVis;
        Node()
        {
            memset(go, 0, sizeof(go));
            link = 0;
            // update collective
            countVis = 0;
        }
    };

    vector<Node> t;
    int addNode()
    {
        t.push_back(Node());
        return sz(t) - 1;
    }

    Node& operator[](int i){
        return t[i];
    }

    vector<int> stringIndex;
    void init(const vector<string> &strs)
    {
        // Might want to reserve with MAX_NODES in constructor
        t.clear();
        addNode();

        stringIndex.clear();
        stringIndex.resize(sz(strs));
        for (int i = 0; i < strs.size(); ++i)
            stringIndex[i] = insert(strs[i]); // update : put colletive of one node information

        pull_info();
    }

    int insert(const string &s) // update : put collective of one node information
    {
        int cur = 0;
        for (char c : s)
        {
            c = getIndex(c);
            if (t[cur].go[c] == 0)
            {
                int x = addNode();
                t[cur].go[c] = x;
            }
            cur = t[cur].go[c];
        }
        // Careful if duplicate strings are allowed. Make sure to add to collective, not just initialize
        // update : collective

        return cur;
    }

    // push_info
//     vector<int> v;

    void pull_info()
    {
        queue<int> q;
        t[0].link = 0;
        // push_info
//         v.push_back(0);

        for (char c = 0; c < K; ++c)
        {
            int &nxt = t[0].go[c];
            if (nxt != 0)
            {
                q.push(nxt);

                // push_info
//                 v.push_back(nxt);
            }
        }

        while(!q.empty())
        {
            int cur = q.front();
            q.pop();

            int curLink = t[cur].link;
            // update collective t[cur].collective += t[curLink].collective


            for (char c = 0; c < K; ++c)
            {
                int &nxt = t[cur].go[c];
                if (nxt == 0)
                    nxt = t[curLink].go[c];
                else
                {
                    q.push(nxt);
                    t[nxt].link = t[curLink].go[c];

                    // push_info
//                     v.push_back(nxt);
                }
            }
        }

        // push_info
//        reverse(v.begin(), v.end());
    }

    // pushes info to nodes in the sequence of suffix links
//    void push_info()
//    {
//        for (int cur : v)
//        {
//            int link = t[cur].link;
//            // update push collective info from cur to get_link(cur). Example: t[link].freq += t[cur].freq;
//            t[link].countVis += t[cur].countVis;
//        }
//    }
}dict;