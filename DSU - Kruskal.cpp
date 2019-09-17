typedef struct edge
{
    int from, to, cost;

    edge(int from, int to, int cost) : from(from), to(to), cost(cost)
    {
    }

    bool operator<(const edge &e) const
    {
        return cost < e.cost;
    }

} edge;

struct UnionFind // disjoint set data structure
{
    vector<int> parent;
    vector<int> rank; // height of tree i guess? Only valid when talking about biggest parent, for child nodes it doesn't mean much.
    int forests;

    UnionFind(int n) // initilization, can be same name as struct cuz no typedef
    {
        parent.resize(n);
        rank.resize(n);
        forests = n;
        for (int i = 0; i < n; ++i)
        {
            parent[i] = i;
            rank[i] = 1;
        }
    }

    int find_parent(int x) // finding parent while path compressing
    {
        if (x == parent[x])
            return x;
        return parent[x] = find_parent(parent[x]);
    }

    void link(int x, int y) // linking 2 trees. x & y are both parents
    {
        if (rank[x] > rank[y])
            swap(x, y); // x is the smaller rank

        parent[x] = parent[y];

        if (rank[x] == rank[y]) // I don't understand this bit
            rank[y]++;
    }

    bool union_sets(int x, int y)
    {
        // we only care about parents
        x = find_parent(x);
        y = find_parent(y);

        if (x != y)
        {
            link(x, y);
            forests--;
        }

        return x != y;
    }


    // There are more applications like finding connected components dynamically and other shit
};
