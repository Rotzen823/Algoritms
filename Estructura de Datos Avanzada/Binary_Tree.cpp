#include<bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<int> vi;

struct BinaryTree{
    vector<iii> tree;

    void add(int dato){
        if(tree.empty()){
            tree.push_back(iii(dato, ii(-1, -1)));
            return;
        }

        add(dato, 0);
    }

    void add(int dato, int v){
        if(dato < tree[v].first){
            if(tree[v].second.first == -1){
                tree.push_back(iii(dato, ii(-1, -1)));
                tree[v].second.first = tree.size() - 1;
            }
            else{
                add(dato, tree[v].second.first);
            }
        }
        else{
            if(tree[v].second.second == -1){
                tree.push_back(iii(dato, ii(-1, -1)));
                tree[v].second.second = tree.size() - 1;
            }
            else{
                add(dato, tree[v].second.second);
            }
        }
    }

    void preorden(int v = 0){
        cout << tree[v].first << " ";

        if(tree[v].second.first != -1){
            preorden(tree[v].second.first);
        }

        if(tree[v].second.second != -1){
            preorden(tree[v].second.second);
        }
    }

    void inorden(int v = 0){
        if(tree[v].second.first != -1){
            inorden(tree[v].second.first);
        }

        cout << tree[v].first << " ";

        if(tree[v].second.second != -1){
            inorden(tree[v].second.second);
        }
    }

    void posorden(int v = 0){
        if(tree[v].second.first != -1){
            posorden(tree[v].second.first);
        }

        if(tree[v].second.second != -1){
            posorden(tree[v].second.second);
        }

        cout << tree[v].first << " ";
    }

};


int main(){
    int n;
    cin >> n;

    BinaryTree tree;

    for(int k = 0; k < n; k++){
        int x;
        cin >> x;
        tree.add(x);
    }

    tree.preorden();
    cout << "\n";
    tree.inorden();
    cout << "\n";
    tree.posorden();
    cout << "\n";
    
    return 0;
}
