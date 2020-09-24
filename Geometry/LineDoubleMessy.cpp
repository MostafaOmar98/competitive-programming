struct Point{
    ld x, y;
    Point (ld x = 0, ld y = 0)
    {
        this->x = x, this->y = y;
    }
    Point operator-(Point p) const{
        return Point(x - p.x, y - p.y);
    }
    friend istream& operator>>(istream& in, Point &p) {
        in >> p.x >> p.y;
        return in;
    }
    friend ostream& operator<<(ostream& out, const Point &p){
        out << p.x << " " << p.y;
        return out;
    }
};
enum {LINE, NONE, POINT};
enum {LESS, EQUAL, GREATER};
int dcmp(ld x, ld y)
{
    if (fabs(x - y) <= eps)
        return EQUAL;
    return x > y ? GREATER : LESS;
}

struct Line{
    // a * y + b * x + c = 0
    // slope is -b/a
    // in this line we maintain a = 1 unless it's vertical. For integral line you dont have to maintain this but other functions will get more complicated
    ld a, b, c;
    Line(Point p1, Point p2)
    {
        if (dcmp(p1.x, p2.x) == EQUAL) { // vertical line on form b * x + c = 0
            a = 0, b = 1, c = -p1.x;
        } else {
            ld dy = p2.y - p1.y, dx = p2.x - p1.x;
            a = 1;
            b = -dy/dx;
            c = p1.x * dy/dx - p1.y;
        }
    }
    Line (ld a, ld b, ld c)
    {
        if (dcmp(a, 0) != EQUAL)
            this->a = 1, this->b = b/a, this->c = c/a;
        else
            this->a = a, this->b = b, this->c = c;
    }

    bool isParallel(const Line &other) const{
        return dcmp(-b * other.a, -other.b * a) == EQUAL;
    }

    // works online if lines are in a canonical form such as keeping a = {0, 1} or dividing by gcd if a,b,c integers and keeping signs consistent
    bool sameLine(const Line &other) const{
        return isParallel(other) && dcmp(c, other.c) == EQUAL;
    }

    ld f(Point p) const {
        return a * p.y + b * p.x + c;
    }


    /*
     * returns LINE if two line are identical
     * returns NONE if two lines don't intersect
     * returns POINT and puts intersection point in out in case they properly intersect
     * old commented version works only if a = 1
     * New version should work otherwise
     */
    int getIntersection(Line &other, Point &out){
        if (sameLine(other))
            return LINE;
        if (isParallel(other))
            return NONE;
        out.x = (a * other.c - other.a * c)/(b * other.a - other.b * a);
        if (dcmp(a, 0) != EQUAL)
            out.y = (-b * out.x - c)/a;
        else
            out.y = (-other.b * out.x - other.c)/other.a;
        return POINT;
    }

//    int getIntersection(Line other, Point &out) const{
//        if (sameLine(other))
//            return LINE;
//        if (isParallel(other))
//            return NONE;
//        if (dcmp(a, 0) == EQUAL)
//        {
//            // vertical line, b should be != 0 unless the line is degenerate
//            // since two lines are not parallel, other is guaranteed not to be vertical
//            assert(dcmp(b, 0) != EQUAL);
//            out.x = -c/b;
//            out.y = -other.b * out.x - other.c;
//        }
//        else if (dcmp(other.a, 0) == EQUAL)
//        {
//            out.x = -other.c/other.b;
//            out.y = -b * out.x - c;
//        }
//        else
//        {
//            out.x = (c - other.c) / (other.b - b);
//            out.y = -b * out.x - c; // dont do it using other as other could be vertical
//        }
//        return POINT;
//    }
};

struct LineSegment{
    Point st, en;
    LineSegment(Point p1, Point p2){
        st = p1, en = p2;
    }

    bool onLine(Point c) const{
        return dcmp(Line(st, en).f(c), 0) == EQUAL;
    }

    bool onDisk(Point c) const{
        Point ca = st - c, cb = en - c;
        return dcmp(ca.dot(cb), 0) != GREATER;
    }

    bool onSegment(Point c) const{
        return onDisk(c) && onLine(c);
    }

    // assuming segment is not on line 'other'
    int getIntersection(Line other, Point &out) const{
        Line l(st, en);
        int state = l.getIntersection(other, out);
        assert(state != LINE);
        if (state != POINT)
            return state;
        if (onDisk(out))
            return POINT;
        return NONE;
    }
};
