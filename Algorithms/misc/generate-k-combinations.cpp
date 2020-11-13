vector<int> ans;
vector<vector<int> > v;
int MAX; // max number of combinations you want
// O(N) * C(N, K)
void gen(int n, int k, int idx, bool rev) {
    if (v.size() >= MAX)
        return;
    if (k > n || k < 0)
        return;

    if (!n) {
        v.push_back({});
        for (int i = 0; i < idx; ++i) {
            if (ans[i])
                v.back().push_back(i + 1);
        }
        return;
    }

    ans[idx] = rev;
    gen(n - 1, k - rev, idx + 1, false);
    ans[idx] = !rev;
    gen(n - 1, k - !rev, idx + 1, true);
}

void all_combinations(int n, int k) {
    ans.resize(n);
    gen(n, k, 0, false);
}
