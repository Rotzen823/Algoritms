#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

struct Grafo{
    int V;
    vector<vi> adj, ancestros;
    vector<bool> ready;
    vi depth;

    void init(int _V){
        V = _V;
        adj.assign(V, vi());
        ancestros.assign(V, vi(32, 0));
        depth.assign(V, 0);
        ready.assign(V, false);
    }

    void ae(int a, int b){ adj[a].push_back(b); }

    void ancest(int v, int anc, int p){
        if(!ancestros[anc][p - 1]){
            return;
        }
        ancestros[v][p] = ancestros[anc][p - 1];
        ancest(v, ancestros[anc][p - 1], p + 1);
    }

    void buildAncest(int x){
        queue<int> q;
        q.push(x);
        ready[x] = true;
        ancestros[x][0] = x;
        depth[x] = 1;
        while(!q.empty()){
            int v = q.front(); q.pop();

            for(int u : adj[v]){
                if(ready[u]){
                    continue;
                }
                ancestros[u][0] = u;
                depth[u] = depth[v] + 1;
                ancest(u, v, 1);
                q.push(u);
                ready[u] = true;
            }
        }
    }

    int lowbit(int x){
        return (-x) & x;
    }

    int ancestK(int v, int k){
        if(k == 0){
            return v;
        }

        int x = lowbit(k);
        int p = 32 - __builtin_clz(x);

        return ancestK(ancestros[v][p], k - x);
    }

    int lca(int a, int b){
        if(depth[a] > depth[b]){
            swap(a, b);
        }

        b = ancestK(b, depth[b] - depth[a]);

        int in = 0, fin = V, med;

        int x, y;
        while(in < fin){
            med = (in + fin) / 2;
            
            x = ancestK(a, med); y = ancestK(b, med);

            if(x == y){
                fin = med;
            }
            else{
                in = med + 1;
            }
        }

        return ancestK(a, in);
    }
    
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m;
    cin >> n >> m;

    Grafo g;
    g.init(n);

    for(int k = 1; k < n; k++){
        int a, b;
        cin >> a >> b;
        g.ae(a, b);
        g.ae(b, a);
    }

    g.buildAncest(0);

    while(m--){
        int a, b;
        cin >> a >> b;

        int anc = g.lca(a, b);
        cout << anc << "\n";
    }

    return 0;
}
