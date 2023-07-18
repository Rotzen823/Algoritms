#include<bits/stdc++.h>
#define INF 1000000

using namespace std;

typedef vector<int> vi;

class SegmentTree{
    private:
        int n;
        vi st;
        int left(int v){
            return (v << 1);
        }
        int right(int v){
            return (v << 1) + 1;
        }
        void build(int id, int value, int v, int l, int r){
            if(l == r){
                st[v] = value;
                return;
            }
            int m = (l + r) / 2;
            if(id <= m){
                build(id, value, left(v), l, m);
            }
            else{
                build(id, value, right(v), m + 1, r);
            }
            st[v] = min(st[left(v)], st[right(v)]);
        }

        int query(int sl, int sr, int v, int l, int r){
            if(sl > r || sr < l){
                return INF;
            }
 
            if(l >= sl && r <= sr){
                return st[v];
            }
 
            int m = (l + r) / 2;
 
            return min(query(sl, sr, left(v), l, m), query(sl, sr, right(v), m + 1, r));
        }
 
    public:
        SegmentTree(int N){
            n = N;
            st.assign(4 * n, 0);
        }
 
        int query(int l, int r){
            return query(l, r, 1, 0, n - 1);
        }
 
        void update(int id, int value){
            return build(id, value, 1, 0, n - 1);
        }
};


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m;
    cin >> n >> m;

    SegmentTree st(n);

    for(int k = 0; k < n; k++){
        int x;
        cin >> x;
        st.update(k, x);
    }

    while(m--){
        char op;
        int a, b;
        cin >> op >> a >> b;
        a--;
        if(op == 'u'){
            st.update(a, b);
        }
        else{
            b--;
            cout << st.query(a, b) << "\n";
        }
    }
    
    return 0;
}
