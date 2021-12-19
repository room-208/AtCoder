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

//エッジ集合
struct Edge {
  int to;
  long long w;
  Edge(int to, long long w) : to(to), w(w) {}
};

using Graph_int = vector<vector<int>>;
using Graph_Edge = vector<vector<Edge>>;

// 深さ優先探索
void DFS(const Graph_Edge &G, int v, vector<vector<int>> &dp,
         const long long &i, mint &ans, int p = -1) {
  for (auto next_v : G[v]) {
    if (next_v.to == p) {
      continue;
    }

    DFS(G, next_v.to, dp, i, ans, v);
  }

  // 更新
  int one = 0;
  int zero = 0;
  long long bit = (1LL << i);
  mint two = mint(2).pow(i);
  for (auto c : G[v]) {
    if (c.to == p) {
      continue;
    }

    int c_one;
    int c_zero;

    if (c.w & bit) {
      c_one = 1 + dp[0][c.to];
      c_zero = dp[1][c.to];
    } else {
      c_one = dp[1][c.to];
      c_zero = 1 + dp[0][c.to];
    }

    // dp[v]
    dp[0][v] += c_zero;
    dp[1][v] += c_one;

    // 単体
    ans += two * c_one;

    // 複数の更新
    ans += two * zero * c_one;
    ans += two * one * c_zero;

    // 個数の更新
    zero += c_zero;
    one += c_one;
  }
}

int main() {
  int N;
  cin >> N;
  int M = N - 1;
  vector<int> u(M), v(M);
  vector<long long> w(M);
  for (int i = 0; i < M; i++) {
    cin >> u[i] >> v[i] >> w[i];
    u[i]--;
    v[i]--;
  }

  Graph_Edge G(N);
  for (int i = 0; i < M; i++) {
    G[u[i]].push_back(Edge(v[i], w[i]));
    G[v[i]].push_back(Edge(u[i], w[i]));
  }

  mint ans = 0;
  vector<vector<int>> dp(2, vector<int>(N));
  for (long long i = 0; i < 60; i++) {
    for (int j = 0; j < N; j++) {
      dp[0][j] = 0;
      dp[1][j] = 0;
    }

    DFS(G, 0, dp, i, ans);
  }

  cout << ans.val() << endl;
}