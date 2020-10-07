#include<bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#define debug(...) debug_out(vec_splitter(#__VA_ARGS__), 0, __LINE__, __VA_ARGS__)
#else
#define debug(...) ;
#endif


typedef long long ll;
typedef long double ld;
#define rep(i, start, end) for(int i = start; i < end; ++i)
#define sz(x) (int)((x).size())
#define pb push_back
#define all(x) x.begin(), x.end()
#define clr(d, v) memset(d, v, sizeof(d))
#define pii pair<int, int>
#define X first
#define Y second
//#define debug(x) cerr << #x << " : " << (x) << " "
const double PI = 3.14159265358979323846;
const double eps = (1e-9);

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


    bool isParallel(const Line &other){
        return dcmp(-b * other.a, -other.b * a) == EQUAL;
    }

    bool sameLine(const Line &other){
        return isParallel(other) && dcmp(c, other.c) == EQUAL;
    }


    /*
     * returns LINE if two line are identical
     * returns NONE if two lines don't intersect
     * returns POINT and puts intersection point in out in case they properly intersect
     * works only if a = 1
     */
    int getIntersection(Line &other, Point &out){
        if (sameLine(other))
            return LINE;
        if (isParallel(other))
            return NONE;
        if (dcmp(a, 0) == EQUAL)
        {
            // vertical line, b should be != 0 unless the line is degenerate
            // since two lines are not parallel, other is guaranteed not to be vertical
            assert(dcmp(b, 0) != EQUAL);
            out.x = -c/b;
            out.y = -other.b * out.x - other.c;
        }
        else
        {
            out.x = (c - other.c) / (other.b - b);
            out.y = -b * out.x - c; // dont do it using other as other could be vertical
        }
        return POINT;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
//    freopen("AC.txt", "w", stdout);
#endif
    Point pt[2][2];
    int n;
    cin >> n;
    cout << "INTERSECTING LINES OUTPUT\n";
    while(cin >> pt[0][0] >> pt[0][1] >> pt[1][0] >> pt[1][1])
    {
        Line l1 = Line(pt[0][0], pt[0][1]), l2 = Line(pt[1][0], pt[1][1]);
        Point intersectionPoint;
        int inter = l1.getIntersection(l2, intersectionPoint);
        if (inter == LINE)
            cout << "LINE\n";
        else if (inter == NONE)
            cout << "NONE\n";
        else
        {
            cout << "POINT " << fixed << setprecision(2) << intersectionPoint << '\n';
        }
    }
    cout << "END OF OUTPUT\n";
}