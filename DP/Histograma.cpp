#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

vi num, izq, der;

void histograma(int n){
    izq.assign(n, 0); der.assign(n, 0);
    stack<int> pila;

    for(int k = 0; k < n; k++){
        while(!pila.empty() && num[pila.top()] <= num[k]){
            pila.pop();
        }

        if(!pila.empty()){
            izq[k] = pila.top();
        }
        else{
            izq[k] = -1;
        }

        pila.push(k);
    }

    while(!pila.empty()){
        pila.pop();
    }

    for(int k = n - 1; k >= 0; k--){
        while(!pila.empty() && num[pila.top()] <= num[k]){
            pila.pop();
        }

        if(!pila.empty()){
            der[k] = pila.top();
        }
        else{
            der[k] = n;
        }

        pila.push(k);
    }
}

int main() {
    int n;
    cin >> n;

    num.assign(n, 0);

    for(int k = 0; k < n; k++){
        cin >> num[k];
    }

    histograma(n);

    for(int k = 0; k < n; k++){
        cout << izq[k] << " ";
    }
    cout << "\n";

    for(int k = 0; k < n; k++){
        cout << der[k] << " ";
    }

    return 0;
}
