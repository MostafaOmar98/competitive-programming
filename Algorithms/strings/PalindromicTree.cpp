const int K = 26;
int getIndex(char c)
{
    return c - 'a';
}
struct PalindromicTree
{
    struct Node
    {
        int nxt[K], link, len;

        // update collective

        Node(int len) : len(len)
        {
            memset(nxt, 0, sizeof(nxt));
            link = 0;
            // update collective

        }
    };

    string s;
    // update general collective
    // example: frequeny of all palindromes or number of unique palindromes

    vector<Node> t;

    Node &operator[](int i)
    {
        return t[i];
    }

    int addNode(int len)
    {
        t.push_back(Node(len));
        return sz(t) - 1;
    }

    int init(const string &str)
    {
        t.clear();
        addNode(-1);
        addNode(0);
        // update general collective

        s = (char)(0) + str;
        return insert();
    }

    int getNextMatch(int cur, int i)
    {
        while(s[i] != s[i - t[cur].len - 1])
            cur = t[cur].link;
        return cur;
    }

    int insert()
    {
        int cur = 1; // cur is the node representing the longest palindrome suffix so far
        for (int i = 1; i < s.size(); ++i)
        {
            cur = getNextMatch(cur, i);

            char c = getIndex(s[i]);
            if (t[cur].nxt[c] == 0) // a new palindrome appears
            {
                int x = addNode(t[cur].len + 2);
                t[cur].nxt[c] = x;

                if (t[x].len == 1)
                    t[x].link = 1;
                else
                    t[x].link = t[getNextMatch(t[cur].link, i)].nxt[c];

                // update unique/general collective

            }
            cur = t[cur].nxt[c];
            // update duplicate collective and or general collective
            // t[cur].freq++; for example
        }
        push_info();
        return cur;
    }

    void push_info()
    {
        for (int cur = sz(t) - 1; cur >= 1; --cur) // works only in palindromic tree not aho corasick
        {
            // t[link].collective += t[cur].collective
            int link = t[cur].link;

        }
    }

} T;