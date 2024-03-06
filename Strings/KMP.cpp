#include <bits/stdc++.h>

using namespace std;

struct KMP{
    int N;
    string P; //String a buscar
    vi b; //Aqui se guarda el patron

    void init(string s){
        P = s;
        N = s.length();
        b.assign(N + 1, 0);
        kmpPreprocess();
    }
    
    //Calculo del patron
    void kmpPreprocess(){ 
        int i = 0, j = -1; b[0] = -1;  
        while(i < N){ 
            while(j >= 0 && P[i] != P[j]) j = b[j]; 
            i++; j++; 
            b[i] = j;
        }
    }   

    //Retorna el indice de la primera aparición de P en T
    //Retorna -1 en caso de que no exista.
    int kmpSearch(string T){ 
        int M = T.length();
        int i = 0, j = 0;   
        while(i < M){ 
            while(j >= 0 && T[i] != P[j]) j = b[j]; 
            i++; j++; 
            if(j == N){
                return i - j;
                j = b[j];
            }
        }
        return -1;
    }
};

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    string P, T;
    cin >> P >> T;

    KMP kmp;
    kmp.init(P);

    cout << kmp.kmpSearch(T) << "\n";

    return 0;
}
