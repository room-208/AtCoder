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
#include <atcoder/scc>
#include <atcoder/fenwicktree>
#include <atcoder/segtree>
#include <atcoder/lazysegtree>
#include <atcoder/modint>

using namespace std;
using namespace atcoder;
using mint = modint998244353; // modint1000000007 static_modint<1000000009>;

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

// osa_k法
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

//アルファベット表
vector<vector<int>> alphabet_table(string S)
{
    int N = (int)S.size();
    vector<vector<int>> c(26, vector<int>(N + 1, INF_int));
    for (int j = N - 1; j >= 0; j--)
    {
        int m = S[j] - 'a';
        for (int i = 0; i < 26; i++)
        {
            if (i == m)
            {
                c[i][j] = j;
            }
            else
            {
                c[i][j] = c[i][j + 1];
            }
        }
    }
    return c;
}

// unoderedのハッシュ
struct HashPair
{
    //注意 constがいる
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2> &p) const
    {

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
vector<vector<T>> matrix_counter_clockwise(vector<vector<T>> &A, int H, int W)
{
    vector<vector<T>> B(W, vector<T>(H));
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            int a = -j + (W - 1);
            int b = i;

            B[a][b] = A[i][j];
        }
    }
    return B;
}

//座標圧縮
void compress(vector<long long> &x)
{
    map<long long, long long> mp;

    for (int i = 0; i < (int)x.size(); i++)
    {
        mp[x[i]] = 0;
    }

    long long compress = 1;
    for (auto itr = mp.begin(); itr != mp.end(); itr++)
    {
        itr->second = compress;
        compress++;
    }

    for (int i = 0; i < (int)x.size(); i++)
    {
        x[i] = mp[x[i]];
    }
}

//セグ木・遅延セグ木
// lazy_segtree<long long, seg::op, seg::e, long long, seg::mapping, seg::composition, seg::id> sgt;
namespace seg
{
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
        return x + f;
    }
    long long composition(long long f, long long g)
    {
        return f + g;
    }
    long long id()
    {
        return 0;
    }
}

int main()
{
    int N, Q;
    cin >> N >> Q;
    string S;
    cin >> S;
    vector<int> t(Q), l(Q), r(Q);
    for (int i = 0; i < Q; i++)
    {
        cin >> t[i] >> l[i] >> r[i];
        l[i]--;
        r[i]--;
    }

    lazy_segtree<long long, seg::op, seg::e, long long, seg::mapping, seg::composition, seg::id> sgt(N + 1);
    sgt.set(0, 0);
    for (int i = 0; i < N; i++)
    {
        int v = sgt.get(i);

        if (S[i] == '(')
        {
            sgt.set(i + 1, v + 1);
        }
        else if (S[i] == ')')
        {
            sgt.set(i + 1, v - 1);
        }
    }

    /*
    for (int i = 0; i <= N; i++)
    {
        cout << sgt.get(i) << " " << endl;
    }
    cout << endl;
    */

    for (int i = 0; i < Q; i++)
    {
        /*
        for (int i = 0; i <= N; i++)
        {
            cout << sgt.get(i) << " ";
        }
        cout << endl;
        */

        if (t[i] == 1)
        {
            if (S[l[i]] == S[r[i]])
            {
                continue;
            }
            else if (S[l[i]] == '(' && S[r[i]] == ')')
            {
                sgt.apply(l[i] + 1, r[i] + 1, -2);
                swap(S[l[i]], S[r[i]]);
            }
            else if (S[l[i]] == ')' && S[r[i]] == '(')
            {
                sgt.apply(l[i] + 1, r[i] + 1, 2);
                swap(S[l[i]], S[r[i]]);
            }
        }
        else if (t[i] == 2)
        {
            int v = sgt.prod(l[i], r[i] + 2);
            int begin = sgt.get(l[i]);
            int end = sgt.get(r[i] + 1);

            if (v == begin && end == begin)
            {
                cout << "Yes" << endl;
            }
            else
            {
                cout << "No" << endl;
            }
        }
    }
}