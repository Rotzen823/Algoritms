#include <bits/stdc++.h>
 
using namespace std;

typedef long long ll;
typedef vector<ll> vi;
const double PI = acos(-1);

//const int N = 4200000; // 200MB
const int N = 2100000; // 100MB
struct Complex {
    double x, y;

    Complex(double x = 0, double y = 0) : x(x), y(y) {}

    friend Complex operator + (const Complex &u, const Complex &v) { return Complex(u.x + v.x, u.y + v.y); }
    friend Complex operator - (const Complex &u, const Complex &v) { return Complex(u.x - v.x, u.y - v.y); }
    friend Complex operator * (const Complex &u, const Complex &v) {
        return Complex(u.x * v.x - u.y * v.y, u.x * v.y + u.y * v.x); 
    }
} a[N], b[N];

int P[N];
void init_P(int n) {
    int l = 0; while ((1 << l) < n) ++l;
    for (int i = 0; i < n; ++i) P[i] = (P[i >> 1] >> 1) | ((i & 1) << (l - 1));
}

vector<Complex> init_W(int n) {
    vector<Complex> w(n); w[1] = 1;
    for (int i = 2; i < n; i <<= 1) {
        auto w0 = w.begin() + i / 2, w1 = w.begin() + i;
        Complex wn(cos(PI / i), sin(PI / i));
        for (int j = 0; j < i; j += 2)
            w1[j] = w0[j >> 1], w1[j + 1] = w1[j] * wn;
    }
    return w; 
} auto w = init_W(1 << 21);

void DIT(Complex *a, int n) {
    for (int k = n >> 1; k; k >>= 1)
        for (int i = 0; i < n; i += k << 1)
            for (int j = 0; j < k; ++j) {
                Complex x = a[i + j], y = a[i + j + k];
                a[i + j + k] = (x - y) * w[k + j], a[i + j] = x + y;
            }
}
void DIF(Complex *a, int n) {
    for (int k = 1; k < n; k <<= 1)
        for (int i = 0; i < n; i += k << 1)
            for (int j = 0; j < k; ++j) {
                Complex x = a[i + j], y = a[i + j + k] * w[k + j];
                a[i + j + k] = x - y, a[i + j] = x + y;
            }
    for (int i = 0; i < n; ++i) a[i].x /= n, a[i].y /= n;
    reverse(a + 1, a + n);
}

vi Mul(const vi &A, const vi &B, int n1, int n2) {
    int n = 1; while (n < n1 + n2 - 1) n <<= 1; init_P(n);
    for (int i = 0; i < n1; ++i) a[i] = Complex(A[i], 0);
    for (int i = 0; i < n2; ++i) b[i] = Complex(B[i], 0);
    fill(a + n1, a + n, Complex(0, 0)); fill(b + n2, b + n, Complex(0, 0));
    DIT(a, n); DIT(b, n);
    for (int i = 0; i < n; ++i) a[i] = a[i] * b[i];
    DIF(a, n); vi ans(n1 + n2 - 1); for (int i = 0; i < n1 + n2 - 1; ++i) ans[i] = (ll) (a[i].x + 0.5);
    return ans;
}
 
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    int n, m;
    cin >> n >> m;
    vi p1(n), p2(m);
    for(int k = 0; k < n; k++){
        int x;
        cin >> x;
        p1[k] = x;
    }

    for(int k = 0; k < m; k++){
        int x;
        cin >> x;
        p2[k] = x;
    }

    vi res = Mul(p1, p2, n, m);

    for(int k = 0; k < (int) res.size(); k++){
        cout << res[k] << " ";
    }

    return 0;
}
