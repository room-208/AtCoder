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
  int index;
  Edge(int to, ll w, int index) : to(to), w(w), index(index) {}
};

using Graph_int = vector<vector<int>>;
using Graph_Edge = vector<vector<Edge>>;

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
vector<int> Dijkstra(const Graph_Edge &G, int s) {
  int N = (int)G.size();
  vector<ll> dist(N, INF_ll);
  vector<int> index;
  dist[s] = 0;

  // (d[v], v) のペアを要素としたヒープを作る
  priority_queue<tuple<ll, int, int>, vector<tuple<ll, int, int>>,
                 greater<tuple<ll, int, int>>>
      que;
  que.push({dist[s], s, -1});

  // ダイクストラ法の反復を開始
  while (!que.empty()) {
    // v: 使用済みでない頂点のうち d[v] が最小の頂点
    // d: v に対するキー値
    int v;
    ll d;
    int i;
    tie(d, v, i) = que.top();
    que.pop();

    // d > dist[v] は，(d, v) がゴミであることを意味する
    if (d > dist[v]) continue;

    index.push_back(i);

    // 頂点 v を始点とした各辺を緩和
    for (auto e : G[v]) {
      if (chmin(dist[e.to], dist[v] + e.w)) {
        // 更新があるならヒープに新たに挿入
        que.push({dist[e.to], e.to, e.index});
      }
    }
  }
  return index;
}

int main() {
  int N, M;
  cin >> N >> M;
  vector<int> A(M), B(M);
  vector<ll> C(M);
  for (int i = 0; i < M; i++) {
    cin >> A[i] >> B[i] >> C[i];
    A[i]--;
    B[i]--;
  }

  Graph_Edge G(N);
  for (int i = 0; i < M; i++) {
    G[A[i]].push_back(Edge(B[i], C[i], i));
    G[B[i]].push_back(Edge(A[i], C[i], i));
  }

  auto index = Dijkstra(G, 0);

  for (int i = 1; i < N; i++) {
    cout << index[i] + 1 << " ";
  }
  cout << endl;
}