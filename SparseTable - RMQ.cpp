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