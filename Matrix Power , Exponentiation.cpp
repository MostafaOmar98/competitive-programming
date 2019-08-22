
const int MOD = 1000000007;
ll mod(ll x)
{
    return (x%MOD + MOD)%MOD;
}

ll mult(ll x, ll y)
{
    return (x%MOD * y%MOD)%MOD;
}

ll add(ll x, ll y)
{
    return (x%MOD + y%MOD)%MOD;
}

#define Matrix vector<vector<ll> >

Matrix makeMatrix(int r, int c)
{
    Matrix ret(r, vector<ll>(c));
    return ret;
}

Matrix makeIdentity(int r, int c)
{
    Matrix ret = makeMatrix(r, c);
    rep(i,0,r)
    ret[i][i] = 1;
    return ret;
}

Matrix addMatrix(const Matrix &a, const Matrix &b)
{
//    assert(sz(a) && sz(a) == sz(b) && sz(a[0]) == sz(b[0])); // has atleast one row, and a.dimensions = b.dimensions
    Matrix ret = makeMatrix(sz(a), sz(a[0]));

    for (int i = 0; i < sz(ret); ++i)
        for (int j = 0; j < sz(ret[i]); ++j)
            ret[i][j] = add(a[i][j], b[i][j]);
}

Matrix multMatrix(const Matrix &a, const Matrix &b)
{
//    assert(sz(a) && sz(a[0]) == sz(b)); // has atleast one row and a.col = b.row
    Matrix ret = makeMatrix(sz(a), sz(b[0]));

    for (int i = 0; i < sz(ret); ++i)
        for (int j = 0; j < sz(ret[i]); ++j)
            for (int k = 0; k < sz(b); ++k)
                ret[i][j] = add(ret[i][j], mult(a[i][k], b[k][j])); // DOING LESS MODS here helps immensly in timelimit, consider writing it manually if a[i][k] and b[k][j] already come modded

    return ret;
}

Matrix powerMatrix(Matrix base, ll exp)
{
//    assert(sz(base));
    Matrix ret = makeIdentity(sz(base), sz(base[0]));

    for (; exp; exp >>= 1)
    {
        if (exp&1)
            ret = multMatrix(ret, base);
        base = multMatrix(base, base);
    }
    return ret;
}

void printMatrix(const Matrix &a)
{
    for (int i = 0; i < sz(a); ++i)
    {
        for (int j = 0; j < sz(a[i]); ++j)
            cout << a[i][j] << ' ';
        cout << '\n';
    }
    cout << '\n';
}
void reset(Matrix x)
{
    rep(i,0,sz(x))
    {
        rep(j,0,sz(x[i]))
            x[i][j] = 0;
    }
}

/*
 * construct Matrix with base cases, know your transitions on paper then construct transformer matrix,
 * get transformer^n and CAREFUL of order of multiplication
 */

/*
 * You can think in 2 transition matrices or more, final transition matrix = Multiplication of all your transition matrices
 */


// Morris's much quicker implementation


const unsigned long long mod = 1LLU<<32;
struct Matrix {
    unsigned long long v[200][200];
    int row, col; // row x col
    Matrix(int n, int m, long long a = 0) {
        memset(v, 0, sizeof(v));
        row = n, col = m;
        for(int i = 0; i < row && i < col; i++)
            v[i][i] = a;
    }
    Matrix operator*(const Matrix& x) const {
        Matrix ret(row, x.col);
        for(int i = 0; i < row; i++) {
            for(int k = 0; k < col; k++) {
                if (v[i][k])
                    for(int j = 0; j < x.col; j++) {
                        ret.v[i][j] += v[i][k] * x.v[k][j],
                                ret.v[i][j] %= mod;
                    }
            }
        }
        return ret;
    }
    Matrix operator^(const long long& n) const {
        Matrix ret(row, col, 1), x = *this;
        long long y = n;
        while(y) {
            if(y&1)	ret = ret * x;
            y = y>>1, x = x * x;
        }
        return ret;
    }
};