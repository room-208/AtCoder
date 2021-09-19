//#define _GLIBCXX_DEBUG
#define _USE_MATH_DEFINES
#include <iostream>
#include <time.h>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
#include <functional>
#include <random>
#include <string>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <bits/stdc++.h>
#include <deque>
#include <queue>
#include <list>
#include <atcoder/all>

using namespace std;

const int MOD = 1000000007;
const int INF_int = 1000000000;
const long long INF_ll = 1000000000000000000LL;
const int COM_MAX = 510000;
const int COM_pskl_N = 60;

long long fac[COM_MAX], finv[COM_MAX], inv[COM_MAX];
vector<vector<long long>> com_pskl;

// テーブルを作る前処理
void COMinit()
{
    fac[0] = fac[1] = 1;
    finv[0] = finv[1] = 1;
    inv[1] = 1;
    for (int i = 2; i < COM_MAX; i++)
    {
        fac[i] = fac[i - 1] * i % MOD;
        inv[i] = MOD - inv[MOD % i] * (MOD / i) % MOD;
        finv[i] = finv[i - 1] * inv[i] % MOD;
    }
}

// 二項係数計算
long long COM(int n, int k)
{
    if (n < k)
        return 0;
    if (n < 0 || k < 0)
        return 0;
    return fac[n] * (finv[k] * finv[n - k] % MOD) % MOD;
}

//パスカルの三角形の二項係数
void COM_paskal()
{
    com_pskl.assign(COM_pskl_N, vector<long long>(COM_pskl_N));
    com_pskl[0][0] = 1;
    for (int i = 1; i < COM_pskl_N; ++i)
    {
        com_pskl[i][0] = 1;
        for (int j = 1; j < COM_pskl_N; j++)
        {
            com_pskl[i][j] = (com_pskl[i - 1][j - 1] + com_pskl[i - 1][j]);
        }
    }
}

//最大公約数
template <class T>
T GCD(T m, T n)
{
    // ベースケース
    if (n == 0)
    {
        return m;
    }

    // 再帰呼び出し
    return GCD(n, m % n);
}

//osa_k法
vector<int> osa_k(int n)
{
    vector<int> res(n + 1);
    iota(res.begin(), res.end(), 0);
    for (int i = 2; i * i <= n; ++i)
    {
        //合成数の判定
        if (res[i] < i)
        {
            continue;
        }

        //最小の素因数の代入
        for (int j = i * i; j <= n; j += i)
        {
            if (res[j] == j)
            {
                res[j] = i;
            }
        }
    }
    return res;
}

//最大・最小化
template <class T>
bool chmax(T &a, const T &b)
{
    if (a < b)
    {
        a = b;
        return 1;
    }
    return 0;
}
template <class T>
bool chmin(T &a, const T &b)
{
    if (b < a)
    {
        a = b;
        return 1;
    }
    return 0;
}

//連長圧縮
vector<pair<char, int>> runLengthEncoding(string s)
{
    int n = s.length();

    vector<pair<char, int>> res;
    char pre = s[0];
    int cnt = 1;
    for (int i = 1; i < n; i++)
    {
        if (pre != s[i])
        {
            res.push_back({pre, cnt});
            pre = s[i];
            cnt = 1;
        }
        else
        {
            cnt++;
        }
    }

    res.push_back({pre, cnt});
    return res;
}

//セグメントツリー
//SegTree<int, 1 << 19> st;
template <class V, int NV>
struct SegTree
{ //[l,r)

    //computationで関数を計算
    V comp(V &l, V &r) { return GCD(l, r); };

    vector<V> val;
    SegTree() { val = vector<V>(NV * 2, 0); }
    V get(int x, int y, int l = 0, int r = NV, int k = 1)
    {
        if (r <= x || y <= l)
            return -INF_int;
        if (x <= l && r <= y)
            return val[k];
        auto a = get(x, y, l, (l + r) / 2, k * 2);
        auto b = get(x, y, (l + r) / 2, r, k * 2 + 1);
        return comp(a, b);
    }
    void update(int i, V v)
    {
        i += NV;
        val[i] = v;
        while (i > 1)
            i >>= 1, val[i] = comp(val[i * 2], val[i * 2 + 1]);
    }
    void add(int i, V v) { update(i, val[i + NV] + v); }
    V operator[](int x) { return get(x, x + 1); }
};

// Union-Find
struct UnionFind
{
    vector<int> par, siz;

    // 初期化
    UnionFind(int n) : par(n, -1), siz(n, 1) {}

    // 根を求める
    int root(int x)
    {
        if (par[x] == -1)
            return x; // x が根の場合は x を返す
        else
            return par[x] = root(par[x]);
    }

    // x と y が同じグループに属するかどうか (根が一致するかどうか)
    bool issame(int x, int y)
    {
        return root(x) == root(y);
    }

    // x を含むグループと y を含むグループとを併合する
    bool unite(int x, int y)
    {
        // x, y をそれぞれ根まで移動する
        x = root(x);
        y = root(y);

        // すでに同じグループのときは何もしない
        if (x == y)
            return false;

        // union by size (y 側のサイズが小さくなるようにする)
        if (siz[x] < siz[y])
            swap(x, y);

        // y を x の子とする
        par[y] = x;
        siz[x] += siz[y];
        return true;
    }

