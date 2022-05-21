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

using mint_M = modint998244353;
using mint_K = static_modint<998244352>;

int main() {
  ll N, K, M;
  cin >> N >> K >> M;

  if (M % 998244353 == 0) {
    cout << 0 << endl;
    return 0;
  }

  mint_K a = mint_K(K).pow(N);
  mint_M ans = mint_M(M).pow(a.val());

  cout << ans.val() << endl;
}