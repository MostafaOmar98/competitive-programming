long double to_deg(ld angle)
{
    return angle * 180.0 / PI;
}

int sign(int x)
{
    if (!x)
        return 0;
    return x > 0 ? 1 : -1;
}

struct Point{
    int x, y;
    void normalize()
    {
        // (0, 0)?
        if (x == 0)
            y = sign(y); // sign matters?
        else if (y == 0)
            x = sign(x); // sign matters?
        else
        {
            int d = __gcd(abs(x), abs(y));
            x /= d;
            y /= d;
        }
    }
    int getQuad() const {
        if (x >= 0)
            return y >= 0 ? 0 : 3;
        return y >= 0 ? 1 : 2;
    }
    int cross (Point other) const{
        return x * other.y - y * other.x;
    }
    int dot(Point other) const {
        return x * other.x + y * other.y;
    }
    int len2() const {
        return dot((*this));
    }
    bool operator<(const Point &other) const {
        int q1 = getQuad(), q2 = other.getQuad();
        if (q1 != q2) {
            return q1 < q2;
        }
        auto c = cross(other);
        if (c == 0) { // both on same ray, return the closer to the origin
            return len2() < other.len2();
        }
        return c > 0;
    }
    bool operator == (const Point &other) const{
        return getQuad() == other.getQuad() && cross(other) == 0;
    }
    ld getAngleTo(Point other) const{
        ld ret = atan2(cross(other), dot(other));
        if (ret < 0)
            ret += 2 * PI;
        return to_deg(ret);
    }

    int distSq(Point p) const{
        int dx = x - p.x, dy = y - p.y;
        return dx * dx + dy * dy;
    }
    ld dist(Point p) const{
        return sqrt(distSq(p));
    }
    long double getDegrees() const{
        long double ret = atan2(y, x);
        if (ret < 0)
            ret += 2 * PI;
        return to_deg(ret);
    }
    friend istream& operator>>(istream& in, Point &p) {
        in >> p.x >> p.y;
        return in;
    }
};
