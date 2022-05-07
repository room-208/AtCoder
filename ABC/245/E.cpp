#define _USE_MATH_DEFINES

#include <algorithm>
#include <atcoder/fenwicktree>
#include <atcoder/lazysegtree>
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

constexpr int INF_int = 1e9;
constexpr ll INF_ll = 1e18;

constexpr int COM_MAX = 1000000;
mint fac[COM_MAX], finv[COM_MAX], inv[COM_MAX];

// テーブルを作る前処理
void COMinit() {
  fac[0] = fac[1] = 1;
  finv[0] = finv[1] = 1;
  inv[1] = 1;
  for (int i = 2; i < COM_MAX; i++) {
    fac[i] = fac[i - 1] * i;
    inv[i] = -inv[mint::mod() % i] * (mint::mod() / i);
    finv[i] = finv[i - 1] * inv[i];
  }
}

// 二項係数計算
mint COM(int n, int k) {
  if (n < k) return 0;
  if (n < 0 || k < 0) return 0;
  return fac[n] * (finv[k] * finv[n - k]);
}

// 順列組合せ
mint PER(int n, int k) {
  if (n < k) return 0;
  if (n < 0 || k < 0) return 0;
  return fac[n] * finv[n - k];
}

//等差数列の和
ll tousa_sum(ll a, ll d, ll n) { return (a * 2 + d * (n - 1)) * n / 2LL; }

// 床関数
ll my_floor(ll a, ll b) {
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
ll my_ceil(ll a, ll b) {
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

// 平方関数
ll my_sqrt(ll x) {
  ll left = 0;
  ll right = numeric_limits<int>::max();
  while (right - left > 1) {
    ll mid = (right + left) / 2;
    if (mid * mid <= x) {
      left = mid;
    } else {
      right = mid;
    }
  }
  return left;
}

//転倒数
ll inv_count(const vector<int> &a) {
  int n = (int)a.size();
  fenwick_tree<int> fw(n);
  ll ans = 0;
  for (int i = 0; i < n; i++) {
    ans += fw.sum(a[i] + 1, n);
    fw.add(a[i], 1);
  }
  return ans;
}

//最大公約数
ll GCD(ll a, ll b) {
  if (b == 0) {
    return a;
  }
  return GCD(b, a % b);
}

//拡張GCD
ll EXTGCD(ll a, ll b, ll &x, ll &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  ll gcd = EXTGCD(b, a % b, y, x);
  y -= (a / b) * x;
  // gcd>0を保証
  if (gcd < 0) {
    gcd *= -1;
    x *= -1;
    y *= -1;
  }
  return gcd;
}

// osa_k法
vector<int> osa_k(int n) {
  vector<int> res(n + 1);
  iota(res.begin(), res.end(), 0);
  for (int i = 2; i * i <= n; ++i) {
    //合成数の判定
    if (res[i] < i) {
      continue;
    }

    //最小の素因数の代入
    for (int j = i * i; j <= n; j += i) {
      if (res[j] == j) {
        res[j] = i;
      }
    }
  }
  return res;
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

// ソート済ペア
template <class Ta, class Tb>
pair<vector<Ta>, vector<Tb>> GetSortedPair(vector<Ta> a, vector<Tb> b,
                                           bool reverse_flag = false) {
  assert(a.size() == b.size());
  int N = a.size();
  vector<pair<Ta, Tb>> p(N);
  for (int i = 0; i < N; i++) {
    p[i] = {a[i], b[i]};
  }
  sort(p.begin(), p.end());
  if (reverse_flag) {
    reverse(p.begin(), p.end());
  }
  for (int i = 0; i < N; i++) {
    a[i] = p[i].first;
    b[i] = p[i].second;
  }
  return {a, b};
}

int main() {
  int N, M;
  cin >> N >> M;
  vector<ll> A(N), B(N), C(M), D(M);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }
  for (int i = 0; i < N; i++) {
    cin >> B[i];
  }
  for (int i = 0; i < M; i++) {
    cin >> C[i];
  }
  for (int i = 0; i < M; i++) {
    cin >> D[i];
  }

  tie(A, B) = GetSortedPair(A, B, true);
  tie(C, D) = GetSortedPair(C, D);

  multiset<ll> st;
  ll last_m = M;
  bool flag = true;
  for (int i = 0; i < N; i++) {
    int m = lower_bound(C.begin(), C.end(), A[i]) - C.begin();

    if (m == M) {
      flag = false;
      break;
    } else {
      for (int k = m; k < last_m; k++) {
        st.insert(D[k]);
      }
      last_m = m;
      auto itr = st.lower_bound(B[i]);
      if (itr == st.end()) {
        flag = false;
        break;
      } else {
        st.erase(itr);
      }
    }
  }

  if (flag) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }
}