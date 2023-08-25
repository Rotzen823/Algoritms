#include <bits/stdc++.h>
#define MAX 100010
using namespace std;
string T, P;
int b[MAX], n, m; 
// b = tabla de reinicios // n = long. de T // m = long. de P 
void kmpPreprocess(){ // Llamar antes de kmpSearch()
    int i = 0, j = -1; b[0] = -1;  // Valores Iniciales
    while(i < m){ //Proceso previo de cadena patrón P
        while(j >= 0 && P[i] != P[j]) j = b[j]; //Diferente, reiniciar j
        i++; j++; // Si es igual avanzamos ambos punteros
        b[i] = j;
    }
}

void kmpSearch(){ //Similar a kmpPreprocess(), pero sobre T
    int i = 0, j = 0;   //Valores iniciales
    while(i < n){ //Buscar en la cadena T
        while(j >= 0 && T[i] != P[j]) j = b[j]; //Diferente, reiniciar j
        i++; j++; //Si es igual avanzamos ambos punteros
        if(j == m){
            cout << "P se encontró en el index " << i - j << "\n";
            j = b[j]; //Preparar j para la siguiente coincidencia
        }
    }
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> P >> T;
    m = P.length();
    n = T.length();

    kmpPreprocess();
    kmpSearch();

    return 0;
}
