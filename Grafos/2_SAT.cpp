#include <bits/stdc++.h>
 
using namespace std;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

struct Grafo{
    int V;
    vector<vi> adj;
    vector<bool> ready;
    vi tin, low, color;
    int numC, timer;
    stack<int> pila;

    void init(int _V){
        V = _V;
        adj.assign(V, vi());
        ready.assign(V, false);
        tin.assign(V, 0); low.assign(V, 0); color.assign(V, 0);
        numC = 0; timer = 1;
    }

    void tarjan(int u) {
        tin[u] = low[u] = timer++;
        ready[u] = true;
        pila.push(u);

        for (int v : adj[u]) {
            if (!tin[v]) {
                tarjan(v);
            }

            if (ready[v]) {
                low[u] = min(low[u], low[v]);
            }
        }

        if (low[u] == tin[u]) {
            numC++;
            while (true) {
                int v = pila.top();
                pila.pop();
                ready[v] = false;
                color[v] = numC;
                if (u == v) {
                    break;
                }
            }
        }
    }

    bool solve2Sat() {
        for (int k = 0; k < V; k++) {
            if (!tin[k]) {
                tarjan(k);
            }
        }
        
        for (int k = 0; k < V; k += 2) {
            if (color[k] == color[k + 1]) {
                return false;
            }
        }
        return true;
    }

    void add_edge(int a, bool na, int b, bool nb) {
        a <<= 1;
        b <<= 1;
        
        int notA = a + 1, notB = b + 1;
        if (na) {
            swap(a, notA);
        }
        if (nb) {
            swap(b, notB);
        }
        
        adj[notA].push_back(b);
        adj[notB].push_back(a);
    }
};
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    Grafo g;
    g.init(n * 2);

    for (int k = 0; k < m; k++) {
        int a, b, na, nb;
        cin >> a >> na >> b >> nb;
        g.add_edge(a, na, b, nb);
    }

    if (g.solve2Sat()) {
        cout << "Hay solucion\n";
    } else {
        cout << "No hay solucion\n";
    }

    return 0;
}
