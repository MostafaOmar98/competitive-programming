long long modinverse(long long a, long long b, long long s0 = 1, long long s1 = 0) { return b == 0 ? s0 : modinverse(b, a % b, s1, s0 - s1 * (a / b)); }
long long gcd(long long a, long long b) { return b == 0 ? a : gcd(b, a % b); }
long long mul(long long a, long long b, long long m) {
    long long q = (long double) a * (long double) b / (long double) m;
    long long r = a * b - q * m;
    return (r + m) % m;
}

struct Equation {
    Equation(long long a, long long m, bool valid = true) { mod = m, ans = a, this->valid = valid; }
    Equation() { valid = false; }
    Equation(Equation a, Equation b) {
        if(!a.valid || !b.valid) {
            valid = false;
            return;
        }
        long long g = gcd(a.mod, b.mod);
        if((a.ans - b.ans) % g != 0) {
            valid = false;
            return;
        }
        valid = true;
        mod = a.mod * (b.mod / g);
        ans = a.ans +
              mul(
                      mul(a.mod, modinverse(a.mod, b.mod), mod),
                      (b.ans - a.ans) / g
                      , mod);
        ans = (ans % mod + mod) % mod;
    }
    long long mod, ans;
    bool valid;
};

Equation CRT(vector<int> a, const vector<int> &m)
{
    if (a.empty()) // what to return here?
        Equation(0,0,false);

    assert(a.size() == m.size());

    for (int i = 0; i < a.size(); ++i)
        a[i] %= m[i];

    Equation last(a[0], m[0]);
    for (int i = 1; i < a.size(); ++i)
    {
        Equation cur(a[i], m[i]);
        last = Equation(last, cur);
    }
    return last;
}