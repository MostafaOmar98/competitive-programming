#include <bits/stdc++.h>

using namespace std;


typedef long long ll;
#define rep(i, start, end) for(int i = start; i < end; ++i)
#define per(i, start, end) for(int i = (int)start-1; i >= end; --i)
#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define F first
#define S second
#define all(x) x.begin(), x.end()
const double PI = 3.14159265358979323846;
const double eps = (1e-9);

int dcmp(double x, double y)
{
    return fabs(x - y) <= eps ? 0 : x < y ? -1 : 1;
}

struct edge {
    int from, to, w;

    edge(int from, int to, int w): from(from), to(to), w(w) {}

    bool operator < (const edge & e) const {
        return w > e.w;
    }
};

int Dijkstra2(vector< vector< edge > > adjList, int src, int dest = -1) // O(E logV)
{
    int n = sz(adjList);
    vi dist(n, OO), prev(n, -1);
    dist[src] = 0;

    priority_queue<edge> q;
    q.push( edge(-1, src, 0) );

    while( !q.empty() ) {
        edge e = q.top();   q.pop();

        if(e.w > dist[e.to]) continue;   // some other state reached better

        prev[ e.to ] = e.from;

        rep(j, adjList[e.to]) {
                edge ne = adjList[e.to][j];
                if( dist[ne.to] > dist[ne.from] + ne.w ) {
                    ne.w = dist[ne.to] = dist[ne.from] + ne.w;
                    q.push( ne );
                }
        }
    }

    return dest == -1 ? -1 : dist[dest];
}


int main()
{
    ios_base::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);

    return 0;
}