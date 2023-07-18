#include <bits/stdc++.h>
#define INF 200000000

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

struct Grafo{
    int V;
    vector<vi> adj;
    vector<bool> ready;
    vi inDegree, sorted;

    void init(int _V){
        V = _V;
        adj.assign(V, vi());
        inDegree.assign(V, 0);
        sorted.assign(V, 0);
    }

    void ae(int a, int b){ adj[a].push_back(b); }

    bool topologicalSort(){
        queue<int> cola;
        int u;

        for(int k = 0; k < V; k++){
            for(int u : adj[k]){
                inDegree[u]++;
            }
        }

        for(int k = 0; k < V; k++){
            if(inDegree[k] == 0){
                cola.push(k);
            }
        }

        for(int k = 0; k < V; k++){
            if(cola.empty()){
                return false;
            }
            sorted[k] = u = cola.front(); cola.pop();
            
            for(int v : adj[u]){
                inDegree[v]--;

                if(inDegree[v] == 0){
                    cola.push(v);
                }
            }
        }

        return true;
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

    if(g.topologicalSort()){
        cout << g.sorted[0];
        for(int k = 1; k < n; k++){
            cout << " " << g.sorted[k];
        }
        cout << "\n";
    }
    else{
        cout << "-1\n";
    }

    return 0;
}
