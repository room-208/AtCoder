#define _USE_MATH_DEFINES

#include <algorithm>
#include <atcoder/fenwicktree>
#include <atcoder/lazysegtree>
#include <atcoder/maxflow>
#include <atcoder/mincostflow>
#include <atcoder/modint>
#include <atcoder/scc>
#include <atcoder/segtree>
#include <bitset>
#include <cmath>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
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
using ll = long long;
using ull = unsigned long long;

namespace seg2 {
bool op(bool a, bool b) { return a & b; }
bool e() { return true; }
}  // namespace seg2
using Segtree2 = segtree<bool, seg2::op, seg2::e>;

int main() {
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int N, M;
  cin >> N >> M;
  vector<int> A(N), B(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i] >> B[i];
    A[i]--;
    B[i]--;
  }

  vector<vector<int>> mp(M);
  for (int i = 0; i < N; i++) {
    mp[A[i]].push_back(i);
    mp[B[i]].push_back(i);
  }

  vector<int> cnt(N, 0);
  unordered_set<int> st;
  for (int i = 0; i < N; i++) {
    st.insert(i);
  }

  vector<int> ans(M + 10, 0);

  int right = 0;
  for (int left = 0; left < M; ++left) {
    while (right < M && !st.empty()) {
      /* 実際に right を 1 進める */
      for (auto &&v : mp[right]) {
        cnt[v]++;
        st.erase(v);
      }
      ++right;
    }

    if (!st.empty()) break;

    /* break した状態で right は条件を満たす最大なので、何かする */
    int min_kukan = right - left;
    int max_kukan = M - left;
    ans[min_kukan]++;
    ans[max_kukan + 1]--;

    /* left をインクリメントする準備 */
    if (right == left) {
      ++right;
    } else {
      for (auto &&v : mp[left]) {
        cnt[v]--;
        if (cnt[v] == 0) {
          st.insert(v);
        }
      }
    }
  }

  for (int i = 1; i <= M; i++) {
    ans[i] += ans[i - 1];
  }

  for (int i = 1; i <= M; i++) {
    cout << ans[i] << " ";
  }
  cout << endl;
}