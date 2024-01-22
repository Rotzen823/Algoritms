#include <bits/stdc++.h>
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
 
using namespace std;

typedef unsigned long long ll;
typedef pair<int, int> ii;
typedef pair<ii, int> iii;
typedef vector<int> vi;
typedef vector<ii> vii;
 
struct SegmentTree {
    int n;
    vector<vector<int>> tree;
    
    //O(nlog(n))
    void build(vector<int> &a, int x, int l, int r) {
        if (l + 1 == r) {
            tree[x] = {a[l]};
            return;
        }
 
        int m = (l + r) / 2;
        build(a, 2 * x + 1, l, m);
        build(a, 2 * x + 2, m, r);
        merge(all(tree[2 * x + 1]), all(tree[2 * x + 2]), back_inserter(tree[x]));
    }
 
    SegmentTree(vector<int>& a) : n(a.size()) {
        int SIZE = 1 << (__lg(n) + bool(__builtin_popcount(n) - 1));
        tree.resize(2 * SIZE - 1);
        build(a, 0, 0, n);
    }
    
    //O(log^2(n))
    int count(int lq, int rq, int mn, int mx, int x, int l, int r) {
        if (rq <= l || r <= lq) return 0;
        if (lq <= l && r <= rq) return lower_bound(all(tree[x]), mx) - lower_bound(all(tree[x]), mn);
 
        int m = (l + r) / 2;
        int a = count(lq, rq, mn, mx, 2 * x + 1, l, m);
        int b = count(lq, rq, mn, mx, 2 * x + 2, m, r);
        return a + b;
    }
    
    //Devuelve la cantidad de numeros en el rango [lq, rq) (lq inclusivo, rq no inclsuivo)
    //Que cumplan la condición: mn <= x <= mx
    int count(int lq, int rq, int mn, int mx) {
        return count(lq, rq, mn, mx, 0, 0, n);
    }
};

struct Grafo{
    int V;
    vector<vi> adj;
    vi in, out;
    int tiempo;

    void init(int _V){
        V = _V;
        adj.assign(V, vi());
        in.assign(V, -1);
        out.assign(V, -1);
        tiempo = 0;
    }

    void ae(int a, int b){ adj[a].push_back(b); }

    void dfs(int u, int p){
        in[u] = tiempo++;
        
        for(int v : adj[u]){
            if(v == p){
                continue;
            }
            dfs(v, u);
        }
    
        out[u] = tiempo++;
    }
};
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, q;
    cin >> n >> q;

    vi a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    SegmentTree st(a);

    while(q--){
        int l, r, xMin, xMax;
        cin >> l >> r >> xMin >> xMax;

        cout << st.count(l, r, xMin, xMax) << "\n";
    }

    return 0;
}
