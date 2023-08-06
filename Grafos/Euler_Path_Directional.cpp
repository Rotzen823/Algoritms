#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

struct Grafo{
    int V;
    int st, end;
    vector<vi> adj;
    vector<bool> ready;
    vi tin, low, path, in;
    int numC, timer;
    stack<int> pila;

    void init(int _V){
        V = _V;
        adj.assign(V, vi());
        ready.assign(V, false);
        tin.assign(V, 0); low.assign(V, 0); in.assign(V, 0);
        numC = 0; timer = 1;
        st = end = -1;
    }

    void ae(int a, int b){ 
        adj[a].push_back(b); 
        in[b]++;
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
                if (u == v) {
                    break;
                }
            }
        }
    }

    void dfs(int u){
        if(ready[u]){
            return;
        }
        ready[u] = true;

        for(int v : adj[u]){
            dfs(v);
        }
    }

    bool isSuperConected(){
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
        tarjan(st);

        if(numC > 1){
            return false;
        }

        for(i = 0; i < V; i++){
            if(!tin[i] && adj[i].size() > 0){
                return false;
            }
        }
        return true;
    }

    bool isConected(int u){
        dfs(u);
        for(int i = 0; i < V; i++){
            if(!ready[i] && adj[i].size() > 0){
                return false;
            }
        }
        return true;
    }

    int isEulerian(){
        for(int i = 0; i < V; i++){
            int ax = (int) adj[i].size();
            if (ax != in[i]){
                if(ax == in[i] + 1 && st == -1){
                    st = i;
                }
                else if(ax + 1 == in[i] && end == -1){
                    end = i;
                }
                else{
                    return 0;
                }
            }
        }

        if(st == -1 && end == -1){
            if(isSuperConected()){
                findEulerPath(st);
                return 2;
            }
            return 0;
        }

        if(isConected(st)){
            ae(end, st);
            findEulerPath(end);
            return 1;
        }
        return 0;
    }

    void findEulerPath(int u){
        while(!adj[u].empty()){
            int v = adj[u].back();
            adj[u].pop_back();
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
        cout << g.path[g.path.size() - 1] + 1;
        for(int i = (int) g.path.size() - 2; i >= 0; i--){
            cout << " " << g.path[i] + 1;
        }
        cout << "\n";
    }
    else{
        cout << "No hay camino de Euler\n";
    }

    return 0;
}
