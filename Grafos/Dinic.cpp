#include <bits/stdc++.h>

#define ENDL '\n'

using namespace std;

typedef long long ll;
typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

int n, m;

struct Dinic {
    using F = ll; // flow type
    struct Edge { int to; F flo, cap; };
    int N;
    vector<Edge> eds;
    vector<vi> adj;
    void init(int _N) { N = _N; adj.resize(N), cur.resize(N); }
    void ae(int u, int v, F cap, F rcap = 0) { assert(min(cap,rcap) >= 0);
        adj[u].push_back(eds.size()); eds.push_back({v, 0, cap});
        adj[v].push_back(eds.size()); eds.push_back({u, 0, rcap});
    }
    vi lev;
    vector<vi::iterator> cur;
    bool bfs(int s, int t) {
        lev = vi(N,-1); for (int i = 0; i < N; i++) cur[i] = begin(adj[i]);
        queue<int> q({s}); lev[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int e : adj[u]) {
                const Edge& E = eds[e];
                int v = E.to; if (lev[v] < 0 && E.flo < E.cap)
                    q.push(v), lev[v] = lev[u]+1;
            }
        }
        return lev[t] >= 0;
    }
    F dfs(int v, int t, F flo) {
        if (v == t) return flo;
        for (; cur[v] != end(adj[v]); cur[v]++) {
            Edge& E = eds[*cur[v]];
            if (lev[E.to]!=lev[v]+1||E.flo==E.cap) continue;
            F df = dfs(E.to,t,min(flo,E.cap-E.flo));
            if (df) { E.flo += df; eds[*cur[v]^1].flo -= df;
                return df; } // saturated >=1 one edge
        }
        return 0;
    }
    void reset(){//Agregar metodo reset para hacer mas de un MaxFlow
        for(int i = 0; i < (int)eds.size(); i++){
            eds[i].flo = 0;
        }
    }
    F maxFlow(int s, int t) {
        //reset();
        F tot = 0; while (bfs(s,t)) while (F df =
            dfs(s,t,numeric_limits<F>::max())) tot += df;
        return tot;
    }
};

/*
    Una forma de mostrar los caminos por donde paso el flujo
    varia mucho dependiendo el problema solo tomar como base.
    *si no es necesario mostrar el camino del flujo no es
        necesario.
*/
Dinic dinic;
stack <int> st;
vi vis;

void printFlow(int p) {
    
    if(p == n){
        st.push(p);
        return;        
    }

    if(p == 1){
        for(int i = 0; i < (int)dinic.adj[p].size(); i++){

            int e = dinic.adj[p][i];

            if(dinic.eds[e].flo > 0 && !vis[e]){
                vis[e] = 1;
                printFlow(dinic.eds[e].to);
                
                cout << st.size() + 1 << ENDL;
                cout << "1";

                while(!st.empty()){
                    cout << " " << st.top();
                    st.pop();
                }
                cout << ENDL;
            }
        }
    }

    for(int i = 0; i < (int)dinic.adj[p].size(); i++){

        int e = dinic.adj[p][i];

        if(dinic.eds[e].flo > 0 && !vis[e]){
            vis[e] = 1;
            printFlow(dinic.eds[e].to);
            st.push(p);
            return;
        }

    }

}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;

    Dinic dinic;
    dinic.init(n + 1);

    for(int i = 0; i < m; i++){
        int a, b, c;
        cin >> a >> b >> c;
        dinic.ae(a, b, c);
    }   

    cout << dinic.maxFlow(1, n);

    //Para saber el Corte minimo
    dinic.bfs(0, n + n + 1);
    
    /*
        Ejecutado el bfs, en vector lev
        contendra lev[i] >= 0 si se trata de un nodo alcanzable,
        lev[i] < 0 si se trata de un nodo no alcanzable.
        Una arista de corte sera aquella que una un nodo alcanzable
        con uno no alcanzable (lev[u] >= 0 && lev[v] < 0)

        *Bastaria con recorer el grafo y comprobar si la arista
         es un punto de corte.

    */

    //Ejemplo
    for(int i = 0; i < n + n + 2; i++){
        for(int j = 0; j < (int)dinic.adj[i].size(); j++){
            int v = dinic.eds[dinic.adj[i][j]].to;
            if(dinic.lev[i] >= 0 && dinic.lev[v] < 0)
                cout << i << " : " << v << ENDL;
        }
    }
    //Es todo para saber el corte minimo

    return 0;
}
