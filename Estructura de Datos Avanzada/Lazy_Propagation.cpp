#include<bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

class Lazy{
    private:
        int n;
        vi st, lazy;
        int left(int v){
            return (v << 1);
        }
        int right(int v){
            return (v << 1) + 1;
        }

        int query(int sl, int sr, int v, int l, int r){
            if(sl > r || sr < l){
                return 0;
            }

            if(lazy[v] != 0){
                st[v] += lazy[v] * (r - l + 1);
                if(r != l){
                    lazy[left(v)] += lazy[v];
                    lazy[right(v)] += lazy[v];
                }
                lazy[v] = 0;
            }

            if(l >= sl && r <= sr){
                return st[v];
            }

            int m = (l + r) / 2;

            return query(sl, sr, left(v), l, m) + query(sl, sr, right(v), m + 1, r);
        }

        void update(int sl, int sr, int value, int v, int l, int r){
            if(lazy[v]){
                st[v] += lazy[v] * (r - l + 1);
                if(r != l){
                    lazy[left(v)] += lazy[v];
                    lazy[right(v)] += lazy[v];
                }
                lazy[v] = 0;
            }

            if(sl > r || sr < l){
                return;
            }

            if(l >= sl && r <= sr){
                st[v] += value * (r - l + 1);
                if(r != l){
                    lazy[left(v)] += value;
                    lazy[right(v)] += value;
                }
                return;
            }

            int m = (l + r) / 2;

            update(sl, sr, value, left(v), l, m);
            update(sl, sr, value, right(v), m + 1, r);

            st[v] = st[left(v)] + st[right(v)];
        }

    public:
        Lazy(int N){
            n = N;
            st.assign(4 * n, 0);
            lazy.assign(4 * n, 0);
        }

        int query(int l, int r){
            return query(l, r, 1, 0, n - 1);
        }

        void update(int l, int r, int value){
            return update(l, r, value, 1, 0, n - 1);
        }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m;
    cin >> n >> m;

    Lazy st(n);

    while(m--){
        char op;
        int a, b, c;
        cin >> op;
        if(op == 'u'){
            cin >> a >> b >> c;
            st.update(a, b, c);
        }
        else{
            cin >> a >> b;
            cout << st.query(a, b) << "\n";
        }
    }
    
    return 0;
}
