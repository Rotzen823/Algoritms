#include<bits/stdc++.h>
#define MAX 35

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;

struct Ford_Fulkerson{
    using F = ll;
    struct Edge { int to; F flo, cap; };
    int N;
    vector<Edge> eds;
    vector<vi> adj;
    void init(int _N) { N = _N; adj.resize(N), cur.resize(N); }
    void ae(int u, int v, F cap, F rcap = 0) { assert(min(cap,rcap) >= 0);
        adj[u].push_back(eds.size()); eds.push_back({v, 0, cap});
        adj[v].push_back(eds.size()); eds.push_back({u, 0, rcap});
    }

    F dfs(int v, int t, F flo) {
        if (v == t) return flo;
        for (int x : adj[v]) {
            Edge& E = eds[x];
            if (E.flo==E.cap) continue;
            F df = dfs(E.to,t,min(flo,E.cap-E.flo));
            if (df) { E.flo += df; eds[*cur[v]^1].flo -= df;
                return df; } // saturated >=1 one edge
        }
        return 0;
    }

    F maxFlow(int s, int t) {
        F tot = 0; while 
        while (F df = dfs(s,t,numeric_limits<F>::max())) tot += df;
        return tot;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m;
    cin >> n >> m;

    Ford_Fulkerson ff;
    ff.init(n + 1);

    for(int i = 0; i < m; i++){
        int a, b, c;
        cin >> a >> b >> c;
        dinic.ae(a, b, c);
    }   

    cout << dinic.maxFlow(1, n) << "\n";

    return 0;
}
