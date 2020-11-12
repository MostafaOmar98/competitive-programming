/// OLD GO SEE StringHash.cpp


const int MOD[2] = {1000000007, 1000000009};
const int P[2] = {29, 31};
const int MAX_N = 100005;
long long pPow[MAX_N][2], pPowInv[MAX_N][2];

//int MOD[RPL] = {982451653, 982462489, 983898581, 983905843,  983914891, 983923079, 1000000007, 1000000009};
//int prime[RPL] = {461, 463, 607, 71, 73, 89, 311, 313}; // Make sure this prime is greater than the greatest character ID

ll add(ll x, ll y, ll m)
{
    x += y;
    if (x >= m)
        x -= m;
    if (x < 0)
        x += m;
    assert (x >= 0 && x < m);
    return x;
}

ll mult(ll x, ll y, ll m)
{
    return (x * y)%m;
}


ll power(ll base, ll exp, ll m)
{
    ll ret = 1;
    for (; exp; exp >>= 1)
    {
        if (exp&1)
            ret = mult(ret, base, m);
        base = mult(base, base, m);
    }
    return ret;
}

ll modInverse(ll x, ll m)
{
    return power(x, m - 2, m);
}




void preForHash()
{
    rep(t,0,2)
    pPow[0][t] = pPowInv[0][t] = 1;
    for (int i = 1; i < MAX_N; ++i)
    {
        rep(t,0,2)
        {
            pPow[i][t] = mult(pPow[i - 1][t], P[t], MOD[t]);
            pPowInv[i][t] = modInverse(pPow[i][t], MOD[t]);
        }
    }

}


vector<ll> addChar(vector<ll> h, int i, int v)
{
    rep(t,0,2)
    h[t] = add(h[t], mult(pPow[i][t], v, MOD[t]), MOD[t]);
    return h;
}

vector<ll> removeChar(vector<ll> h, int i, int v)
{
    rep(t,0,2)
    h[t] = add(h[t], -1 * mult(pPow[i][t], v, MOD[t]), MOD[t]);
    return h;
}

vector<ll> standardize(vector<ll> h, int i)
{
    rep(t,0,2)
    h[t] = mult(h[t], pPowInv[i][t], MOD[t]);
    return h;
}

/*
 * https://codeforces.com/contest/1200/submission/58666466
 */