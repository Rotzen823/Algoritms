#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

struct MCMF {
	using F = ll; using C = ll; // flow type, cost type
	struct Edge { int to, rev; F flo, cap; C cost; };
	int N0;
    const ll  INF = 1e18; 
	vector<C> p, dist;
	vii pre;
	vector<vector<Edge>> adj;

	void init(int _N) {
	    N0 = _N;
		p.resize(N0); dist.resize(N0); pre.resize(N0); adj.resize(N0);
    }
	void ae(int u, int v, F cap, C cost) {
	    assert(cap >= 0);
		adj[u].push_back({v,(int) adj[v].size(), 0, cap, cost});
		adj[v].push_back({u,(int) adj[u].size() - 1, 0, 0, -cost});
	}
	bool path(int s, int t) { // send flow through lowest cost path
		dist.assign(N0,INF);
		using T = pair<C, int>;     // (distance, vtx)
		priority_queue<T, vector<T>, greater<T>> todo;
		todo.push({dist[s] = 0,s});
		while (todo.size()) { // Dijkstra
			T x = todo.top(); todo.pop();
			if (x.first > dist[x.second]) continue;
			for(auto e : adj[x.second]) { // all weights should be non-negative
				if(e.flo < e.cap && ( dist[e.to] > x.first + e.cost + p[x.second] - p[e.to])){
					dist[e.to] = x.first + e.cost + p[x.second]-p[e.to]; // pi function
					pre[e.to] = {x.second, e.rev};
					todo.push({dist[e.to],e.to});
				}
			}
		} // if costs are doubles, add some EPS so you don't traverse ~0-weight cycle repeatedly
		return dist[t] != INF; // true if augmenting path
	}
	pair<F,C> calc(int s, int t, bool hasNegCost = false) {
	    assert(s != t);
	    if(hasNegCost) { // take care negative flow
            for(int k=0; k<N0; k++) for(int i=0; i<N0; i++) for(auto e : adj[i]) // Bellman-Ford, 0 index
                if (e.cap && (p[e.to] > p[i]+e.cost) ) p[e.to] = p[i]+e.cost;
	    }

		F totFlow = 0; C totCost = 0;
		while (path(s,t)) { // p -> potentials for Dijkstra
			for(int i=0; i<N0; i++) p[i] += dist[i]; // don't matter for unreachable
			F df = INF;
			for (int x = t; x != s; x = pre[x].first) {
				Edge& e = adj[pre[x].first][adj[x][pre[x].second].rev];
				if(df > e.cap-e.flo) df = e.cap-e.flo;
            }
            // if we want to do fixed flow target K, just limit totFlow to upto K
			// df = min(df, K - totFlow; and break after the backtrack df adjustment if we can reach K in this iteration
			totFlow += df; totCost += (p[t]-p[s])*df;
			for (int x = t; x != s; x = pre[x].first) {
				Edge& e = adj[x][pre[x].second];
				e.flo -= df;
				adj[pre[x].first][e.rev].flo += df;
			}
		} // get max flow you can send along path
		return {totFlow, totCost};
	}
};

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m;
    cin >> n >> m;

    MCMF flow;
    flow.init(n);

    for(int k = 0; k < m; k++){
        int a, b;
        ll f, c;
        cin >> a >> b >> f >> c;
        flow.ae(a, b, f, c);
    }

    auto res = flow.calc(0, n - 1);

    cout << res.first << " " << res.second << "\n";

    return 0;
}
