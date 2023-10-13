#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

double const EPS = 1e-9;
const double PI=acos(-1.0);
double DEG_to_RAD(double d) { return d*PI/180.0; }
double RAD_to_DEG(double r) { return r*180.0/PI; }

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

// rotate p by theta degrees CCW w.r.t origin (0, 0)
point rotate(point p, double theta) {
  double rad = DEG_to_RAD(theta);                // convert to radian
  return point(p.x*cos(rad) - p.y*sin(rad),
               p.x*sin(rad) + p.y*cos(rad));
}

//Vector
struct vec { double x, y; // name: `vec' is different from STL vector
    vec(double _x, double _y) : x(_x), y(_y) {}
};

vec toVec(const point &a, const point &b) {      // convert 2 points
    return vec(b.x-a.x, b.y-a.y);                  // to vector a->b
}

vec scale(const vec &v, double s) {              // s = [<1..1..>1]
  return vec(v.x*s, v.y*s);                      // shorter/eq/longer
}  

point translate(const point &p, const vec &v) {  // translate p
  return point(p.x+v.x, p.y+v.y);                // according to v
}  

//Producto punto
int dot(vec a, vec b) { return (a.x*b.x + a.y*b.y); }

// returns the cross product of two vectors a and b
double cross(vec a, vec b) { return a.x*b.y - a.y*b.x; }

// returns the squared value of the normalized vector
double norm_sq(vec v) { return v.x*v.x + v.y*v.y; }

//Linea
struct line { double a, b, c; };  // most versatile

// the answer is stored in the third parameter (pass by reference)
void pointsToLine(point p1, point p2, line &l) {
    if (fabs(p1.x-p2.x) < EPS)                     // vertical line is fine
      l = {1.0, 0.0, -p1.x};                       // default values
    else {
      double a = -(double)(p1.y-p2.y) / (p1.x-p2.x);
      l = {a, 1.0, -(double)(a*p1.x) - p1.y};      // NOTE: b always 1.0
    }
}

// convert point and gradient/slope to line
void pointSlopeToLine(point p, double m, line &l) {
  l.a = -m;                                      // always -m
  l.b = 1;                                       // always 1
  l.c = -((l.a * p.x) + (l.b * p.y));            // compute this
}

bool areParallel(line l1, line l2) {             // check a & b
  return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS);
}

bool areSame(line l1, line l2) {                 // also check  c
  return areParallel(l1 ,l2) && (fabs(l1.c-l2.c) < EPS);
}

// returns true (+ intersection point p) if two lines are intersect
bool areIntersect(line l1, line l2, point &p) {
  if (areParallel(l1, l2)) return false;         // no intersection
  // solve system of 2 linear algebraic equations with 2 unknowns
  p.x = (l2.b*l1.c - l1.b*l2.c) / (l2.a*l1.b - l1.a*l2.b);
  // special case: test for vertical line to avoid division by zero
  if (fabs(l1.b) > EPS) p.y = -(l1.a*p.x + l1.c);
  else                  p.y = -(l2.a*p.x + l2.c);
  return true;
}

void closestPoint(line l, point p, point &ans) {
    // this line is perpendicular to l and pass through p
    line perpendicular;                            
    if (fabs(l.b) < EPS) {                         // vertical line
        ans.x = -(l.c);
        ans.y = p.y;
        return;
    }
    if (fabs(l.a) < EPS) {                         // horizontal line
        ans.x = p.x;
        ans.y = -(l.c);
        return;
    }
    pointSlopeToLine(p, 1/l.a, perpendicular);     // normal line
    // intersect line l with this perpendicular line
    // the intersection point is the closest point
    areIntersect(l, perpendicular, ans);
}

// returns the reflection of point on a line
void reflectionPoint(line l, point p, point &ans) {
    point b;
    closestPoint(l, p, b);                         // similar to distToLine
    vec v = toVec(p, b);                           // create a vector
    ans = translate(b, v);           // translate p twice
}

// returns the distance from p to the line defined by
// two points a and b (a and b must be different)
// the closest point is stored in the 4th parameter (byref)
double distToLine(point p, point a, point b, point &c) {
  vec ap = toVec(a, p), ab = toVec(a, b);
  double u = dot(ap, ab) / norm_sq(ab);
  // formula: c = a + u*ab
  c = translate(a, scale(ab, u));                // translate a to c
  return dist(p, c);                             // Euclidean distance
}

// returns the distance from p to the line segment ab defined by
// two points a and b (technically, a has to be different than b)
// the closest point is stored in the 4th parameter (byref)
double distToLineSegment(point p, point a, point b, point &c) {
  vec ap = toVec(a, p), ab = toVec(a, b);
  double u = dot(ap, ab) / norm_sq(ab);
  if (u < 0.0) {                                 // closer to a
    c = point(a.x, a.y);
    return dist(p, a);                           // dist p to a
  }
  if (u > 1.0) {                                 // closer to b
    c = point(b.x, b.y);
    return dist(p, b);                           // dist p to b
  }
  return distToLine(p, a, b, c);                 // use distToLine
}

// compute the intersection point between line segment p-q and line A-B
point lineIntersectSeg(point p, point q, point A, point B) {
  double a = B.y-A.y, b = A.x-B.x, c = B.x*A.y - A.x*B.y;
  double u = fabs(a*p.x + b*p.y + c);
  double v = fabs(a*q.x + b*q.y + c);
  return point((p.x*v + q.x*u) / (u+v), (p.y*v + q.y*u) / (u+v));
}

// angle aob in rad
double angle(const point &a, const point &o, const point &b) {
    vec oa = toVec(o, a), ob = toVec(o, b);        // a != o != b
    return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob)));
}  

// note: to accept collinear points, we have to change the `> 0'
// returns true if point r is on the left side of line pq
bool ccw(point p, point q, point r) {
  return cross(toVec(p, q), toVec(p, r)) > -EPS;
}

// returns true if point r is on the same line as the line pq
bool collinear(point p, point q, point r) {
    return fabs(cross(toVec(p, q), toVec(p, r))) < EPS;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    
    return 0;
}
