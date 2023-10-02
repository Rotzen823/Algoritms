#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int sacarArea(vii &puntos){
    int n = puntos.size();
    int area = 0;
    for(int k = 0; k < n; k++){
        int j = (k + 1) % n;
        area += puntos[k].first * puntos[j].second - puntos[j].first * puntos[k].second;
    }

    return abs(area) / 2;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vii puntos;
    for(int k = 0; k < n; k++){
        int x, y;
        cin >> x >> y;
        puntos.push_back(ii(x, y));
    }

    cout << sacarArea(puntos);
  

  return 0;
}
