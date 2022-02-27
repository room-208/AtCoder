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

//等差数列の和
long long tousa_sum(long long a, long long d, long long n) {
  return (a * 2LL + d * (n - 1)) * n / 2LL;
}

// 床関数
long long my_floor(long long a, long long b) {
  assert(b != 0);
  if (b < 0) {
    a *= -1;
    b *= -1;
  }
  if (a > 0) {
    return (a / b);
  } else if (a < 0) {
    if (a % b == 0) {
      return (a / b);
    } else {
      return (a / b) - 1;
    }
  }
  return 0;
}

// 天井関数
long long my_ceil(long long a, long long b) {
  assert(b != 0);
  if (b < 0) {
    a *= -1;
    b *= -1;
  }
  if (a > 0) {
    if (a % b == 0) {
      return (a / b);
    } else {
      return (a / b) + 1;
    }
  } else if (a < 0) {
    return (a / b);
  }
  return 0;
}

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
  int T;
  cin >> T;
  vector<int> N(T), M(T);
  vector<vector<long long>> X(T), Y(T);
  for (int t = 0; t < T; t++) {
    cin >> N[t] >> M[t];
    X[t].resize(N[t]);
    Y[t].resize(N[t]);
    for (int i = 0; i < N[t]; i++) {
      cin >> X[t][i] >> Y[t][i];
    }
  }

  for (int t = 0; t < T; t++) {
    const long long n = N[t];
    const long long m = M[t];
    const vector<long long> x = X[t];
    const vector<long long> y = Y[t];

    vector<long long> D;
    long long B = 0;
    for (int i = 0; i < n; i++) {
      if (B < 0 && B + x[i] * y[i] >= 0) {
        long long z = my_ceil(B, -x[i]) - 1;
        if (z == 0) {
          D.push_back(tousa_sum(B + x[i], x[i], y[i]));
        } else {
          D.push_back(tousa_sum(B + x[i], x[i], z));
          D.push_back(tousa_sum(B + (z + 1LL) * x[i], x[i], y[i] - z));
        }
      } else if (B >= 0 && B + x[i] * y[i] < 0) {
        long long z = my_floor(B, -x[i]);
        if (z == 0) {
          D.push_back(tousa_sum(B + x[i], x[i], y[i]));
        } else {
          D.push_back(tousa_sum(B + x[i], x[i], z));
          D.push_back(tousa_sum(B + (z + 1LL) * x[i], x[i], y[i] - z));
        }
      } else {
        D.push_back(tousa_sum(B + x[i], x[i], y[i]));
      }
      B += x[i] * y[i];
    }

    long long ans = x[0];
    long long tmp = 0;
    for (int i = 0; i < (int)D.size(); i++) {
      tmp += D[i];
      chmax(ans, tmp);
    }
    cout << ans << endl;
  }
}