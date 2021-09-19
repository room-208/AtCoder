//#define _GLIBCXX_DEBUG
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

/*
vector<int> a(N);
vector<vector<int>> a(N, vector<int>(N));
auto itr = a.begin();
for (auto itr = a.begin(); itr != a.end(); itr++)
{
    cout << itr - a.begin() << endl; = 0,1,...,N-1
}
sort(a.begin(), a.end());
reverse(a.begin(), a.end());
*/

/*
list<int> lst;
lst.push_front(i);
lst.push_back(i);
lst.pop_front();
lst.pop_back();
for(auto itr = lst.begin(); itr != lst.end(); ++itr) {
    std::cout << *itr << "\n";
}
*/

/*
bool cmp(const std::pair<int, int> &a, const std::pair<int, int> &b)
{
    return a.first < b.first;
}
vector<pair<int, int>> p(N);
for (int i = 0; i < N; i++)
{
    p[i].first = a[i];
    p[i].second = b[i];
}
sort(p.begin(), p.end(), cmp);
for (int i = 0; i < N; i++)
{
    a[i] = p[i].first;
    b[i] = p[i].second;
}
*/

/*
std::unordered_set<int> hash;
*/

/*
struct Edge
{
    int to;
    long long w;
    Edge(int to, long long w) : to(to), w(w) {}
};
using Graph = vector<vector<Edge>>;
Graph G(N);
    for (int i = 0; i < M; ++i) {
        int a, b;
        long long w;
        cin >> a >> b >> w;
        G[a].push_back(Edge(b, w));
    }
*/

using namespace std;

const int MAX = 510000;
const int MOD = 1000000007;
const int INF = 1000000000;

long long fac[MAX], finv[MAX], inv[MAX];

// テーブルを作る前処理
void COMinit()
{
    fac[0] = fac[1] = 1;
    finv[0] = finv[1] = 1;
    inv[1] = 1;
    for (int i = 2; i < MAX; i++)
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
            return 0;
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

struct Hara
{
    int a, b;
};

bool operator<(const Hara &hara_1, const Hara &hara_2)
{
    return hara_1.b > hara_2.b;
}

int main()
{
    int N;
    cin >> N;
    vector<int> x, y, h;
    vector<int> x_zero, y_zero, h_zero;
    for (int i = 0; i < N; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;

        if (c == 0)
        {
            x_zero.push_back(a);
            y_zero.push_back(b);
            h_zero.push_back(c);
        }
        else
        {
            x.push_back(a);
            y.push_back(b);
            h.push_back(c);
        }
    }

    int SIZE = x.size();
    int SIZE_zero = x_zero.size();

    for (int C_x = 0; C_x <= 100; C_x++)
    {
        for (int C_y = 0; C_y <= 100; C_y++)
        {
            int H = h[0] + abs(x[0] - C_x) + abs(y[0] - C_y);
            bool flag = true;

            if (H < 1)
            {
                continue;
            }

            for (int i = 1; i < SIZE; i++)
            {
                int H_tmp = h[i] + abs(x[i] - C_x) + abs(y[i] - C_y);

                if (H != H_tmp)
                {
                    flag = false;
                    break;
                }
            }

            if (flag)
            {
                bool flag_zero = true;
                for (int i = 0; i < SIZE_zero; i++)
                {
                    int tmp = H - abs(x_zero[i] - C_x) - abs(y_zero[i] - C_y);

                    if (tmp > 0)
                    {
                        flag_zero = false;
                        break;
                    }
                }

                if (flag_zero)
                {
                    cout << C_x << " " << C_y << " " << H << endl;
                    C_x = INF;
                    C_y = INF;
                }
            }
        }
    }
}