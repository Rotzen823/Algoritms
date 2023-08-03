#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

typedef struct Nodo{
    char x;
    int c;
    vi pref;
}Nodo;

struct Trie{
    vector<Nodo> trie;
    void init(){
        trie.push_back({' ', 0, vi()});
    }

    void update(string pal, int p = 0, int v = 0){
        trie[v].c++;

        if(p == (int)pal.length()){
            return;
        }

        for(int u : trie[v].pref){
            if(trie[u].x == pal[p]){
                update(pal, p + 1, u);
                return;
            }
        }

        trie.push_back({pal[p], 0, vi()});
        trie[v].pref.push_back(trie.size() - 1);
        update(pal, p + 1, trie.size() - 1);
    }

    int query(string pal, int p = 0,  int v = 0){
        if(p == (int)pal.length()){
            return trie[v].c;
        }

        for(int u : trie[v].pref){
            if(trie[u].x == pal[p]){
                return query(pal, p + 1, u);
            }
        }

        return 0;
    }
};

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    Trie tr;
    tr.init();

    while(n--){
        string ax;
        cin >> ax;

        tr.update(ax);
    }

    int m;
    cin >> m;

    while(m--){
        string ax;
        cin >> ax;
        cout << tr.query(ax) << "\n";
    }

    return 0;
}
