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

const int INF_int = 1000000000;

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

using Graph_int = vector<vector<int>>;

// 深さ優先探索
int id = 1;
void DFS0(const Graph_int &G, int v, vector<int> &L, vector<int> &R,
          int p = -1) {
  if (v != 0 && G[v].size() == 1) {
    L[v] = id;
    R[v] = id;
    id++;
  }
  for (auto next_v : G[v]) {
    if (next_v == p) {
      continue;
    }

    DFS0(G, next_v, L, R, v);
  }
}

// 深さ優先探索
void DFS(const Graph_int &G, int v, vector<int> &L, vector<int> &R,
         int p = -1) {
  for (auto next_v : G[v]) {
    if (next_v == p) {
      continue;
    }

    DFS(G, next_v, L, R, v);
  }

  // 帰りがけ時に、部分木サイズを求める
  for (auto c : G[v]) {
    if (c == p) {
      continue;
    }

    // 子頂点を根とする部分きのサイズを加算する
    chmin(L[v], L[c]);
    chmax(R[v], R[c]);
  }
}

int main() {
  int N;
  cin >> N;
  Graph_int G(N);
  for (int i = 0; i < N - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    G[u].push_back(v);
    G[v].push_back(u);
  }

  vector<int> L(N, INF_int), R(N, -INF_int);

  DFS0(G, 0, L, R);
  DFS(G, 0, L, R);
  for (int i = 0; i < N; i++) {
    cout << L[i] << " " << R[i] << endl;
  }
}