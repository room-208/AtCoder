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
using mint = modint998244353;  // modint1000000007 static_modint<1000000009>;

const long long INF_ll = 1000000000000000000LL;

//最大・最小化
template <class T>
bool chmax(T &a, const T &b) {
  if (a < b) {
    a = b;
    return 1;
  }
  return 0;
}
template <class T>
bool chmin(T &a, const T &b) {
  if (b < a) {
    a = b;
    return 1;
  }
  return 0;
}

int main() {
  int N;
  cin >> N;
  long long X, Y;
  cin >> X >> Y;
  vector<long long> A(N), B(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }
  for (int i = 0; i < N; i++) {
    cin >> B[i];
  }

  vector<long long> dp((1 << N), INF_ll);
  dp[0] = 0;
  for (int S = 1; S < (1 << N); S++) {
    vector<int> vec;
    for (int i = 0; i < N; i++) {
      if (S & (1 << i)) {
        vec.push_back(i);
      }
    }

    for (int i = 0; i < N; i++) {
      if (S & (1 << i)) {
        long long cost = llabs(A[i] - B[(int)vec.size() - 1]) * X;
        int n = upper_bound(vec.begin(), vec.end(), i) - vec.begin();
        cost += Y * ((int)vec.size() - n);
        chmin(dp[S], dp[S & ~(1 << i)] + cost);
      }
    }
  }

  cout << dp[(1 << N) - 1] << endl;
}