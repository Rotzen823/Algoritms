#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

struct Grafo{
    int V;
    vector<vi> adj;
    vector<bool> ready;
    vi tin, low;
    int numC, timer;
    stack<int> pila;

    void init(int _V){
        V = _V;
        adj.assign(V, vi());
        ready.assign(V, false);
        tin.assign(V, 0); low.assign(V, 0);
        numC = 0; timer = 1;
    }

    void ae(int a, int b){ adj[a].push_back(b); }

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
                if (u == v) {
                    break;
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
        int a, b;
        cin >> a >> b;
        g.ae(a, b);
    }

    for (int k = 0; k < n; k++) {
        if (!g.tin[k]) {
            g.tarjan(k);
        }
    }
    cout << g.numC << "\n";

    return 0;
}
