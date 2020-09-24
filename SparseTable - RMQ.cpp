int n;
vector<int> a;
const int MAX_N = 100005, MAX_K = 20;
int table[MAX_N][MAX_K], Log[MAX_N];


void sparsePre()
{
    for (int i = 0; i < n; ++i)
        table[i][0] = a[i];

    for (int j = 1; (1<<j) <= n; ++j)
    {
        int rangeSize = (1<<j);
        for (int i = 0; i + rangeSize - 1 < n; ++i)
            table[i][j] = min(table[i][j - 1], table[i + rangeSize / 2][j - 1]);
    }

    Log[1] = 0;
    for (int size = 2; size <= n; ++size)
        Log[size] = Log[size/2] + 1;
}


int getMin(int st, int en)
{
    int size = en - st + 1, j = Log[size];
    return min(table[st][j], table[en - (1<<j) + 1][j]);
}

//----------------------------------------------------

template <typename T, class F = function<T(const T&, const T&)>>
class SparseTable {
public:
    int n;
    vector<vector<T>> sp;
    F func;

    SparseTable() {}

    void init(const vector<T>& a, const F& f) {
        func = f;
        n = static_cast<int>(a.size());
        int max_log = 32 - __builtin_clz(n);
        sp.resize(max_log);
        sp[0] = a;
        for (int j = 1; j < max_log; ++j)
        {
            sp[j].resize(n - (1 << j) + 1);
            for (int i = 0; i <= n - (1 << j); ++i)
            {
                sp[j][i] = func(sp[j - 1][i], sp[j - 1][i + (1 << (j - 1))]);
            }
        }
    }
    T get(int l , int r) const{
        int lg = 32 - __builtin_clz(r - l + 1) - 1;
        return func(sp[lg][l] , sp[lg][r - (1 << lg) + 1]);
    }
};
