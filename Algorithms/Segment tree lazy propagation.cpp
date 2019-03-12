int n;
const int MAX_N = 100005;
ll tree[4 * MAX_N];
ll lazy[4 * MAX_N];

void check(int p, int l, int r)
{
    if (lazy[p] != 0)
    {
        tree[p] += lazy[p] * (r - l + 1);
        if (l != r)
        {
            lazy[2 * p] += lazy[p];
            lazy[2 * p + 1] += lazy[p];
        }
        lazy[p] = 0;
    }
}

void updateSegment(int a, int b, int p = 1, int l = 0, int r = n - 1)
{
    if (l >= a && r <= b)
    {
        lazy[p]++;
        check(p, l, r);
        return;
    }
    check(p, l, r);
    if (r < a || l > b)
        return;

    updateSegment(a, b, 2 * p, l, (l + r)/2);
    updateSegment(a, b, 2 * p + 1, (l+r)/2 + 1, r);
    tree[p] = tree[2 * p] + tree[2 * p + 1];
}
ll get(int a, int b, int p = 1, int l = 0, int r = n - 1)
{
    check(p, l, r);
    if (l >= a && r <= b)
    {
        return tree[p];
    }
    if (r < a || l > b)
        return 0;

    return get(a, b, 2 * p , l, (l + r)/2) + get(a, b, 2 * p + 1, 1 + (l + r)/2, r);
}
