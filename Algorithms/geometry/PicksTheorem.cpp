#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const long double eps = (1e-15);
enum
{
    LESS, EQUAL, GREATER
};

template <class T>
struct Point {
    typedef Point P;
    T x = 0, y = 0;
    Point(T x, T y) : x(x), y(y) {}
    Point() {}
    Point operator-(const Point& p) const { return Point{x - p.x, y - p.y}; }
    T cross(const P& p) const { return x * p.y - y * p.x; }

    friend istream& operator>>(istream& is, P& p) { return is >> p.x >> p.y; }
};

// gets triangle area using 3 points
ll doubleTriangleArea(Point<ll> a, Point<ll> b, Point<ll> c)
{
    Point<ll> ab = b - a, ac = c - a;
    return ab.cross(ac);
}

template <typename T>
T doublePolygonArea(const vector<Point<T> > &v)
{
    T ret = 0;
    for (int i = 1; i + 1 < v.size(); ++i)
    {
        Point<T> ab = v[i] - v[0], ac = v[i + 1] - v[0];
        ret += ab.cross(ac);
    }
    return abs(ret);
}
// https://codeforces.com/gym/101873/problem/G
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<Point<ll> > v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i];

    ll doubleA = doublePolygonArea(v);
    ll B = 0;
    for (int i = 0; i < n; ++i)
    {
        Point<ll> d = v[(i + 1)%n] - v[i];
        d.x = abs(d.x), d.y = abs(d.y);
        B += __gcd(d.x, d.y);
    }
    ll doubleI = doubleA - B + 2;
    cout << doubleI/2 << '\n';

}