#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

typedef struct Edge{
    int a;
    int b;
    int c;

    friend bool operator<(const Edge& a, const Edge& b) {
        return a.c > b.c;
    }
}Edge;

struct Grafo{
    int V;
    vector<vii> adj;
    vector<bool> ready;

    void init(int _V){
        V = _V;
        adj.assign(V, vii());
        ready.assign(V, false);
    }

    void ae(int a, int b, int c){ adj[a].push_back({b, c}); }

    int prim(){
        priority_queue<Edge> q;
        q.push({-1, 0, 0});
        int costo = 0;
        Edge edge;
        for(int k = 0; k < V; k++){
            do{
                edge = q.top();
                q.pop();   
            }while(ready[edge.b]);
            costo += edge.c;
            ready[edge.b] = true;
            for(auto e : adj[edge.b]){
                int v = e.first;
                if(!ready[v]){
                    q.push({edge.b, v, e.second});
                }
            }
        }
        return costo;
    }

};

int main() { 
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m;
    cin >> n >> m;
    Grafo g;
    g.init(n);

    while(m--){
        int a, b, c;
        cin >> a >> b >> c;
        g.ae(a, b, c);
        g.ae(b, a, c);
    }

    cout << g.prim() << "\n";

    return 0;
}
