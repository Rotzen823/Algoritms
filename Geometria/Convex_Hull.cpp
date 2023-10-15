#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

double const EPS = 1e-9;

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

//Vector
struct vec { double x, y; // name: `vec' is different from STL vector
    vec(double _x, double _y) : x(_x), y(_y) {}
};

vec toVec(const point &a, const point &b) {      // convert 2 points
    return vec(b.x-a.x, b.y-a.y);                  // to vector a->b
}

// returns the cross product of two vectors a and b
double cross(vec a, vec b) { return a.x*b.y - a.y*b.x; }

// note: to accept collinear points, we have to change the `> 0'
// returns true if point r is on the left side of line pq
bool ccw(point p, point q, point r) {
    return cross(toVec(p, q), toVec(p, r)) > -EPS;
}

vector<point> CH_Andrew(vector<point> &pts) {    // overall O(n log n)
    int n = pts.size(), k = 0;
    vector<point> H(2*n);
    sort(pts.begin(), pts.end());                  // sort the points by x/y

    for (int i = 0; i < n; ++i) {                  // build lower hull
        while ((k >= 2) && !ccw(H[k-2], H[k-1], pts[i])) --k;
        H[k++] = pts[i];
    }
    
    for (int i = n-2, t = k+1; i >= 0; --i) {       // build upper hull
        while ((k >= t) && !ccw(H[k-2], H[k-1], pts[i])) --k;
        H[k++] = pts[i];
    }

    H.resize(k);
    return H;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vector<point> pts;

    int n;
    cin >> n;

    while(n--){
        double x, y;
        cin >> x >> y;
        pts.push_back(point(x, y));
    }

    vector<point> hull = CH_Andrew(pts);

    cout << hull.size() - 1 << "\n";

    for(int k = 0; k < (int) hull.size() - 1; k++){
        cout << hull[k].x << " " << hull[k].y << "\n";
    }

    return 0;
}
