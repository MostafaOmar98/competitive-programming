typedef long double ld;

// Heron's formula
// gets triangle area using 3 sides
ld triangleArea(ld a, ld b, ld c)
{
    ld s = (a + b + c)/2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

// gets triangle area using 3 points
ld triangleArea(Point<ld> a, Point<ld> b, Point<ld> c)
{
    Point<ld> ab = b - a, ac = c - a;
    return 0.5 * fabs(ab.cross(ac));
}
// both can be substitued with any other triangle area form
ld incircleRadius(ld a, ld b, ld c)
{
    ld area = triangleArea(a, b, c);
    return 2 * area/(a + b + c);
}

ld circumcircleRadius(ld a, ld b, ld c)
{
    ld area = triangleArea(a, b, c);
    return a * b * c / (4 * area);
}


// alternative for circumcircleRadius
double circumcircleRadius(const P& A, const P& B, const P& C) {
    return (B-A).dist()*(C-B).dist()*(A-C).dist()/
           abs((B-A).cross(C-A))/2;
}
P circumcircleCenter(const P& A, const P& B, const P& C) {
    P b = C-A, c = B-A;
    return A + (b*c.dist2()-c*b.dist2()).perp()/b.cross(c)/2;
}



