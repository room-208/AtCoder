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

const int MOD = 1000000007;
const int INF_int = 1000000000;
const long long INF_ll = 1000000000000000000LL;
const int COM_MAX = 510000;

int main() {
  long long H, W;
  int N;
  cin >> H >> W >> N;
  long long sx, sy;
  cin >> sx >> sy;
  sx--;
  sy--;
  long long gx, gy;
  cin >> gx >> gy;
  gx--;
  gy--;
  vector<long long> X(N), Y(N);
  for (int i = 0; i < N; i++) {
    cin >> X[i] >> Y[i];
    X[i]--;
    Y[i]--;
  }

  map<int, vector<long long>> tate, yoko;
  for (int i = 0; i < N; i++) {
    tate[Y[i]].push_back(INF_ll);
    tate[Y[i]].push_back(-INF_ll);
    yoko[X[i]].push_back(INF_ll);
    yoko[X[i]].push_back(-INF_ll);
  }
  for (int i = 0; i < N; i++) {
    tate[Y[i]].push_back(X[i]);
    yoko[X[i]].push_back(Y[i]);
  }
  for (int i = 0; i < N; i++) {
    sort(tate[Y[i]].begin(), tate[Y[i]].end());
    sort(yoko[X[i]].begin(), yoko[X[i]].end());
  }

  queue<pair<long long, long long>> que;
  map<pair<long long, long long>, int> dist;
  dist[make_pair(sx, sy)] = 0;
  que.push(make_pair(sx, sy));  // s を橙色頂点にする

  while (!que.empty()) {
    auto v = que.front();
    que.pop();

    long long x = v.first;
    long long y = v.second;

    if (tate.count(y)) {
      long long key = x;
      auto itr = upper_bound(tate[y].begin(), tate[y].end(), key);
      long long tate1 = *itr;
      itr--;
      long long tate0 = *itr;

      if (tate1 != INF_ll) {
        auto next = make_pair(tate1 - 1, y);
        if (!dist.count(next)) {
          dist[next] = dist[v] + 1;
          que.push(next);
        }
      }
      if (tate0 != -INF_ll) {
        auto next = make_pair(tate0 + 1, y);
        if (!dist.count(next)) {
          dist[next] = dist[v] + 1;
          que.push(next);
        }
      }
    }

    if (yoko.count(x)) {
      long long key = y;
      auto itr = upper_bound(yoko[x].begin(), yoko[x].end(), key);
      long long yoko1 = *itr;
      itr--;
      long long yoko0 = *itr;

      if (yoko1 != INF_ll) {
        auto next = make_pair(x, yoko1 - 1);
        if (!dist.count(next)) {
          dist[next] = dist[v] + 1;
          que.push(next);
        }
      }
      if (yoko0 != -INF_ll) {
        auto next = make_pair(x, yoko0 + 1);
        if (!dist.count(next)) {
          dist[next] = dist[v] + 1;
          que.push(next);
        }
      }
    }
  }

  if (dist.count(make_pair(gx, gy))) {
    cout << dist[make_pair(gx, gy)] << endl;
  } else {
    cout << -1 << endl;
  }
}