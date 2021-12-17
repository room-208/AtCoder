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

//エッジ集合
struct Edge {
  int to;
  long long c;
  long long d;
  Edge(int to, long long c, long long d) : to(to), c(c), d(d) {}
};

using Graph_Edge = vector<vector<Edge>>;

long long func(long long C, long long D, long long dist) {
  long long a = sqrt((long double)(D));

  long long res = C + (D / (dist + 1)) + dist;

  for (long long i = a - 100; i < a + 100; i++) {
    if (i >= dist) {
      chmin(res, C + (D / (i + 1)) + i);
    }
  }

  return res;
}

//ダイクストラ法
vector<long long> Dijkstra(const Graph_Edge &G, int s) {
  int N = (int)G.size();
  vector<long long> dist(N, INF_ll);
  dist[s] = 0;

  // (d[v], v) のペアを要素としたヒープを作る
  priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                 greater<pair<long long, int>>>
      que;
  que.push(make_pair(dist[s], s));

  // ダイクストラ法の反復を開始
  while (!que.empty()) {
    // v: 使用済みでない頂点のうち d[v] が最小の頂点
    // d: v に対するキー値
    int v = que.top().second;
    long long d = que.top().first;
    que.pop();

    // d > dist[v] は，(d, v) がゴミであることを意味する
    if (d > dist[v]) continue;

    // 頂点 v を始点とした各辺を緩和
    for (auto e : G[v]) {
      long long w = func(e.c, e.d, dist[v]);
      if (chmin(dist[e.to], w)) {
        // 更新があるならヒープに新たに挿入
        que.push(make_pair(dist[e.to], e.to));
      }
    }
  }

  return dist;
}

int main() {
  int N, M;
  cin >> N >> M;
  vector<int> A(M), B(M);
  vector<long long> C(M), D(M);
  for (int i = 0; i < M; i++) {
    cin >> A[i] >> B[i] >> C[i] >> D[i];
    A[i]--;
    B[i]--;
  }

  Graph_Edge G(N);
  for (int i = 0; i < M; i++) {
    G[A[i]].push_back(Edge(B[i], C[i], D[i]));
    G[B[i]].push_back(Edge(A[i], C[i], D[i]));
  }

  vector<long long> dist = Dijkstra(G, 0);

  if (dist[N - 1] == INF_ll) {
    cout << -1 << endl;
  } else {
    cout << dist[N - 1] << endl;
  }
}