#include<bits/stdc++.h>

using namespace std;
 
int modpow(int x, int n, int m) {
    if (n == 0)
        return 1;

    int u = modpow(x, n/2, m);
    u = (u * u) % m;
    if (n % 2 == 1){
        u = (u * x) % m;
    }

  return u;
}



int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int x, k, m;
    cin >> x >> k >> m;

    cout << modpow(x, k, m) << "\n";

    return 0;
}
