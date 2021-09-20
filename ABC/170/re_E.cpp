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

long long fac[COM_MAX], finv[COM_MAX], inv[COM_MAX];

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

//転倒数
long long inv_count(const vector<int> &a)
{
    int n = (int)a.size();
    fenwick_tree<int> fw(n);
    long long ans = 0;
    for (int i = 0; i < n; i++)
    {
        ans += fw.sum(a[i] + 1, n);
        fw.add(a[i], 1);
    }
    return ans;
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
//segtree<long long, seg::op, seg::e> sgt;
//lazy_segtree<long long, seg::op, seg::e, long long, seg::mapping, seg::composition, seg::id> sgt;
namespace seg
{
    const long long ID = 0;
    long long op(long long a, long long b)
    {
        return min(a, b);
    }
    long long e()
    {
        return INF_ll;
    }
    long long mapping(long long f, long long x)
    {
        if (f == ID)
        {
            return x;
        }
        else
        {
            return x + f;
        }
    }
    long long composition(long long f, long long g)
    {
        if (f == ID)
        {
            return g;
        }
        else
        {
            return f + g;
        }
    }
    long long id()
    {
        return ID;
    }
    long long target;
    bool f(long long v) { return v < target; }
}

int main()
{
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N), B(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i] >> B[i];
        B[i]--;
    }
    vector<int> C(Q), D(Q);
    for (int i = 0; i < Q; i++)
    {
        cin >> C[i] >> D[i];
        C[i]--;
        D[i]--;
    }

    int M = 200000;
    vector<set<pair<int, int>>> st(M);
    segtree<long long, seg::op, seg::e> sgt(M);
    for (int i = 0; i < N; i++)
    {
        st[B[i]].insert(make_pair(A[i], i));
    }
    for (int i = 0; i < M; i++)
    {
        if (st[i].empty())
        {
            continue;
        }

        long long s = prev(st[i].end())->first;
        sgt.set(i, s);
    }

    for (int q = 0; q < Q; q++)
    {
        int i = C[q];
        int a = A[i];
        int b = B[i];
        B[i] = D[q];
        int d = D[q];

        //出る
        st[b].erase(make_pair(a, i));
        if (st[b].empty())
        {
            sgt.set(b, INF_ll);
        }
        else
        {
            long long s = prev(st[b].end())->first;
            sgt.set(b, s);
        }

        //入る
        st[d].insert(make_pair(a, i));
        if (st[d].empty())
        {
            sgt.set(d, INF_ll);
        }
        else
        {
            long long s = prev(st[d].end())->first;
            sgt.set(d, s);
        }

        cout << sgt.all_prod() << endl;
    }
}