#include<bits/stdc++.h>

using namespace std;

vector<bool> esPrimo;
 
void criba(int n){
    esPrimo.assign(n, true);

    esPrimo[0] = esPrimo[1] = false;

    for(int k = 2; (k * k) <= n; k++){
        if(esPrimo[k]){
            for(int j = k * k; j <= n; j += k){
                esPrimo[j] = false;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;

    criba(n);

    cout << "Primos:\n";
    for(int k = 0; k <= n; k++){
        if(esPrimo[k]){
            cout << k << " ";
        }
    }

    return 0;
}
