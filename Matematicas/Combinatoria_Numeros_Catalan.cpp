#include <bits/stdc++.h>
#define MOD 1000000
#define MAX 2010

using namespace std;

typedef long long ll;

ll comb[MAX][MAX];

ll nCk(ll n, ll k){
    if(k < 0 || k > n){
        return 0;
    }

    if(n == k || k == 0){
        return 1;
    }

    if(comb[n][k] != -1){
        return comb[n][k];
    }

    return comb[n][k] = (nCk(n - 1, k - 1) + nCk(n - 1, k)) % MOD;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    ll n;
    memset(comb, -1, sizeof(comb));

    cin >> n;
    ll res = (nCk(2 * n, n) - nCk(2 * n, n - 1) + MOD) % MOD;  
    cout << res << "\n";

    return 0;
}
