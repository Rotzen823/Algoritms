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


int main() { 
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, q;
    cin >> n >> q;
    UnionFind uf(n);

    while(q--){
        int a, b;
        cin >> a >> b;
        uf.unionSet(a, b);
        
        cout << uf.numDisjointSets() << "\n";
    }

    return 0;
}
