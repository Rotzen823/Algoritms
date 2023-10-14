#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> ii;
typedef vector<ii> vii;

double const EPS = 1e-9;
const double PI = acos(-1.0);

//Puntos
struct point {
    double x, y;                                   // if need more precision
    point() { x = y = 0.0; }                       // default constructor
    point(double _x, double _y) : x(_x), y(_y) {}  // constructor

    bool operator < (point other) const {          // override < operator
        if (fabs(x-other.x) > EPS)                   // useful for sorting
          return x < other.x;                        // by x-coordinate
        return y < other.y;                          // if tie, by y-coordinate
    }
    
    // use EPS (1e-9) when testing equality of two floating points
    bool operator == (point other) const {
      return (fabs(x-other.x) < EPS && (fabs(y-other.y) < EPS));
    }
};

double dist(point p1, point p2) {                // Euclidean distance
  // hypot(dx, dy) returns sqrt(dx*dx + dy*dy)
  return hypot(p1.x-p2.x, p1.y-p2.y);            // return double
}

//Vector
struct vec { double x, y; // name: `vec' is different from STL vector
    vec(double _x, double _y) : x(_x), y(_y) {}
};

vec toVec(const point &a, const point &b) {      // convert 2 points
    return vec(b.x-a.x, b.y-a.y);                  // to vector a->b
}

//Producto punto
int dot(vec a, vec b) { return (a.x*b.x + a.y*b.y); }

// returns the cross product of two vectors a and b
double cross(vec a, vec b) { return a.x*b.y - a.y*b.x; }

// returns the squared value of the normalized vector
double norm_sq(vec v) { return v.x*v.x + v.y*v.y; }

// note: to accept collinear points, we have to change the `> 0'
// returns true if point r is on the left side of line pq
bool ccw(point p, point q, point r) {
  return cross(toVec(p, q), toVec(p, r)) > -EPS;
}

// angle aob in rad
double angle(const point &a, const point &o, const point &b) {
    vec oa = toVec(o, a), ob = toVec(o, b);        // a != o != b
    return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob)));
}  

// returns the perimeter of polygon P, which is the sum of
// Euclidian distances of consecutive line segments (polygon edges)
double perimeter(const vector<point> &P) {       // by ref for efficiency
  double ans = 0.0;
  for (int i = 0; i < (int)P.size()-1; ++i)      // note: P[n-1] = P[0]
    ans += dist(P[i], P[i+1]);                   // as we duplicate P[0]
  return ans;
}

// returns the area of polygon P
double area(const vector<point> &P) {
  double ans = 0.0;
  for (int i = 0; i < (int)P.size()-1; ++i)      // Shoelace formula
    ans += (P[i].x*P[i+1].y - P[i+1].x*P[i].y);
  return fabs(ans)/2.0;                          // only do / 2.0 here
}

// returns true if we always make the same turn
// while examining all the edges of the polygon one by one
bool isConvex(const vector<point> &P) {
    int n = (int)P.size();
    // a point/sz=2 or a line/sz=3 is not convex  
    if (n <= 3) return false;
    bool firstTurn = ccw(P[0], P[1], P[2]);        // remember one result,
    for (int i = 1; i < n-1; ++i)                 // compare with the others
        if (ccw(P[i], P[i+1], P[(i+2) == n ? 1 : i+2]) != firstTurn)
            return false;                              // different -> concave
    return true;   
}

// returns 1/0/-1 if point p is inside/on (vertex/edge)/outside of
// either convex/concave polygon P
int insidePolygon(point pt, const vector<point> &P) {
    int n = (int)P.size();
    if (n <= 3) return -1;                         // avoid point or line
    bool on_polygon = false;
    for (int i = 0; i < n-1; ++i)                  // on vertex/edge?
        if (fabs(dist(P[i], pt) + dist(pt, P[i+1]) - dist(P[i], P[i+1])) < EPS)
        on_polygon = true;
    if (on_polygon) return 0;                      // pt is on polygon
    double sum = 0.0;                              // first = last point
    for (int i = 0; i < n-1; ++i) {
        if (ccw(pt, P[i], P[i+1]))
        sum += angle(P[i], pt, P[i+1]);            // left turn/ccw
        else
        sum -= angle(P[i], pt, P[i+1]);            // right turn/cw
    }
    return fabs(sum) > PI ? 1 : -1;              // 360d->in, 0d->out
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<point> puntos;
    for(int k = 0; k < n; k++){
        double x, y;
        cin >> x >> y;
        puntos.push_back(point(x, y));
    }
    puntos.push_back(puntos[0]);

    cout << area(puntos);
    cout << perimeter(puntos);

  return 0;
}
