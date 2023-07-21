#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

struct Grafo{
    int V;
    vector<vi> adj;
    vector<bool> ready;

    void init(int _V){
        V = _V;
        adj.assign(V, vi());
        ready.assign(V, false);
    }

    void ae(int a, int b){ adj[a].push_back(b); }

    void dfs(int u){
        if(ready[u]){
            return;
        }
        ready[u] = true;

        cout << u << " ";

        for(int v : adj[u]){
            dfs(v);
        }
    }

    void bfs(int x){
        queue<int> q;
        q.push(x);
        ready[x] = true;

        cout << x << " ";
        while(!q.empty()){
            int u = q.front(); q.pop();

            for(int v : adj[u]){
                if(!ready[v]){
                    ready[v] = true;
                    cout << v << " ";
                    q.push(v);
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
        g.ae(b, a);
    }

    g.dfs(0);
    cout << "\n";
    g.ready.assign(n, false);
    g.bfs(0);
    cout << "\n";

    return 0;
}
