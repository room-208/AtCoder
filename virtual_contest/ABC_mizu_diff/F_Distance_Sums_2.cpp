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
vector<int> OsaK(int n) {
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

// 素数を取得する
vector<int> GetPrime(int n) {
  vector<int> osak = OsaK(n);
  vector<int> prime;
  for (int k = 2; k <= n; k++) {
    if (k == osak[k]) {
      prime.push_back(k);
    }
  }
  return prime;
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

//連長圧縮
vector<pair<char, int>> runLengthEncoding(string s) {
  int n = s.length();

  vector<pair<char, int>> res;
  char pre = s[0];
  int cnt = 1;
  for (int i = 1; i < n; i++) {
    if (pre != s[i]) {
      res.push_back({pre, cnt});
      pre = s[i];
      cnt = 1;
    } else {
      cnt++;
    }
  }

  res.push_back({pre, cnt});
  return res;
}

//アルファベット表
vector<vector<int>> alphabet_table(string S) {
  int N = (int)S.size();
  vector<vector<int>> table(26, vector<int>(N + 1, INF_int));
  for (int j = N - 1; j >= 0; j--) {
    int m = S[j] - 'a';
    for (int i = 0; i < 26; i++) {
      if (i == m) {
        table[i][j] = j;
      } else {
        table[i][j] = table[i][j + 1];
      }
    }
  }
  return table;
}

// unoderedのハッシュ
struct HashPair {
  //注意 constがいる
  template <class T1, class T2>
  size_t operator()(const pair<T1, T2> &p) const {
    // first分をハッシュ化する
    auto hash1 = hash<T1>{}(p.first);

    // second分をハッシュ化する
    auto hash2 = hash<T2>{}(p.second);

    //重複しないようにハッシュ処理
    size_t seed = 0;
    seed ^= hash1 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    seed ^= hash2 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    return seed;
  }
};

//座標圧縮
vector<ll> compress(vector<ll> &x) {
  map<ll, ll> mp;

  for (int i = 0; i < (int)x.size(); i++) {
    mp[x[i]] = 0;
  }

  ll compress = 1;
  for (auto itr = mp.begin(); itr != mp.end(); itr++) {
    itr->second = compress;
    compress++;
  }

  vector<ll> y(x.size());
  for (int i = 0; i < (int)x.size(); i++) {
    y[i] = mp[x[i]];
  }
  return y;
}

// 最長増加部分列
vector<int> LIS(const vector<int> &A) {
  int N = A.size();
  vector<int> x;
  vector<int> P(N);
  for (int i = 0; i < N; i++) {
    int key = A[i];
    auto itr = lower_bound(x.begin(), x.end(), key);
    if (itr == x.end()) {
      x.push_back(key);
    } else {
      *itr = key;
    }
    P[i] = x.size();
  }
  return P;
}

//セグ木・遅延セグ木
// segtree<ll, seg::op, seg::e> sgt;
// lazy_segtree<ll, seg::op, seg::e, ll, seg::mapping,
// seg::composition, seg::id> sgt;
namespace seg {
const ll ID = -1;
ll op(ll a, ll b) { return max(a, b); }
ll e() { return -INF_ll; }
ll mapping(ll f, ll x) {
  if (f == ID) {
    return x;
  } else {
    return f;
  }
  // return f + x;
}
ll composition(ll f, ll g) {
  if (f == ID) {
    return g;
  } else {
    return f;
  }
  // return f + g;
}
ll id() { return ID; }
ll target;
bool f(ll v) { return v < target; }
}  // namespace seg

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

//エッジ集合
struct Edge {
  int to;
  ll w;
  Edge(int to, ll w) : to(to), w(w) {}
};

using Graph_int = vector<vector<int>>;
using Graph_Edge = vector<vector<Edge>>;

class Rerooting {
 private:
  struct DP {
    ll dp;
    ll subtree_size;
    DP() {}
    DP(ll dp, ll subtree_size) : dp(dp), subtree_size(subtree_size) {}
  };

 public:
  vector<DP> res;

 private:
  vector<vector<DP>> dp;
  Graph_Edge G;

 public:
  Rerooting(int N) {
    dp.resize(N);
    res.resize(N, e());
    G.resize(N);
  }
  void build() {
    int root = 0;
    dfs_init(root);
    dfs_reroot(root, e());
  }
  void add_edge(int a, int b, ll c) { G[a].push_back(Edge(b, c)); }

 private:
  // mergeの単位元
  DP e() { return DP(0, 0); }
  // マージ
  DP merge(DP dp_cum, DP dp) {
    return DP(dp_cum.dp + dp.dp, dp_cum.subtree_size + dp.subtree_size);
  }
  // 頂点に関する計算
  DP add_root(int v, ll w, DP dp) {
    return DP(dp.dp + dp.subtree_size + 1, dp.subtree_size + 1);
  }
  // 初期解
  DP dfs_init(int v, ll w = 0, int p = -1) {
    DP dp_cum = e();
    int degree = G[v].size();
    dp[v].resize(degree);
    for (int i = 0; i < degree; i++) {
      auto next_v = G[v][i];
      if (next_v.to == p) {
        continue;
      }
      dp[v][i] = dfs_init(next_v.to, next_v.w, v);
      dp_cum = merge(dp_cum, dp[v][i]);
    }
    return add_root(v, w, dp_cum);
  }
  // 全方位
  void dfs_reroot(int v, DP dp_p, int p = -1) {
    int degree = G[v].size();
    // 親方向を計算
    for (int i = 0; i < degree; i++) {
      auto next_v = G[v][i];
      if (next_v.to == p) {
        dp[v][i] = dp_p;
      }
    }
    // 累積マージ
    vector<DP> S_l(degree + 1, e()), S_r(degree + 1, e());
    for (int i = 0; i < degree; i++) {
      S_l[i + 1] = merge(S_l[i], dp[v][i]);
    }
    for (int i = degree - 1; i >= 0; i--) {
      S_r[i] = merge(S_r[i + 1], dp[v][i]);
    }
    // resを計算
    res[v] = S_l[degree];
    // 下の階層に潜る
    for (int i = 0; i < degree; i++) {
      auto next_v = G[v][i];
      if (next_v.to == p) {
        continue;
      }
      DP dp_v = add_root(v, next_v.w, merge(S_l[i], S_r[i + 1]));
      dfs_reroot(next_v.to, dp_v, v);
    }
  }
};

int main() {
  int N;
  cin >> N;
  Rerooting reroot(N);
  for (int i = 0; i < N - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    reroot.add_edge(u, v, 1);
    reroot.add_edge(v, u, 1);
  }

  reroot.build();
  for (int i = 0; i < N; i++) {
    cout << reroot.res[i].dp << endl;
  }
}