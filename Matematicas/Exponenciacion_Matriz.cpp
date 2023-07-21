#include<bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

typedef struct Matrix{
    vector<vi> mat;
    int n, m;

    Matrix(int N, int M, int a){
        n = N; m = M;
        mat.assign(n, vi(m, 0));

        for(int k = 0; k < n; k++){
            for(int j = 0; j < m; j++){
                mat[k][j] = (k == j) * a;
            }
        }
    }

    Matrix operator *(const Matrix& a) const
    {
        Matrix ans(n, a.m, 0);
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < a.m; j++)
            {
                for(int k = 0; k < m; k++){
                    int res = (mat[i][k] * a.mat[k][j]);
                    ans.mat[i][j] = (ans.mat[i][j] + res);
                }
            }
        }
        return ans;
    }    
}Matrix;

Matrix qpow(Matrix x, int n)
{
    Matrix ans(x.n, x.m, 1);
    while(n)
    {
        if(n & 1) ans = ans * x;
        n >>= 1;
        x = x * x;
    }
    return ans;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, k;
    cin >> n >> k;

    Matrix x(n, n, 0);
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> x.mat[i][j];
        }
    }

    Matrix r = qpow(x, k);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << r.mat[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}
