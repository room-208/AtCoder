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

int main() {
  int N;
  cin >> N;
  vector<long long> A(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }

  mint ans = 0;
  for (long long i = 0; i <= 60; i++) {
    long long one = 0;
    long long zero = 0;

    for (int j = 0; j < N; j++) {
      if (A[j] & (1LL << i)) {
        one++;
      } else {
        zero++;
      }
    }

    ans += mint(2).pow(i) * one * zero;
  }

  cout << ans.val() << endl;
}