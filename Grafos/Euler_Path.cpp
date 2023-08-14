#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;

struct Grafo{
    int V, st, end;
    struct Edge { int to; bool used; };
    vector<vi> adj;
    vector<Edge> edges;
    vector<bool> ready;
    vi path;

    void init(int _V){
        V = _V;
        adj.assign(V, vi());
        ready.assign(V, false);
        st = end = 0;
    }

    void ae(int a, int b){ 
        adj[a].push_back(edges.size()); edges.push_back({b, false});
        adj[b].push_back(edges.size()); edges.push_back({a, false}); 
    }

    void dfs(int u){
        if(ready[u]){
            return;
        }
        ready[u] = true;

        for(int e : adj[u]){
            dfs(edges[e].to);
        }
    }

    bool isConected(){
        int i;
        for(i = 0; i < V; i++){
            if(adj[i].size() > 0){
                break;
            }
        }

        if(i == V){
            return true;
        }
        st = end = i;
        dfs(st);

        for(i = 0; i < V; i++){
            if(!ready[i] && adj[i].size() > 0){
                return false;
            }
        }
        return true;
    }

    int isEulerian(){
        if(!isConected()){
            return 0;
        }

        int odd = 0;
        bool first = true;
        for(int i = 0; i < V; i++){
            if (adj[i].size() & 1){
                odd++;
                if(first){
                    first = false;
                    st = i;
                }
                else{
                    end = i;
                }
            }
        }

        if(odd == 0){
            findEulerPath(st);
            return 2;
        }
        if(odd == 2){
            ae(st, end);
            ae(end, st);
            findEulerPath(st);
            return 1;
        }
        return 0;
    }

    void findEulerPath(int u){
        while(!adj[u].empty()){
            int e = adj[u].back();
            adj[u].pop_back();
            if(edges[e].used){
                continue;
            }
            int v = edges[e].to;
            edges[e^1].used = true;
            findEulerPath(v);
        }
        path.push_back(u);
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
        a--; b--;
        g.ae(a, b);
    }

    int ax = g.isEulerian();
    if(ax){
        if(ax == 2){
            cout << "Circuito de Euler:\n";
        }
        else{
            cout << "Camino de Euler:\n";
            g.path.pop_back();
        }
        cout << g.path[0];
        for(int i = 1; i < (int) g.path.size(); i++){
            cout << " " << g.path[i];
        }
        cout << "\n";
    }
    else{
        cout << "No hay camino de Euler\n";
    }

    return 0;
}
