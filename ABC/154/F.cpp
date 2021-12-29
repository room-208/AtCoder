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
using mint = modint1000000007;

const int MOD = 1000000007;
const int INF_int = 1000000000;
const long long INF_ll = 1000000000000000000LL;
const int COM_MAX = 2500000;

long long fac[COM_MAX], finv[COM_MAX], inv[COM_MAX];

// テーブルを作る前処理
void COMinit() {
  fac[0] = fac[1] = 1;
  finv[0] = finv[1] = 1;
  inv[1] = 1;
  for (int i = 2; i < COM_MAX; i++) {
    fac[i] = fac[i - 1] * i % MOD;
    inv[i] = MOD - inv[MOD % i] * (MOD / i) % MOD;
    finv[i] = finv[i - 1] * inv[i] % MOD;
  }
}

// 二項係数計算
long long COM(int n, int k) {
  if (n < k) return 0;
  if (n < 0 || k < 0) return 0;
  return fac[n] * (finv[k] * finv[n - k] % MOD) % MOD;
}

mint A(int x, int y) {
  vector<mint> dp(2500000);
  dp[0] = 1;
  for (int z = 1; z <= x + y; z++) {
    dp[z] = dp[z - 1] * 2;
    if (z > x) {
      dp[z] -= COM(z - 1, x);
    }
    if (z > y) {
      dp[z] -= COM(z - 1, y);
    }
  }

  mint res = 0;
  for (int z = 0; z <= x + y; z++) {
    res += dp[z];
  }
  return res;
}

int main() {
  int r1, c1, r2, c2;
  cin >> r1 >> c1 >> r2 >> c2;

  COMinit();

  mint ans = A(r2, c2) - A(r2, c1 - 1) - A(r1 - 1, c2) + A(r1 - 1, c1 - 1);

  cout << ans.val() << endl;
}