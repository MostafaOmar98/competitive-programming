/*
 * Treat Hash as a mathematical vector, it's convenient way of adding 2 values (for different mods), in your mind just think about one value
 * For whole string hash you only need one "Hash" and keep updating it, h = h[i - 1] + s[i] * ppow[i]
 */


//int MOD[RPL] = {982451653, 982462489, 983898581, 983905843,  983914891, 983923079, 1000000007, 1000000009};
//int prime[RPL] = {461, 463, 607, 71, 73, 89, 311, 313}; // Make sure this prime is greater than the greatest character ID

int MOD[2] = {1000000007, 1000000003};
const int MAX_N = 1e6 + 5, K = 2;

struct Hash{
    int h[K];
    Hash(int x = 0)
    {
        for (int i = 0; i < K; ++i) h[i] = x;
    }
    Hash(const Hash &p) {
        memcpy(h, p.h, sizeof h);
    }
    void operator+=(Hash p) {
        for (int i = 0; i < K; ++i) {
            h[i] += p.h[i];
            if (h[i] >= MOD[i]) h[i] -= MOD[i];
        }
    }
    Hash operator+(Hash p) {
        Hash res = *this;
        for (int i = 0; i < K; ++i) {
            res.h[i] += p.h[i];
            if (res.h[i] >= MOD[i]) res.h[i] -= MOD[i];
        }
        return res;
    }
    Hash operator-(Hash p) {
        Hash res = *this;
        for (int i = 0; i < K; ++i) {
            res.h[i] -= p.h[i];
            if (res.h[i] < 0) res.h[i] += MOD[i];
        }
        return res;
    }
    Hash operator*(int p) {
        Hash res = *this;
        for (int i = 0; i < K; ++i) {
            res.h[i] = res.h[i] * 1ll * p % MOD[i];
        }
        return res;
    }
    Hash operator*(Hash p) {
        Hash res = *this;
        for (int i = 0; i < K; ++i) {
            res.h[i] = res.h[i] * 1ll * p.h[i] % MOD[i];
        }
        return res;
    }
    bool operator==(Hash p) {
        for (int i = 0; i < K; ++i) {
            if (h[i] != p.h[i]) return false;
        }
        return true;
    }
};
int p;
Hash ppow[MAX_N];

// call this
void preHash()
{
    mt19937 rnd = mt19937(chrono::system_clock::now().time_since_epoch().count());
    p = max(129u, rnd() % 65536); // p >= max character
    ppow[0] = 1;
    for (int i = 1; i < MAX_N; ++i)
        ppow[i] = ppow[i - 1] * p;
}

struct AllStringHash{
    vector<Hash> h;

    // if you want to keep hash for all prefixes of string
    void init(const string &s)
    {
        h.clear();
        h.push_back(ppow[0] * s[0]);
        for (int i = 1; i < sz(s); ++i)
            h.push_back(h[i - 1] + ppow[i] * s[i]);
    }

    // if you want to get hash of a segment NOTE this is multiplied by ppow[l]. divide by it if you want it
    Hash get(int l, int r) const
    {
        Hash ret = h[r];
        if (l)
            ret = ret - h[l - 1];
        return ret;
    }

    bool ok(int l, int r) const {
        return l >= 0 && r < sz(h);
    }

    // compare segments
    bool isEqual(int l1, int r1, const AllStringHash &h2, int l2, int r2)
    {
        if (r2 - l2 != r1 - l1 || !ok(l1, r1) || !h2.ok(l2, r2))
            return false;
        Hash a = get(l1, r1), b =  h2.get(l2, r2);
        return (a * ppow[l2] == b * ppow[l1]);
    }
};

