// area of regular polygon using circumcircle radius r
ld regularPolygonArea(ld r, int n)
{
    return  r * r * n * sin(2 * PI / n) / 2;
}

// area of regular polygon using side length s
ld regularPolygonArea(ld s, int n)
{
    return (s * s * n)/(4 * tan(PI/n));
}

// returns double of a simple polygon area (can be non convex) int O(n)
// returns double of the area so it's safe with integers (The only precision error is gonna be the 0.5 when you divide by 2)
template <typename T>
T doublePolygonArea(const vector<Point<T> > &v)
{
    T ret = 0;
    for (int i = 1; i + 1 < sz(v); ++i)
    {
        Point<T> ab = v[i] - v[0], ac = v[i + 1] - v[0];
        ret += ab.cross(ac);
    }
    return abs(ret);
}
