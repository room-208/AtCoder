#define _USE_MATH_DEFINES

#include <algorithm>
#include <atcoder/fenwicktree>
#include <atcoder/lazysegtree>
#include <atcoder/maxflow>
#include <atcoder/mincostflow>
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
using mint = modint998244353;  // modint1000000007 static_modint<1000000009>;
using ll = long long;
using ull = unsigned long long;

ll dfs(ll N, ll R, ll B, ll X, ll Y) {
  if (N == 1) {
    return B;
  }
  return dfs(N - 1, R + R * X + B, R * X * Y + B * Y, X, Y);
}

int main() {
  ll N, X, Y;
  cin >> N >> X >> Y;

  cout << dfs(N, 1, 0, X, Y) << endl;
}