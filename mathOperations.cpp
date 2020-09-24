const int MOD = 1000000007;

ll power(ll base, int exp)
{
    ll ret = 1;
    while(exp)
    {
        if (exp&1)
            ret = mult(ret, base);
        base = mult(base, base);
        exp /= 2;
    }
    return ret;
}

ll modInverse(ll x)
{
    return power(x, MOD - 2);
}

ll div(ll x, ll y)
{
    return mult(x, modInverse(y));
}

int findSign(int x)
{
    if (x == 0)
        return 0;
    return x < 0 ? -1 : 1;
}

pair<int, int> handleFraction(int a, int b)
{
    if (b == 0)
        return {1, 0}; // DO YOU NEED SIGN HERE? In slopes -1, 0 is same as 1, 0
    if (a == 0)
        return {0, 1}; // Does it need findSign(b)?? is sloe {0, -1} same as slope {0, 1}?
    int div = __gcd(abs(a), abs(b));
    a /= div;
    b /= div;
    int sign = findSign(a) * findSign(b);
    return {sign * abs(a), abs(b)};
}
// ax + by = gcd(a, b)
/*
 * solves modInverse as x from extended_euclid(a, m) is the modinverse of a under m (Valid only when gcd(a, m) == 1)
 */
ll extended_euclid(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    ll g = extended_euclid(b, a % b, y,x);
    y -= (a/b) * x;
    return g;
}



// line defined by by - ax + c = 0
struct line{
    ll a, b, c;
    line()
    {
        a = 0, b = 0, c = 0;
    }
    line (ll _a, ll _b, ll _c)
    {
        a = _a;
        b = _b;
        c = _c;
    }
    bool operator < (const line &other) const
    {
        if (a != other.a)
            return a < other.a;
        if (b != other.b)
            return b < other.b;
        return c < other.c;
    }
    bool operator == (const line &other) const
    {
        return a == other.a && b == other.b && c == other.c;
    }

};
line makeLine(pair<ll, ll> p1, pair<ll, ll> p2)
{
    ll a = p1.Y - p2.Y, b = p1.X - p2.X;
    pair<ll, ll> temp = handleFraction(a, b); // handleFraction here must return {1,0} in case b == 0
    a = temp.first, b = temp.second;
    ll c = -1LL * b * p1.Y + 1LL * a * p1.X;
    a *= -1;
    line ret(a, b, c);
    return ret;

}


pair<ll, ll> getSlope(line l)
{
    return handleFraction(l.a, l.b);
}

// quick inverse by NourElDin, I don't understand
void buildInverse()
{
    invi[1] = 1;
    for (int i = 2; i < MAX; i++)
    {
        invi[i] = mod - mul(mod / i, invi[mod % i]);
        assert(mul(i, invi[i]) == 1);
    }
}

typedef complex<int> point;
#define dp(a, b) ((conj(a) * b).real())
#define cp(a, b) ((conj(a) * b).imag())
#define angle(a) (atan2(a.imag(), a.real()))
#define rotate0(a, angle) (a * exp(point(0, angle)))
#define length(a) (hypot(a.imag(), a.real()))
#define rotateAr(a, angle, around) (rotate0(((a) - (around)),(angle)) + around)
#define reflect(a, m) (conj((a)/(m)) * (m))
#define normalize(a) ((a) / length(a));



// hash set
// if you want to hash string using this hash the pair (i, a[i])
// ull hash(pii a) {return mix(a.first ^ mix(a.second));}

typedef unsigned long long ull;
ull TIME = chrono::steady_clock::now().time_since_epoch().count();
ull mix(ull o)
{
    o ^= TIME;
    o += 0x9e3779b97f4a7c15;
    o = (o ^ (o >> 30)) * 0xbf58476d1ce4e5b9;
    o = (o ^ (o >> 27)) * 0x94d049bb133111eb;
    return o ^ (o >> 31);
}



int main()
{
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<> uniform(0, n);
    return 0;
}