    // x を含むグループのサイズ
    int size(int x)
    {
        return siz[root(x)];
    }
};

//エッジ集合
struct Edge
{
    int to;
    long long w;
    Edge(int to, long long w) : to(to), w(w) {}
};

using Graph_int = vector<vector<int>>;
using Graph_Edge = vector<vector<Edge>>;

// 深さ優先探索
void DFS(const Graph_int &G, int v, vector<bool> &seen)
{
    seen[v] = true;

    for (auto next_v : G[v])
    {
        if (seen[next_v])
        {
            continue;
        }

        DFS(G, next_v, seen);
    }
}

//幅優先探索
void BFS(const Graph_int &G, int s)
{
    int N = (int)G.size();   // 頂点数
    vector<int> dist(N, -1); // 全頂点を「未訪問」に初期化
    queue<int> que;

    // 初期条件 (頂点 s を初期頂点とする)
    dist[s] = 0;
    que.push(s); // s を橙色頂点にする

    // BFS 開始 (キューが空になるまで探索を行う)
    while (!que.empty())
    {
        int v = que.front(); // キューから先頭頂点を取り出す
        que.pop();

        // v からたどれる頂点をすべて調べる
        for (int x : G[v])
        {
            // すでに発見済みの頂点は探索しない
            if (dist[x] != -1)
                continue;

            // 新たな白色頂点 x について距離情報を更新してキューに挿入
            dist[x] = dist[v] + 1;
            que.push(x);
        }
    }
}

//01BFS
void BFS_01(const Graph_Edge &G, int s)
{
    int N = (int)G.size();             // 頂点数
    vector<long long> dist(N, INF_ll); // 全頂点を「未訪問」に初期化
    deque<int> que;

    // 初期条件 (頂点 s を初期頂点とする)
    dist[s] = 0;
    que.push_front(s);

    // BFS 開始 (キューが空になるまで探索を行う)
    while (!que.empty())
    {
        int v = que.front(); // キューから先頭頂点を取り出す
        que.pop_front();

        // v からたどれる頂点をすべて調べる
        for (auto x : G[v])
        {
            if (chmin(dist[x.to], dist[v] + x.w))
            {
                if (x.w == 0)
                {
                    que.push_front(x.to);
                }
                if (x.w == 1)
                {
                    que.push_back(x.to);
                }
            }
        }
    }
}

//ベルマン・フォード法
void Bellman_Ford(const Graph_Edge &G, int s)
{
    int N = (int)G.size();
    bool exist_negative_cycle = false; // 負閉路をもつかどうか
    vector<long long> dist(N, INF_ll);
    dist[s] = 0;

    for (int iter = 0; iter < N; ++iter)
    {
        bool update = false; // 更新が発生したかどうかを表すフラグ
        for (int v = 0; v < N; ++v)
        {
            // dist[v] = INF のときは頂点 v からの緩和を行わない
            if (dist[v] == INF_ll)
                continue;

            for (auto e : G[v])
            {
                // 緩和処理を行い，更新されたら update を true にする
                if (chmin(dist[e.to], dist[v] + e.w))
                {
                    update = true;
                }
            }
        }

        // 更新が行われなかったら，すでに最短路が求められている
        if (!update)
            break;

        // N 回目の反復で更新が行われたならば，負閉路をもつ
        if (iter == N - 1 && update)
            exist_negative_cycle = true;
    }
}

//ダイクストラ法
void Dijkstra(const Graph_Edge &G, int s)
{
    int N = (int)G.size();
    vector<long long> dist(N, INF_ll);
    dist[s] = 0;

    // (d[v], v) のペアを要素としたヒープを作る
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> que;
    que.push(make_pair(dist[s], s));

    // ダイクストラ法の反復を開始
    while (!que.empty())
    {
        // v: 使用済みでない頂点のうち d[v] が最小の頂点
        // d: v に対するキー値
        int v = que.top().second;
        long long d = que.top().first;
        que.pop();

        // d > dist[v] は，(d, v) がゴミであることを意味する
        if (d > dist[v])
            continue;

        // 頂点 v を始点とした各辺を緩和
        for (auto e : G[v])
        {
            if (chmin(dist[e.to], dist[v] + e.w))
            {
                // 更新があるならヒープに新たに挿入
                que.push(make_pair(dist[e.to], e.to));
            }
        }
    }
}

//オーバーフロー判定
//__builtin_add_overflow
//__builtin_mul_overflow

//ノード変換
int to_node(int i, int j, int W)
{
    return W * i + j;
}

//in_out判定
bool in_out(int i, int j, int H, int W)
{
    if (0 <= i && i < H && 0 <= j && j < W)
    {
        return true;
    }

    return false;
}

struct my_struct
{
    int a, b;
};

bool operator<(const my_struct &s_1, const my_struct &s_2)
{
    return s_1.b > s_2.b;
}

int main()
{
    string S;
    cin >> S;

    if (S == "Hello,World!")
    {
        cout << "AC" << endl;
    }
    else
    {
        cout << "WA" << endl;
    }
}