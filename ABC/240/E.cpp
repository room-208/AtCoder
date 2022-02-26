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

long long fac[COM_MAX], finv[COM_MAX], inv[COM_MAX];

// テーブルを作る前処理
void COMinit() {
  fac[0] = fac[1] = 1;
  finv[0] = finv[1] = 1;
  inv[1] = 1;
  for (int i = 2; i < COM_MAX; i++) {
    fac[i] = fac[i - 1] * i % MOD;
    inv[i] = MOD - inv[MOD % i] * (MOD / i) % MOD;
    finv[i] = finv[i - 1] * inv[i] % MOD;
  }
}

// 二項係数計算
long long COM(int n, int k) {
  if (n < k) return 0;
  if (n < 0 || k < 0) return 0;
  return fac[n] * (finv[k] * finv[n - k] % MOD) % MOD;
}

//繰り返し二乗法
long long MOD_pow(long long a, long long n) {
  long long res = 1;
  while (n > 0) {
    if (n & 1) res = res * a % MOD;
    a = a * a % MOD;
    n >>= 1;
  }
  return res;
}

//等差数列の和
long long tousa_sum(long long a, long long d, long long n) {
  return (a * 2 + d * (n - 1)) * n / 2;
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

// 平方関数
long long my_sqrt(long long x) {
  long long left = 0;
  long long right = numeric_limits<int>::max();
  while (right - left > 1) {
    long long mid = (right + left) / 2;
    if (mid * mid <= x) {
      left = mid;
    } else {
      right = mid;
    }
  }
  return left;
}

//転倒数
long long inv_count(const vector<int> &a) {
  int n = (int)a.size();
  fenwick_tree<int> fw(n);
  long long ans = 0;
  for (int i = 0; i < n; i++) {
    ans += fw.sum(a[i] + 1, n);
    fw.add(a[i], 1);
  }
  return ans;
}

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
  vector<vector<int>> c(26, vector<int>(N + 1, INF_int));
  for (int j = N - 1; j >= 0; j--) {
    int m = S[j] - 'a';
    for (int i = 0; i < 26; i++) {
      if (i == m) {
        c[i][j] = j;
      } else {
        c[i][j] = c[i][j + 1];
      }
    }
  }
  return c;
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

// 行列半時計回り90度回転
template <class T>
vector<vector<T>> matrix_counter_clockwise(vector<vector<T>> &A, int H, int W) {
  vector<vector<T>> B(W, vector<T>(H));
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      int a = -j + (W - 1);
      int b = i;

      B[a][b] = A[i][j];
    }
  }
  return B;
}

//座標圧縮
void compress(vector<long long> &x) {
  map<long long, long long> mp;

  for (int i = 0; i < (int)x.size(); i++) {
    mp[x[i]] = 0;
  }

  long long compress = 1;
  for (auto itr = mp.begin(); itr != mp.end(); itr++) {
    itr->second = compress;
    compress++;
  }

  for (int i = 0; i < (int)x.size(); i++) {
    x[i] = mp[x[i]];
  }
}

//セグ木・遅延セグ木
// segtree<long long, seg::op, seg::e> sgt;
// lazy_segtree<long long, seg::op, seg::e, long long, seg::mapping,
// seg::composition, seg::id> sgt;
namespace seg {
const long long ID = 0;
long long op(long long a, long long b) { return min(a, b); }
long long e() { return INF_ll; }
long long mapping(long long f, long long x) {
  if (f == ID) {
    return x;
  } else {
    return x + f;
  }
}
long long composition(long long f, long long g) {
  if (f == ID) {
    return g;
  } else {
    return f + g;
  }
}
long long id() { return ID; }
long long target;
bool f(long long v) { return v < target; }
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
  long long w;
  Edge(int to, long long w) : to(to), w(w) {}
};

using Graph_int = vector<vector<int>>;
using Graph_Edge = vector<vector<Edge>>;

//部分木サイズ
void subtree_size_cal(const Graph_int &G, int v, vector<int> &subtree_size,
                      int p = -1) {
  for (auto c : G[v]) {
    if (c == p) {
      continue;
    }

    subtree_size_cal(G, c, subtree_size, v);
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

// 深さ優先探索
void DFS(const Graph_int &G, int v, vector<int> &L, vector<int> &R,
         int p = -1) {
  for (auto next_v : G[v]) {
    if (next_v == p) {
      continue;
    }

    DFS(G, next_v, L, R, v);
  }

  // 帰りがけ時に、部分木サイズを求める
  for (auto c : G[v]) {
    if (c == p) {
      continue;
    }

    // 子頂点を根とする部分きのサイズを加算する
    chmin(L[v], L[c]);
    chmax(R[v], R[c]);
  }
}

int main() {
  int N;
  cin >> N;
  Graph_int G(N);
  for (int i = 0; i < N - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    G[u].push_back(v);
    G[v].push_back(u);
  }

  vector<int> L(N, INF_int), R(N, -INF_int);
  int val = 1;
  for (int v = 1; v < N; v++) {
    if (G[v].size() == 1) {
      L[v] = val;
      R[v] = val;
      val++;
    }
  }

  DFS(G, 0, L, R);

  for (int i = 0; i < N; i++) {
    cout << L[i] << " " << R[i] << endl;
  }
}