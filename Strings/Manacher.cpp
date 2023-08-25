#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

string preProcessManacher(string S) {
	// WARNING: S must not contain any of ^#$ characters
	int n = S.size();
	if (n == 0) {
		return "^$";
	}
	
	string T(2 * n + 3, '#');
	T[0] = '^';
	for (int i = 0; i < n; i++) {
		T[2 * i + 1] = '#';
		T[2 * i + 2] = S[i];
	}

	T[2 * n + 1] = '#';
	T[2 * n + 2] = '$';

	return T;
}

string manacher(string S, string T) {
	int C = 0, R = 0, maxLen = 0, centerIndex = 0;
	int n = T.size();
	// Number of palindromes centered at i
	vi P(n);

	for (int i = 1; i < n - 1; i++) {
		int j = 2 * C - i;
		P[i] = (R > i) ? min(R - i, P[j]) : 0;

		// Expand palindrome centered at i
		while (T[i + 1 + P[i]] == T[i - 1 - P[i]]) {
			P[i]++;
		}

		// If a longer palindrome is found, update center
		if (i + P[i] > R) {
			C = i;
			R = i + P[i];
		}
		// Store the center and length of longest palindrome
		if (P[i] > maxLen) {
			maxLen = P[i];
			centerIndex = i;
		}
	}

	return S.substr((centerIndex - 1 - maxLen) / 2, maxLen);
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

	string s;
	cin >> s;

	cout << manacher(s, preProcessManacher(s)) << "\n";

    return 0;
}
