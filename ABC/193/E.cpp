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

const long long INF_ll = 5LL * 1000000000000000000LL;

//最大公約数
template <class T>
T GCD(T m, T n) {
  // ベースケース
  if (n == 0) {
    return m;
  }

  // 再帰呼び出し
  return GCD(n, m % n);
}

//拡張GCD
long long extgcd(long long a, long long b, long long &x, long long &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  long long gcd = extgcd(b, a % b, x, y);
  long long oldX = x;
  x = y;
  y = oldX - a / b * y;
  return gcd;
}

template <class T>
bool chmin(T &a, const T &b) {
  if (b < a) {
    a = b;
    return 1;
  }
  return 0;
}

long long waketostop(long long X, long long Y, long long P, long long Q) {
  long long Z = 2LL * X + 2LL * Y;
  long long R = P + Q;
  long long C = P - X;
  long long D = P + Q - X;

  long long n0, m0;
  long long g = GCD(Z, R);
  Z /= g;
  R /= g;
  extgcd(Z, -R, n0, m0);

  if (Z * n0 - R * m0 == -1) {
    n0 *= -1;
    m0 *= -1;
  }

  long long ans = INF_ll;
  bool flag = false;
  for (long long i = C; i < D; i++) {
    if (i % g == 0) {
      flag = true;
      long long h = i / g;
      long long e =
          max(ceil(-(((long double)n0 * (long double)h) / (long double)R)),
              ceil(-(((long double)m0 * (long double)h) / (long double)Z)));
      long long n = R * e + n0 * h;
      long long m = Z * e + m0 * h;
      chmin(ans, (2LL * X + 2LL * Y) * n + X);
    }
  }

  if (flag) {
    return ans;
  } else {
    return -1;
  }
}

long long stoptowake(long long X, long long Y, long long P, long long Q) {
  long long Z = 2LL * X + 2LL * Y;
  long long R = P + Q;
  long long C = X - P;
  long long D = X + Y - P;

  long long n0, m0;
  long long g = GCD(Z, R);
  Z /= g;
  R /= g;
  extgcd(-Z, R, n0, m0);

  if (-Z * n0 + R * m0 == -1) {
    n0 *= -1;
    m0 *= -1;
  }

  long long ans = INF_ll;
  bool flag = false;
  for (long long i = C; i < D; i++) {
    if (i % g == 0) {
      flag = true;
      long long h = i / g;
      long long e =
          max(ceil(-(((long double)n0 * (long double)h) / (long double)R)),
              ceil(-(((long double)m0 * (long double)h) / (long double)Z)));
      long long n = R * e + n0 * h;
      long long m = Z * e + m0 * h;
      chmin(ans, (P + Q) * m + P);
    }
  }

  if (flag) {
    return ans;
  } else {
    return -1;
  }
}

int main() {
  int T;
  cin >> T;
  vector<long long> X(T), Y(T), P(T), Q(T);
  for (int i = 0; i < T; i++) {
    cin >> X[i] >> Y[i] >> P[i] >> Q[i];
  }

  for (int i = 0; i < T; i++) {
    // 起きてる間に停車のとき
    long long ans0 = waketostop(X[i], Y[i], P[i], Q[i]);
    // 停車の間に起きるとき
    long long ans1 = stoptowake(X[i], Y[i], P[i], Q[i]);

    if (ans0 == -1 && ans1 == -1) {
      cout << "infinity" << endl;
    } else {
      if (ans0 == -1) {
        cout << ans1 << endl;
      } else if (ans1 == -1) {
        cout << ans0 << endl;
      } else {
        if (ans1 > ans0) {
          cout << ans0 << endl;
        } else {
          cout << ans1 << endl;
        }
      }
    }
  }
}