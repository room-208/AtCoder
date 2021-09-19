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
#include <atcoder/fenwicktree>
#include <atcoder/segtree>
#include <atcoder/lazysegtree>

using namespace std;
using namespace atcoder;

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

//繰り返し二乗法
long long MOD_pow(long long a, long long n)
{
    long long res = 1;
    while (n > 0)
    {
        if (n & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        n >>= 1;
    }
    return res;
}

//等差数列の和
long long tousa_sum(long long a, long long d, long long n)
{
    return (a * 2 + d * (n - 1)) * n / 2;
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

//拡張GCD
long long extgcd(long long a, long long b, long long &x, long long &y)
{
    if (b == 0)
    {
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

//unoderedのハッシュ
struct HashPair
{

    //注意 constがいる
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2> &p) const
    {

        //first分をハッシュ化する
        auto hash1 = hash<T1>{}(p.first);

        //second分をハッシュ化する
        auto hash2 = hash<T2>{}(p.second);

        //重複しないようにハッシュ処理
        size_t seed = 0;
        seed ^= hash1 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= hash2 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};

//セグ木・遅延セグ木
struct S
{
    long long value;
    int index;
};
S op_max(S a, S b)
{
    if (a.value > b.value)
    {
        return a;
    }
    else
    {
        return b;
    }
}
S e_max()
{
    return {-INF_ll, -1};
}
S op_min(S a, S b)
{
    if (a.value < b.value)
    {
        return a;
    }
    else
    {
        return b;
    }
}
S e_min()
{
    return {INF_ll, -1};
}

int main()
{
    int N;
    long long Z, W;
    cin >> N >> Z >> W;
    vector<long long> a(N);
    for (int i = 0; i < N; i++)
    {
        cin >> a[i];
    }

    vector<S> b(N);
    for (int i = 0; i < N; i++)
    {
        b[i].value = a[i];
        b[i].index = i;
    }
    long long X = Z;
    long long Y = W;
    int flag = 0;
    int n = 0;
    segtree<S, op_max, e_max> sgt_max(b);
    segtree<S, op_min, e_min> sgt_min(b);
    while (n != N)
    {
        if (flag == 0)
        {
            S x_max = sgt_max.prod(n, N);
            X = x_max.value;
            n = x_max.index + 1;
        }
        else if (flag == 1)
        {
            S x_min = sgt_min.prod(n, N);
            Y = x_min.value;
            n = x_min.index + 1;
        }

        flag = 1 - flag;
    }

    long long ans = -1;
    chmax(ans, llabs(X - Y));

    X = Z;
    Y = W;
    flag = 0;
    n = 0;
    while (n != N)
    {
        if (flag == 0)
        {
            S x_min = sgt_min.prod(n, N);
            X = x_min.value;
            n = x_min.index + 1;
        }
        else if (flag == 1)
        {
            S x_max = sgt_max.prod(n, N);
            Y = x_max.value;
            n = x_max.index + 1;
        }

        flag = 1 - flag;
    }
    chmax(ans, llabs(X - Y));

    cout << ans << endl;
}