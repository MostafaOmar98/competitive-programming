const int MAX_N = 1000; // keep changing this for verification
int mem[MAX_N];

// your grundy
int grundy(int len)
{
    if (len == 0)
        return 0;
    int &ret = mem[len];
    if (~ret)
        return ret;
    vector<bool> exist(MAX_N + 1);
    for (int i = 0; i < len; ++i)
        exist[grundy(max(0, i - 1)) ^ grundy(max(0, len - (i + 1) - 1))] = true;

    ret = 0;
    while(exist[ret])
        ret++;
    return ret;
}

bool ok(vector<int> v, int len)
{
    vector<int> period;
    for (int i = 0; i < len; ++i)
        period.push_back(v[i]);

    for (int i = 0; i < sz(v); i += len)
    {
        for (int j = 0; i + j < sz(v) && j < len; ++j)
        {
            if (period[j] != v[i + j])
            {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
//    freopen("AC.txt", "w", stdout);
#endif
    clr(mem, -1);
    int last = 0;
    vector<int> v;
    for (int i = 0; i < MAX_N; ++i)
    {
        if (i > 100) // big starting point 3ashan lower values don't cycle sa3at
            v.push_back(grundy(i));
    }

    for (int periodLength = 1; periodLength <= sz(v); ++periodLength)
    {
        if (ok(v, periodLength))
        {
            cout << periodLength << endl;
            return 0;
        }
    }
}