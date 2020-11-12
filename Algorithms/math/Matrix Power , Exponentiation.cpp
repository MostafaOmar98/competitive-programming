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