
const long double EPS = 1e-10;


bool areEqual(long double x, long double y, long double eps = EPS) {
    auto diff = abs(x - y);
    x = abs(x), y = abs(y);
    if (diff <= eps) return true;
    if (min(x, y) <= eps) return false;
    return diff <= eps * max(x, y);
}
enum Relation { LESS_THAN, EQUAL, GREATER_THAN };
// SUPER SLOW
int compareDoubles(long double x, long double y, long double eps = EPS) {
    if (areEqual(x, y, eps)) return Relation::EQUAL; // CHANGE TO abs(x - y) <= eps for fastness
    if (x < y) return Relation::LESS_THAN;
    return Relation::GREATER_THAN;
}

bool isZero(long double x, long double eps = EPS) { return abs(x) <= eps; }
template <class T>
struct Point {
    typedef Point P;
    const static P Invalid;
    const static P Origin;

    T x = 0, y = 0;
    Point(T x, T y) : x(x), y(y) {}
    Point() {}
    pair<T, T> to_pair() const { return make_pair(x, y); }
    Point operator+(const Point& p) const { return Point{x + p.x, y + p.y}; }
    Point operator-(const Point& p) const { return Point{x - p.x, y - p.y}; }
    Point operator*(T c) const { return Point(x * c, y * c); }
    Point operator/(T c) const { return Point(x / c, y / c); }
    bool operator<(const Point& p) const {
        return (*this) != p && to_pair() < p.to_pair();
    }
    bool operator>(const Point& p) const { return (*this) != p && !(*this < p); }
    bool operator==(const Point& p) const {
        return isZero(this->x - p.x) && isZero(this->y - p.y);
    }
    bool operator!=(const Point& p) const { return !(*this == p); }
    T cross(const P& p) const { return x * p.y - y * p.x; }
    T cross(const P& a, const P& b) const { return (a - *this).cross(b - *this); } // v.cross(a, b) v is the common point
    T dot(const P& p) const { return x * p.x + y * p.y; }
    P midPoint(const P& p) const { return ((*this) + p) / 2; }
    P getVector(const P& p) const { return p - (*this); } // v.getVector(p). vector from v to p
    T dist2(const P& p) const { return getVector(p).len2(); }
    T len2() const { return (*this).dot(*this); }
    long double dist(const P& p) const { return sqrt(dist2(p)); }
    long double len() const { return sqrt(len2()); }
    P rotateCCW90() const { return P(-y, x); }
    P rotateCCW90Around(const P& p) const { // rotating this around p. I think rotateCCWAround can be done the same way
        return p + p.getVector(*this).rotateCCW90();
    }
    P rotateCCW(long double angle) const { // angle in radian
        return Point(x * cos(angle) - y * sin(angle),
                     x * sin(angle) + y * cos(angle));
    }
    P unit() const { return (*this) / len(); }

    // Project point onto line through a and b (assuming a != b).
    P projectOnLine(const P& a, const P& b) const {
        P ab = a.getVector(b);
        P ac = a.getVector(*this);
        return a + ab * ac.dot(ab) / a.dist2(b);
    }

    // Project point c onto line segment through a and b (assuming a != b).
    P projectOnSegment(const P& a, const P& b) const {
        P& c = *this;
        P ab = a.getVector(b);
        P ac = a.getVector(c);

        long double r = dot(ac, ab), d = a.dist2(b);
        if (r < 0) return a;
        if (r > d) return b;

        return a + ab * r / d;
    }

    // counter clockwise angle from this to other
    ld getAngleTo(Point other) const{
        ld ret = atan2(cross(other), dot(other));
        if (ret < 0)
            ret += 2 * PI;
        return ret;
    }

    // minimum angle between this and other
    ld getMinimumAngle(Point other) const{
        ld ret = getAngleTo(other);
        ret = min(ret, 2 * PI - ret);
        return ret;
    }

    P reflectAroundLine(const P& a, const P& b) const {
        return projectOnLine(a, b) * 2 - (*this);
    }

    // NOT TESTED CHECK PLS
    bool isOnSegment(const P& a, const P& b) const{
        Point ab = b - a, ac = a - (*this);
        return isZero(ab.cross(ac)) && dcmp(ac.dot(ac), 0) != GREATER;
    }

    int getQuad() const {
        if (x >= 0) {
            if (y >= 0) return 0;
            return 3;
        }
        if (y >= 0) return 1;
        return 2;
    }

    friend istream& operator>>(istream& is, P& p) { return is >> p.x >> p.y; }

    friend ostream& operator<<(ostream& os, const P& p) {
        return os << p.x << " " << p.y;
    }
};

// around origin
bool antiClockwiseComparator(const P& a, const P& b) {
    int q1 = a.getQuad(), q2 = b.getQuad();
    if (q1 != q2) {
        return q1 < q2;
    }
    auto cross = a.cross(b);
    if (cross == 0) { // both on same ray, return the closer to the origin
        return a.len2() < b.len2();
    }
    return cross > 0;
}

template <typename T>
const Point<T> Point<T>::Invalid = Point<T>(numeric_limits<T>::max(),
                                            numeric_limits<T>::max());
template <typename T>
const Point<T> Point<T>::Origin = Point<T>(0, 0);

using P = Point<int>;

template <typename T>
bool colinear(Point<T> a, Point<T> b, Point<T> c)
{
    Point<T> ab = b - a, ac = c - a;
    return isZero(ab.cross(ac));
}