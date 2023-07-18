#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;

class UnionFind{
    private:
        vi p, rank, setSize;
        int numSets;
    public:
        UnionFind(int N){
            setSize.assign(N, 1); numSets = N; rank.assign(N, 0); p.assign(N, 0);
            for(int k = 0; k < N; k++){
                p[k] = k;
            }
        }
        int findSet(int a){
            return a == p[a] ? a : (p[a] = findSet(p[a]));
        }
        bool isSameSet(int a, int b){
            return findSet(a) == findSet(b);
        }
        void unionSet(int a, int b){
            if(isSameSet(a, b)){
                return;
            }

            int x = findSet(a), y = findSet(b);
            if(rank[y] > rank[x]){
                swap(x, y);
            }
            p[y] = x;
            setSize[x] += setSize[y];
            if(rank[x] == rank[y]){
                rank[x]++;
            }
            numSets--;
        }
        int sizeOfSet(int a){
            return setSize[findSet(a)];
        }
        int numDisjointSets(){
            return numSets;
        }
};

typedef struct Edge{
    int a;
    int b;
    int c;

    friend bool operator<(const Edge& a, const Edge& b) {
        return a.c < b.c;
    }
}Edge;

struct Grafo{
    int V;
    vector<Edge> edges;

    void init(int _V){
        V = _V;
    }

    void ae(int a, int b, int c){ edges.push_back({a, b, c}); }

    int kruskal(){
        sort(edges.begin(), edges.end());
        UnionFind uf(V);

        int res = 0;
        for(auto x : edges){
            if(uf.numDisjointSets() == 1){
                break;
            }

            if(!uf.isSameSet(x.a, x.b)){
                res += x.c;
                uf.unionSet(x.a, x.b);
            }
        }

        return res;
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
        int a, b, c;
        cin >> a >> b >> c;
        g.ae(a, b, c);
        g.ae(b, a, c);
    }

    cout << g.kruskal() << "\n";

    return 0;
}
