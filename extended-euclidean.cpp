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
 *  very important in division ceil, floor the sign.
 *  handle zeros indepedently.
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
    if (b > a) // b is smaller now
    {
        // if you don't wanna do this you gotta add the if condition for a == 0;
        swap(a, b);
        swap(x1, y1);
        swap(x2, y2);
    }
    if (a == 0 && b == 0)
    {
        if (c == 0)
            return 1LL * (x2 - x1 + 1) * (y2 - y1 + 1);
        else
            return 0;
    }
    else if (b == 0)
    {
        if (c%a != 0)
            cout << 0 << '\n';
        else
        {
            long long x = c/a;
            if (x >= x1 && x <= x2)
                return 1LL * (y2 - y1 + 1);
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