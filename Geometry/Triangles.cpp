typedef long double ld;

// Heron's formula
ld triangleArea(ld a, ld b, ld c)
{
    ld s = (a + b + c)/2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
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
