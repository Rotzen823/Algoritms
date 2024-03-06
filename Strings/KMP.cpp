#include <bits/stdc++.h>
#define MAX 100010
using namespace std;

struct KMP{
    int N;
    string P;
    vi b;
    int b[MAX], n, m; 

    void init(string s){
        P = s;
        N = s.length();
        b.assign(N + 1, 0);
        kmpPreprocess();
    }
    
    void kmpPreprocess(){ 
        int i = 0, j = -1; b[0] = -1;  
        while(i < N){ 
            while(j >= 0 && P[i] != P[j]) j = b[j]; 
            i++; j++; 
            b[i] = j;
        }
    }   

    //Retorna la primera aparición de P en T
    //Regresa el indice de inicio.
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

    cin >> P >> T;
    m = P.length();
    n = T.length();

    kmpPreprocess();
    kmpSearch();

    return 0;
}
