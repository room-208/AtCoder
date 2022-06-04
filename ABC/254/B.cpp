#define _USE_MATH_DEFINES

#include <algorithm>
#include <atcoder/fenwicktree>
#include <atcoder/lazysegtree>
#include <atcoder/modint>
#include <atcoder/scc>
#include <atcoder/segtree>
#include <bitset>
#include <cmath>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using namespace atcoder;
using ll = long long;
using ull = unsigned long long;

constexpr int INF_int = 1e9;
constexpr ll INF_ll = 1e18;
const double EPS = 1e-10;

ll COM(ll n, ll r) {
  ll res = 1;
  for (ll i = 0; i < r; i++) {
    res *= (n - i);
    res /= (i + 1);
  }
  return res;
}

int main() {
  int N;
  cin >> N;
  vector<vector<ll>> A(N);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j <= i; j++) {
      A[i].push_back(COM(i, j));
    }
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j <= i; j++) {
      cout << A[i][j] << " ";
    }
    cout << endl;
  }
}