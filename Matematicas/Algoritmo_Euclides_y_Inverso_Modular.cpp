#include<bits/stdc++.h>
#define MOD 1000000007

using namespace std;

typedef pair<int, int> ii;
 
int gcd(int a, int b){
    while(b > 0){
        int r = a % b;
        a = b;
        b = r;
    }

    return a;
}

ii mcdExt(int a, int b){
    int r, y = 0, x1 = 0, y1 = 1, tx, ty;
    int x = 1;
    while(b > 0){
        r= a % b;
        tx = x1, ty = y1;
        x1 = x - (a / b) * x1;
        x = tx;
        y1 = y - (a / b) * y1;
        y = ty;
        a = b;
        b = r;
    }

    return ii(x, y);
}

int inv_mod(int a, int b){
    int x = mcdExt(b, MOD).first;
    x = (x + MOD) % MOD;
    return (a * x) % MOD;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int a, b;
    cin >> a >> b;

    cout << inv_mod(a, b) << "\n";

    return 0;
}
