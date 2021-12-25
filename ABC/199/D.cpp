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

// Union-Find
struct UnionFind {
  vector<int> par, siz;

  // 初期化
  UnionFind(int n) : par(n, -1), siz(n, 1) {}

  // 根を求める
  int root(int x) {
    if (par[x] == -1)
      return x;  // x が根の場合は x を返す
    else
      return par[x] = root(par[x]);
  }

  // x と y が同じグループに属するかどうか (根が一致するかどうか)
  bool issame(int x, int y) { return root(x) == root(y); }

  // x を含むグループと y を含むグループとを併合する
  bool unite(int x, int y) {
    // x, y をそれぞれ根まで移動する
    x = root(x);
    y = root(y);

    // すでに同じグループのときは何もしない
    if (x == y) return false;

    // union by size (y 側のサイズが小さくなるようにする)
    if (siz[x] < siz[y]) swap(x, y);

    // y を x の子とする
    par[y] = x;
    siz[x] += siz[y];
    return true;
  }

  // x を含むグループのサイズ
  int size(int x) { return siz[root(x)]; }
};

int main() {
  int N, M;
  cin >> N >> M;
  vector<pair<int, int>> edges;
  for (int i = 0; i < M; i++) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    edges.push_back(make_pair(a, b));
  }

  long long ans = 0;
  for (int S = 0; S < (1 << N); S++) {
    vector<int> color(N, -1);
    for (int i = 0; i < N; i++) {
      if (S & (1 << i)) {
        color[i] = 0;
      } else {
        color[i] = 1;
      }
    }

    UnionFind uf(2 * N);
    bool flag = true;
    for (auto &&e : edges) {
      int a = e.first;
      int b = e.second;
      if (color[a] == 0 && color[b] == 0) {
        flag = false;
        break;
      } else if (color[a] == 1 && color[b] == 1) {
        uf.unite(a, b + N);
        uf.unite(a + N, b);
      }
    }

    if (!flag) {
      continue;
    }

    long long cnt = 0;
    for (int i = 0; i < N; i++) {
      if (color[i] == 1) {
        if (uf.issame(i, i + N)) {
          flag = false;
          break;
        } else if (i == uf.root(i)) {
          cnt++;
        }
      }
    }

    if (flag) {
      ans += (1LL << cnt);
    }
  }

  cout << ans << endl;
}