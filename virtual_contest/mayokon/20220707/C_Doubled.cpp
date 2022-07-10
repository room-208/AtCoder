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

constexpr int INF_int = 1e9;
constexpr ll INF_ll = 1e18;
const double EPS = 1e-10;

constexpr int COM_MAX = 5000000;
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

// 二項係数計算 (long long)
ll COMLL(ll n, ll r) {
  ll res = 1;
  for (ll i = 0; i < r; i++) {
    res *= (n - i);
    res /= (i + 1);
  }
  return res;
}

// 順列組合せ
mint PER(int n, int k) {
  if (n < k) return 0;
  if (n < 0 || k < 0) return 0;
  return fac[n] * finv[n - k];
}

//等差数列の和
// a：初項 d：等差 n：数列の数
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
// y*y <= x を満たす最大の y を返します。
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

// a^k <= n < a^(k+1) を満たす k を返します。
ll my_log(ll a, ll n) {
  assert(n > 0);
  assert(a > 1);
  ull pow = 1;
  for (int k = 0; k <= 100; k++) {
    pow *= a;
    if (n < pow) {
      return k;
    }
  }
  assert(false);
  return -1;
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

class RollingHash {
 private:
  vector<ull> base_cands;
  ull base1, base2;

 private:
  // 基数をランダムに取得します
  ull GetRandBase(mt19937 &mt) {
    int index = uniform_int_distribution<int>(0, base_cands.size() - 1)(mt);
    ull res = base_cands[index];
    base_cands.erase(base_cands.begin() + index);
    return res;
  }
  // Sのハッシュ値を取得します
  vector<ull> GetHashValue(const string &S, int len, ull base) const {
    if (len > S.size()) {
      return {};
    }
    ull base_pow_len = 1;
    for (int i = 0; i < len; i++) {
      base_pow_len *= base;
    }
    vector<ull> hashs;
    hashs.reserve(S.size() - len + 1);
    ull hash_val = 0;
    for (int i = 0; i < len; i++) {
      hash_val = hash_val * base + S[i];
    }
    hashs.emplace_back(hash_val);
    for (int i = 1; i + len - 1 < S.size(); i++) {
      hash_val = hash_val * base + S[i + len - 1] - base_pow_len * S[i - 1];
      hashs.emplace_back(hash_val);
    }
    return hashs;
  }

 public:
  RollingHash() {
    base_cands = {100000007ULL, 1000000007ULL, 37ULL, 2ULL};
    random_device seed_gen;
    mt19937 mt(seed_gen());
    base1 = GetRandBase(mt);
    base2 = GetRandBase(mt);
  }
  // Sの[start,end]のlenの長さの部分列のハッシュ値を取得します
  vector<pair<ull, ull>> GetHashPairValues(const string &S, int len, int start,
                                           int end) const {
    auto S_sub = S.substr(start, end - start + 1);
    vector<ull> hash1 = GetHashValue(S_sub, len, base1);
    vector<ull> hash2 = GetHashValue(S_sub, len, base2);
    vector<pair<ull, ull>> hash_pair;
    hash_pair.reserve(hash1.size());
    for (size_t i = 0; i < hash1.size(); i++) {
      hash_pair.emplace_back(hash1[i], hash2[i]);
    }
    return hash_pair;
  }
  // Tのハッシュ値を取得します
  pair<ull, ull> GetHashPairValue(const string &T) const {
    ull hash1 = GetHashValue(T, T.size(), base1).front();
    ull hash2 = GetHashValue(T, T.size(), base2).front();
    return {hash1, hash2};
  }
};

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
vector<ll> CompressCoordinate(vector<ll> &x) {
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

// Range Mindex Query (最小値とindexのペアを返すセグメント木)
namespace rmq {
struct Pair {
  ll val;
  int index;
};
// マージ演算
Pair op(Pair a, Pair b) {
  if (a.val >= b.val) {
    return a;
  }
  return b;
}
Pair e() { return {-INF_ll, -1}; }
// 区間更新
Pair id() { return {-1, -1}; }
Pair mapping(Pair f, Pair x) {
  if (f.val == id().val) {
    return x;
  } else {
    return f;
  }
}
Pair composition(Pair f, Pair g) {
  if (f.val == id().val) {
    return g;
  } else {
    return f;
  }
}
// 二分探索
ll target;
bool f(Pair x) { return x.val < target; };
// 初期化
void Init(vector<ll> A, segtree<rmq::Pair, rmq::op, rmq::e> &sgt) {
  vector<Pair> init(A.size());
  for (int i = 0; i < A.size(); i++) {
    init[i] = {A[i], i};
  }
  sgt = segtree<rmq::Pair, rmq::op, rmq::e>(init);
}
}  // namespace rmq

// RMQのエイリアス
using RMQ = segtree<rmq::Pair, rmq::op, rmq::e>;
using Lazy_RMQ = lazy_segtree<rmq::Pair, rmq::op, rmq::e, rmq::Pair,
                              rmq::mapping, rmq::composition, rmq::id>;

// セグメント木・遅延セグメント木
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

// セグメント木のエイリアス
using Segtree = segtree<ll, seg::op, seg::e>;
using LazySegtree = lazy_segtree<ll, seg::op, seg::e, ll, seg::mapping,
                                 seg::composition, seg::id>;

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
    DP() {}
    DP(ll dp) : dp(dp) {}
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
  DP e() { return DP(0); }
  // マージ
  DP merge(DP dp_cum, DP dp) { return DP(max(dp_cum.dp, dp.dp)); }
  // 頂点に関する計算
  DP add_root(int v, ll w, DP dp) { return DP(dp.dp + w); }
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

// 深さ優先探索
void DFS(const Graph_int &G, int v, vector<bool> &seen) {
  seen[v] = true;

  for (auto next_v : G[v]) {
    if (seen[next_v]) {
      continue;
    }

    DFS(G, next_v, seen);
  }
}

//根付き木
void cal_par(const Graph_int &G, int v, vector<int> &par, int p = -1) {
  for (auto next_v : G[v]) {
    if (next_v == p) {
      continue;
    }

    cal_par(G, next_v, par, v);
  }

  par[v] = p;
}

//部分木サイズ
void cal_subtree_size(const Graph_int &G, int v, vector<int> &subtree_size,
                      int p = -1) {
  for (auto c : G[v]) {
    if (c == p) {
      continue;
    }

    cal_subtree_size(G, c, subtree_size, v);
  }

  // 帰りがけ時に、部分木サイズを求める
  subtree_size[v] = 1;  // 自分自身
  for (auto c : G[v]) {
    if (c == p) {
      continue;
    }

    // 子頂点を根とする部分きのサイズを加算する
    subtree_size[v] += subtree_size[c];
  }
}

//トポロジカルソート
class TopologicalSort {
 private:
  void dfs(const Graph_int &G, int v, vector<bool> &seen, vector<int> &order) {
    seen[v] = true;
    for (auto next_v : G[v]) {
      if (seen[next_v]) {
        continue;
      }

      dfs(G, next_v, seen, order);
    }

    order.push_back(v);
  }

 public:
  vector<int> sort(const Graph_int &G) {
    int N = (int)G.size();
    vector<int> order;
    vector<bool> seen(N, false);
    for (int v = 0; v < N; v++) {
      if (seen[v]) {
        continue;
      }

      dfs(G, v, seen, order);
    }

    reverse(order.begin(), order.end());
    return order;
  }
};

//幅優先探索
vector<int> BFS(const Graph_int &G, int s) {
  int N = (int)G.size();    // 頂点数
  vector<int> dist(N, -1);  // 全頂点を「未訪問」に初期化
  queue<int> que;

  // 初期条件 (頂点 s を初期頂点とする)
  dist[s] = 0;
  que.push(s);  // s を橙色頂点にする

  // BFS 開始 (キューが空になるまで探索を行う)
  while (!que.empty()) {
    int v = que.front();  // キューから先頭頂点を取り出す
    que.pop();

    // v からたどれる頂点をすべて調べる
    for (int x : G[v]) {
      // すでに発見済みの頂点は探索しない
      if (dist[x] != -1) continue;

      // 新たな白色頂点 x について距離情報を更新してキューに挿入
      dist[x] = dist[v] + 1;
      que.push(x);
    }
  }
  return dist;
}

// 01BFS
vector<ll> BFS_01(const Graph_Edge &G, int s) {
  int N = (int)G.size();       // 頂点数
  vector<ll> dist(N, INF_ll);  // 全頂点を「未訪問」に初期化
  deque<int> que;

  // 初期条件 (頂点 s を初期頂点とする)
  dist[s] = 0;
  que.push_front(s);

  // BFS 開始 (キューが空になるまで探索を行う)
  while (!que.empty()) {
    int v = que.front();  // キューから先頭頂点を取り出す
    que.pop_front();

    // v からたどれる頂点をすべて調べる
    for (auto x : G[v]) {
      if (chmin(dist[x.to], dist[v] + x.w)) {
        if (x.w == 0) {
          que.push_front(x.to);
        }
        if (x.w == 1) {
          que.push_back(x.to);
        }
      }
    }
  }
  return dist;
}

//ベルマン・フォード法
vector<ll> Bellman_Ford(const Graph_Edge &G, int s) {
  int N = (int)G.size();
  bool exist_negative_cycle = false;  // 負閉路をもつかどうか
  vector<ll> dist(N, INF_ll);
  dist[s] = 0;

  for (int iter = 0; iter < N; ++iter) {
    bool update = false;  // 更新が発生したかどうかを表すフラグ
    for (int v = 0; v < N; ++v) {
      // dist[v] = INF のときは頂点 v からの緩和を行わない
      if (dist[v] == INF_ll) continue;

      for (auto e : G[v]) {
        // 緩和処理を行い，更新されたら update を true にする
        if (chmin(dist[e.to], dist[v] + e.w)) {
          update = true;
        }
      }
    }

    // 更新が行われなかったら，すでに最短路が求められている
    if (!update) break;

    // N 回目の反復で更新が行われたならば，負閉路をもつ
    if (iter == N - 1 && update) exist_negative_cycle = true;
  }
  return dist;
}

//ダイクストラ法
vector<ll> Dijkstra(const Graph_Edge &G, int s) {
  int N = (int)G.size();
  vector<ll> dist(N, INF_ll);
  dist[s] = 0;

  // (d[v], v) のペアを要素としたヒープを作る
  priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>>
      que;
  que.push(make_pair(dist[s], s));

  // ダイクストラ法の反復を開始
  while (!que.empty()) {
    // v: 使用済みでない頂点のうち d[v] が最小の頂点
    // d: v に対するキー値
    int v = que.top().second;
    ll d = que.top().first;
    que.pop();

    // d > dist[v] は，(d, v) がゴミであることを意味する
    if (d > dist[v]) continue;

    // 頂点 v を始点とした各辺を緩和
    for (auto e : G[v]) {
      if (chmin(dist[e.to], dist[v] + e.w)) {
        // 更新があるならヒープに新たに挿入
        que.push(make_pair(dist[e.to], e.to));
      }
    }
  }
  return dist;
}

// ワーシャル・フロイド法
vector<vector<ll>> WarshallFloyd(vector<vector<ll>> &w) {
  vector<vector<ll>> dist = w;
  int N = dist.size();
  for (int k = 0; k < N; k++) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }
  return dist;
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

// ソート済タプル
template <class Ta, class Tb, class Tc>
tuple<vector<Ta>, vector<Tb>, vector<Tc>> GetSortedTuple(
    vector<Ta> a, vector<Tb> b, vector<Tc> c, bool reverse_flag = false) {
  assert(a.size() == b.size());
  assert(b.size() == c.size());
  int N = a.size();
  vector<tuple<Ta, Tb, Tc>> t(N);
  for (int i = 0; i < N; i++) {
    t[i] = {a[i], b[i], c[i]};
  }
  sort(t.begin(), t.end());
  if (reverse_flag) {
    reverse(t.begin(), t.end());
  }
  for (int i = 0; i < N; i++) {
    tie(a[i], b[i], c[i]) = t[i];
  }
  return {a, b, c};
}

//組み込み関数（GCC）
//__builtin_add_overflow
//__builtin_mul_overflow
//__builtin_popcount()
//__builtin_popcountll()

//ノード変換
int to_node(int i, int j, int W) { return W * i + j; }

// ij変換
pair<int, int> to_ij(int v, int W) {
  int i = v / W;
  int j = v - W * i;

  return make_pair(i, j);
}

// in_out判定
bool Is_in(int i, int j, int H, int W) {
  if (0 <= i && i < H && 0 <= j && j < W) {
    return true;
  }

  return false;
}

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

struct my_struct {
  int a, b;
};

bool operator<(const my_struct &s_1, const my_struct &s_2) {
  return s_1.b > s_2.b;
}

int main() {
  ll N;
  cin >> N;

  int cnt = 0;
  for (int i = 1; i <= 10000000; i++) {
    string a = to_string(i);
    string b = a;
    b += a;
    ll K = stol(b);
    if (K <= N) {
      cnt++;
    }
  }

  cout << cnt << endl;
}