/*
 * Gives minimum abs(x) + abs(y)
 * Gives x <= y (Whoever has 1 at base case will be minimum) Eshat3'elt fe mas2ala
 *  then doesn't seem to work in the general case
 * Equations initially assume a > b but seems that it doesn't matter what you give it
 *  at first
 * Careful overflow
 * Can generate more solutions mesh far2a 3and meen el + we 3and meen el -
 * x = x0 - k * a/g
 * y = y0 + k * a/g
 */

/*
 * Notes:
 * This is the only correct way to do ceilDiv and floorDiv for positive and negative
 *  numbers. Other AC's with other ones are most probably luck or weak testcases
 *
 *  Always Long long everywhere fel masa2el deh. Too hard to catch overflow
 *
 *  abstract find_any_solution. get answer for positive a, b and change x's accordingly
 *
 *  low, high depends on sign of a, and b. keep g always positive.
 *  very important in inequalities, must be sure of signs of el 7agat ely betdrab feha
 *   otherwise need if condition in case you will flip the inequality
 *
 *  very important in division ceil, floor the sign.
 *
 *  handle zeros indepedently.
 *
 *  Extended Euclidean gives x, y such that abs(x, y) <= abs(a, b). (Not accurate but
 *   for overflow purposes)
 */

int sign(long long x)
{
    if (!x)
        return x;
    return x >= 0 ? 1 : -1;
}

long long ceilDiv(long long a, long long b)
{
    long long ret = a/b;
    if (ret * b != a && sign(a) * sign(b) == 1)
        ret++;
    return ret;
}

long long floorDiv(long long a, long long b)
{
    long long ret = a/b;
    if (ret * b != a && sign(a) * sign(b) == -1)
        ret--;
    return ret;
}

void solve(long long a, long long b, long long &x, long long &y, long long &g)
{
    if (b == 0)
    {
        g = a;
        x = 1;
        y = 0;
        return;
    }

    long long x1, y1;
    solve(b, a%b, x1, y1, g);
    x = y1;
    y = x1 - floorDiv(a, b) * y1; // allowed floor division this way 3ashan a, b always positive
}

bool find_any_solution(long long a, long long b, long long c, long long &x0, long long &y0, long long &g) {
    solve(abs(a), abs(b), x0, y0, g);
    if (a == 0 && b == 0)
    {
        if (c != 0)
            return false;
        x0 = y0 = g = 0; // arbitrary x0, y0. infinite number of solutions
        return true;
    }

    if (c % g)
        return false;

    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}

long long findNumberOfSolutions(long long a, long long b, long long c, long long x1, long long x2, long long y1, long long y2)
{
    if (a == 0 && b == 0)
    {
        if (c == 0)
            return (x2 - x1 + 1) * (y2 - y1 + 1);
        else
            return 0;
    }
    else if (b == 0)
    {
        if (c%a != 0)
            return 0;
        else
        {
            long long x = c/a;
            if (x >= x1 && x <= x2)
                return y2 - y1 + 1;
            else
                return 0;
        }
    }
    else if (a == 0)
    {
        if (c%b != 0)
            return 0;
        else
        {
            long long y = c/b;
            if (y >= y1 && y <= y2)
                return x2 - x1 + 1;
            else
                return 0;
        }
    }
    else
    {
        long long x0, y0;
        long long g;
        if (!find_any_solution(a, b, c, x0, y0, g))
            return 0;

        long long l1, h1, l2, h2;

        if (b >= 0)
            l1 = ceilDiv(g * (x1 - x0), b), h1 = floorDiv(g * (x2 - x0), b);
        else
            l1 = ceilDiv(g * (x2 - x0), b), h1 = floorDiv(g * (x1 - x0), b);

        if (a >= 0)
            l2 = ceilDiv(g * (-y2 + y0), a), h2 = floorDiv(g * (-y1 + y0), a);
        else
            l2 = ceilDiv(g * (-y1 + y0), a), h2 = floorDiv(g * (-y2 + y0), a);

        long long l = max(l1, l2), h = min(h1, h2);
        if (l > h)
            return 0;
        else
            return h - l + 1;
    }
    assert(0);
    return -1;
}


// number of solutions copied from cp-algorithms
void shift_solution(int & x, int & y, int a, int b, int cnt) {
    x += cnt * b;
    y -= cnt * a;
}

int find_all_solutions(int a, int b, int c, int minx, int maxx, int miny, int maxy) {
    int x, y, g;
    if (!find_any_solution(a, b, c, x, y, g))
        return 0;
    a /= g;
    b /= g;

    int sign_a = a > 0 ? +1 : -1;
    int sign_b = b > 0 ? +1 : -1;

    shift_solution(x, y, a, b, (minx - x) / b);
    if (x < minx)
        shift_solution(x, y, a, b, sign_b);
    if (x > maxx)
        return 0;
    int lx1 = x;

    shift_solution(x, y, a, b, (maxx - x) / b);
    if (x > maxx)
        shift_solution(x, y, a, b, -sign_b);
    int rx1 = x;

    shift_solution(x, y, a, b, -(miny - y) / a);
    if (y < miny)
        shift_solution(x, y, a, b, -sign_a);
    if (y > maxy)
        return 0;
    int lx2 = x;

    shift_solution(x, y, a, b, -(maxy - y) / a);
    if (y > maxy)
        shift_solution(x, y, a, b, sign_a);
    int rx2 = x;

    if (lx2 > rx2)
        swap(lx2, rx2);
    int lx = max(lx1, lx2);
    int rx = min(rx1, rx2);

    if (lx > rx)
        return 0;
    return (rx - lx) / abs(b) + 1;
}


//----------------------------
// tourist code avoids overflow

long long mulmod(long long a, long long b, long long c) {
    long long sign = 1;
    if (a < 0) {
        a = -a;
        sign = -sign;
    }
    if (b < 0) {
        b = -b;
        sign = -sign;
    }
    a %= c;
    b %= c;
    long long res = 0;
    while (b > 0) {
        if (b & 1) {
            res = (res + a) % c;
        }
        a = (a + a) % c;
        b >>= 1;
    }
    if (sign == -1) {
        res = (-res) % c;
    }
    return res;
}

template<typename T>
T extgcd(T a, T b, T &x, T &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    T p = b / a;
    T g = extgcd(b - p * a, a, y, x);
    x -= p * y;
    return g;
}

template<typename T>
bool diophantine(T a, T b, T c, T &x, T &y, T &g) {
    if (a == 0 && b == 0) {
        if (c == 0) {
            x = y = g = 0;
            return true;
        }
        return false;
    }
    if (a == 0) {
        if (c % b == 0) {
            x = 0;
            y = c / b;
            g = abs(b);
            return true;
        }
        return false;
    }
    if (b == 0) {
        if (c % a == 0) {
            x = c / a;
            y = 0;
            g = abs(a);
            return true;
        }
        return false;
    }
    g = extgcd(a, b, x, y);
    if (c % g != 0) {
        return false;
    }
    T dx = c / a;
    c -= dx * a;
    T dy = c / b;
    c -= dy * b;
    x = dx + mulmod(x, c / g, b);
    y = dy + mulmod(y, c / g, a);
    g = abs(g);
    return true;
}