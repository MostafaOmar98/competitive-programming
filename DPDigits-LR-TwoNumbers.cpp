int a, b;
const int B = 31;
long long mem[B][2][2][2][2];


int getBit(int x, int i){
    return ((x>>i)&1);
}

pair<int, int> get(bool l, bool g, int i){
    int st = 0, en = 1;
    if (getBit(a, i) && !g)
        st = 1;
    if (!getBit(b, i) && !l)
        en = 0;
    return {st, en};
}

long long solve(int i, bool l1, bool g1, bool l2, bool g2)
{
    if (i == -1)
        return 1;
    long long &ret = mem[i][l1][g1][l2][g2];
    if (~ret)
        return ret;
    auto p1 = get(l1, g1, i), p2 = get(l2, g2, i);
    ret = 0;
    for (int x = p1.first; x <= p1.second; ++x){
        for (int y = p2.first; y<=p2.second;++y){
            if (x == 1 && y == 1)
                continue;
            ret += solve(i - 1,
                         l1||x < getBit(b, i),
                         g1||x > getBit(a, i),
                         l2||y < getBit(b, i),
                         g2||y > getBit(a, i));
        }
    }
    return ret;
}