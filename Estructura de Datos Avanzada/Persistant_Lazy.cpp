#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

typedef struct Node{
    int l;
    int r;
    int st;
    int flag;
    bool hasFlag;
}Node;

class PersistanLazy{
    private:
        int N, NODES;
        vector<Node> nodes;

        void build(int p, int id, int value, int L, int R){
            if(p >= (int)nodes.size()){
                nodes.push_back({0, 0, 0, 0, false});
            }

            if(L == R){
                nodes[p].st = value;
                return;
            }

            int m = (L + R) / 2;

            if(id <= m){
                if(!nodes[p].l){
                    nodes[p].l = ++NODES;
                }

                build(nodes[p].l, id, value, L, m);
            }
            else{
                if(!nodes[p].r){
                    nodes[p].r = ++NODES;
                }

                build(nodes[p].r, id, value, m + 1, R);
            }

            int op1 = 0, op2 = 0;
            if(nodes[p].l){
                op1 = nodes[nodes[p].l].st;
            }

            if(nodes[p].r){
                op2 = nodes[nodes[p].r].st;
            }

            nodes[p].st = op1 + op2;
        }

        int newlazykid(int node, int delta, int L, int R) {
            int p = ++NODES;
            nodes.push_back({0, 0, 0, 0, false});

            nodes[p].l = nodes[node].l;
            nodes[p].r = nodes[node].r;
            //nodes[p].flag = nodes[node].flag;  need this since lazy kid might be lazy before
            nodes[p].hasFlag = true;
            
            /* range increase */
            nodes[p].flag = delta;
            nodes[p].st = (R - L + 1) * delta;
            /* edit depending on the problem */     
            return p;
        }

        int newParent(int L, int R){
            int p = ++NODES;
            nodes.push_back({0, 0, 0, 0, false});
            nodes[p].st = nodes[L].st + nodes[R].st;
            nodes[p].l = L; nodes[p].r = R;

            return p;
        }

        void propagate(int p, int L, int R) {
            if (nodes[p].hasFlag) {
                if (L != R) { // spread the laziness
                    int m = (L + R) / 2;
                    nodes[p].l = newlazykid(nodes[p].l, nodes[p].flag, L, m);
                    nodes[p].r = newlazykid(nodes[p].r, nodes[p].flag, m + 1, R);
                }
                // reset flag
                nodes[p].hasFlag = false;
            }
        }

        int update(int a, int b, int x, int p, int L, int R) {
            if (b < L || R < a)   return p;
            if (a <= L && R <= b) return newlazykid(p, x, L, R); 
            propagate(p, L, R); // always do this before going down
            int m = (L + R) / 2;
            return newParent(update(a, b, x, nodes[p].l, L, m), update(a, b, x, nodes[p].r, m + 1, R));
        }

        int query(int a, int b, int p, int L, int R) {
            if (b < L || R < a)   return 0;
            if (a <= L && R <= b) return nodes[p].st;
            propagate(p, L, R); // always do this before going down
            int m = (L + R) / 2;
            return query(a, b, nodes[p].l, L, m) + query(a, b, nodes[p].r, m + 1, R);
        }
    public:
        PersistanLazy(int _N){
            N = _N;
            NODES = 0;
        }

        void build(int p, int id, int value){
            build(p, id, value, 0, N - 1);
        }

        int update(int a, int b, int x, int p){
            return update(a, b, x, p, 0, N - 1);
        }

        int query(int a, int b, int p){
            return query(a, b, p, 0, N - 1);
        }
};

int main() {
    std::cin.tie(nuintptr);
    std::ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    vi tetra;
    tetra.push_back(0);

    PersistanLazy st(n);
    for(int k = 0; k < n; k++){
        int x;
        cin >> x;
        st.build(0, k, x);
    }

    int t = 0;
    while(m--){
        char op;
        int a, b, p;
        int x;
        cin >> op;
        switch(op){
            case 'Q':
            cin >> a >> b;
            cout << st.query(a - 1, b - 1, tetra[t]) << "\n";
            break;
            case 'U':
            cin >> a >> b >> x;
            p = st.update(a - 1, b - 1, x, tetra[t]);
            tetra.push_back(p);
            t = tetra.size() - 1;
            break;
            case 'T':
            cin >> t;
            break;
        }
    }

    return 0;
}
