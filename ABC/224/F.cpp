//#define _GLIBCXX_DEBUG
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <time.h>

#include <algorithm>
#include <atcoder/fenwicktree>
#include <atcoder/lazysegtree>
#include <atcoder/modint>
#include <atcoder/scc>
#include <atcoder/segtree>
#include <cmath>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
using namespace atcoder;
using mint = modint998244353;

namespace seg {
mint op(mint a, mint b) { return a + b; }
mint e() { return 0; }
}  // namespace seg

int main() {
  string S;
  cin >> S;
  int N = S.size();
  reverse(S.begin(), S.end());

  vector<mint> a(N);
  for (size_t i = 0; i < N; i++) {
    a[i] = S[i] - '0';
  }

  segtree<mint, seg::op, seg::e> sgt(N);
  for (size_t i = 0; i < N; i++) {
    sgt.set(i, mint(2).pow(N - 1 - i) * mint(10).pow(i));
  }

  mint ans = a[0] * mint(2).pow(N - 1);
  for (size_t i = 1; i < N; i++) {
    ans += a[i] * (sgt.prod(0, i) * mint(2).inv() +
                   mint(2).pow(N - 1 - i) * mint(10).pow(i));
  }

  cout << ans.val() << endl;
}