const int K = 26;
struct Node{
    char ch;
    Node* nxt[K], *go[K], *parent, *link;
    int id;
    int sum;

    Node(Node* parent, char ch, int id) : parent(parent), ch(ch), id(id)
    {
        link = nullptr;
        sum = 0;
        memset(nxt, 0, sizeof(nxt));
        memset(go, 0, sizeof(go));
    }

    ~Node()
    {
        for (char c = 0; c < K; ++c)
            delete nxt[c];
    }
};

struct AhoCorasick{
    Node* head;
    int cnt;
    Node* addNode(Node* parent, char c)
    {
        return new Node(parent, c, cnt++);
    }

    void init(const vector<string> &strs, vector<int> &val)
    {
        delete head;
        head = addNode(0, 0);
        head->parent = head;

        for (int i = 0; i < strs.size(); ++i)
            insert(strs[i], val[i]);

        pull_info();
    }

    // update Alphabet indexing
    int getIndex(char c)
    {
        return c - 'a';
    }

    Node* insert(const string &s, int val)
    {
        Node* cur = head;
        for (char c : s)
        {
            c = getIndex(c);
            if (cur->nxt[c] == nullptr)
                cur->nxt[c] = addNode(cur, c);
            cur = cur->nxt[c];
        }
        cur->sum += val;
        return cur;
    }

    Node* get_link(Node* cur)
    {
        if (cur->link != nullptr)
            return cur->link;
        if (cur == head || cur->parent == head)
            return cur->link = head;
        cur->link = match(get_link(cur->parent), cur->ch);
        return cur->link;
    }

    Node* match(Node* cur, char c)
    {
        if (cur->go[c] != nullptr)
            return cur->go[c];
        if (cur->nxt[c] != nullptr)
            return cur->go[c] = cur->nxt[c];
        if (cur == head)
            return cur->go[c] = head;
        return cur->go[c] = match(get_link(cur), c);
    }
    vector<Node*> topsort()
    {
        vector<Node*> q;
        q.push_back(head);
        for (int i = 0; i < sz(q); ++i)
        {
            Node* u = q[i];
            for (int c = 0; c < K; ++c)
                if (u->nxt[c] != nullptr)
                    q.push_back(u->nxt[c]);
        }
        return q;
    }

    // pulls info from the nodes in the sequence of suffix links
    void pull_info()
    {
        // clear collective ds?
        vector<Node*> q = topsort();
        for (Node* cur : q)
        {
            // update pull collective info from get_link(cur) to cur. Example: freq[cur] += freq[get_link(cur)]
            cur->sum += get_link(cur)->sum;
        }
    }

    // pushes info to nodes in the sequence of suffix links
    void push_info()
    {
        vector<Node*> q = topsort();
        reverse(all(q));
        for (Node* cur : q)
        {
            // update push collective info from cur to get_link(cur). Example: freq[get_link(cur)] += freq[cur];

        }
    }
};