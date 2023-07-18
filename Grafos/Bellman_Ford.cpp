#include <bits/stdc++.h>
#define INF 100000000

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;

typedef struct Edge{
    int a;
    int b;
    int c;
}Edge;

struct Grafo{
    int V;
    vector<Edge> edges;
    vi dist;

    void init(int _V){
        V = _V;
    }

    void ae(int a, int b, int c){ edges.push_back({a, b, c}); }

    void bellman_ford(int x){
        dist.assign(V, INF);

        dist[x] = 0;
        bool bandera = true;
        while (bandera) {
            bandera = false;
            for (auto e : edges) {
                int a, b, w;
                a = e.a; b = e.b; w = e.c;
                if((dist[a] + w) < dist[b]){
                    dist[b] = dist[a] + w;
                    bandera = true;
                }
            }
        }
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

    g.bellman_ford(0);
    for(int k = 0; k < n; k++){
        cout << "0 -> " << k << ": " << g.dist[k] << "\n";
    }

    return 0;
}
