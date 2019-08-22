
int n, Q;
const int S = 67; // MAX_N/sqrt(MAX_Q)
struct Query{
    int l, r, idx;

    inline pair<int, int> toPair() const
    {
        return make_pair(l/S, (l/S) & 1 ? -r : r);
    }

    bool operator < (const Query &other) const
    {
        return this->toPair() < other.toPair();
    }
};

const int MAX_N = 3e4 + 5, MAX_Q = 2e5 + 5, MAX_E = 1e6 + 5; // CHANGE
int a[MAX_N], freq[MAX_E];
Query vq[MAX_Q];
int ans[MAX_Q], tempAns; // Long long?

void add(int x)
{
    freq[x]++;
    tempAns += (freq[x] == 1);
}

void rmv(int x)
{
    tempAns -= (freq[x] == 1);
    freq[x]--;
}

void mo()
{
    sort(vq, vq + Q); // modify indices before sorting
    int cl = 0, cr = -1; // 1 based?
    for (int i = 0; i < Q; ++i)
    {
        int l = vq[i].l, r = vq[i].r, idx = vq[i].idx;
        while (cl > l)
            add(a[--cl]);
        while(cr < r)
            add(a[++cr]);
        while (cl < l)
            rmv(a[cl++]);
        while(cr > r)
            rmv(a[cr--]);
        ans[idx] = tempAns;
    }
}