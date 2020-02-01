/*
 * Gives minimum abs(x) + abs(y)
 * Gives x <= y (Whoever has 1 at base case will be minimum)
 * Equations initially assume a > b but seems that it doesn't matter what you give it
 *  at first
 * Careful overflow
 * Can generate more solutions mesh far2a 3and meen el + we 3and meen el -
 * x = x0 - k * a/g
 * y = y0 + k * a/g
 */
void solve(int a, int b, int &x, int &y, int &g)
{
    if (b == 0)
    {
        g = a;
        x = 1;
        y = 0;
        return;
    }

    int x1, y1;
    solve(b, a%b, x1, y1, g);
    x = y1;
    y = x1 - (a/b) * y1;
}
