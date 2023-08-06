#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
typedef pair <int, int> ii;
typedef vector <ii> vii;
typedef vector <int> vi;

struct Grafo{
    int V;
    vector<vi> adj;
    int dfsNumberCounter, dfsRoot, rootChildren;
    vi dfs_num, dfs_low, dfs_parent, articulation_vertex;

    void init(int _V){
        V = _V;
        adj.assign(V, vi());
        dfsNumberCounter = dfsRoot = rootChildren = 0;
        dfs_num.assign(V, -1); dfs_low.assign(V, 0);
        dfs_parent.assign(V, 0); articulation_vertex.assign(V, false);
    }

    void ae(int a, int b){ adj[a].push_back(b); }

    void articulationPointAndBridge(int u) {
        dfs_low[u] = dfs_num[u] = dfsNumberCounter++;      
        for (int v : adj[u]) {
            if (dfs_num[v] == -1) {   
                dfs_parent[v] = u;
                if (u == dfsRoot) rootChildren++;  
                articulationPointAndBridge(v);

                if (dfs_low[v] >= dfs_num[u]){
                    articulation_vertex[u] = true;  
                }                       
                if (dfs_low[v] > dfs_num[u]){
                    cout << "Edge: " << u << " - " << v << "\n";
                }                           
                dfs_low[u] = min(dfs_low[u], dfs_low[v]);       
            }
            else if (v != dfs_parent[u]){
                dfs_low[u] = min(dfs_low[u], dfs_num[v]); 
            }     
        } 
    }
};

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m;
    cin >> n >> m;

    Grafo g;
    g.init(n);

    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        g.ae(a, b);
        g.ae(b, a);
    }

    cout << "Bridges:\n";

    for(int i = 0; i < n; i++){
        if(g.dfs_num[i] == -1){
            g.dfsRoot = i;
            g.rootChildren = 0;
            g.articulationPointAndBridge(i);
            g.articulation_vertex[i] = (g.rootChildren > 1); //Caso especial
        }
    }

    cout << "Articulation Points:\n";

    for(int i = 0; i < n; i++){
        if(g.articulation_vertex[i]){
            cout << "Vertex " << i << "\n";
        }
    }

    return 0;
}
