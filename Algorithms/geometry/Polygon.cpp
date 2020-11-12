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