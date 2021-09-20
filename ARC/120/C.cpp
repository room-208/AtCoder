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

int main()
{
    int N;
    cin >> N;
    vector<int> A(N), B(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
        A[i] += i;
    }
    for (int i = 0; i < N; i++)
    {
        cin >> B[i];
        B[i] += i;
    }

    map<int, int> mp;
    for (int i = 0; i < N; i++)
    {
        mp[A[i]] = 0;
    }
    int cnt = 0;
    for (auto itr = mp.begin(); itr != mp.end(); itr++)
    {
        itr->second = cnt;
        cnt++;
    }
    vector<int> a(N), b(N);
    for (int i = 0; i < N; i++)
    {
        a[i] = mp[A[i]];
        b[i] = mp[B[i]];
    }

    unordered_map<int, int> mp_a, mp_b;
    for (int i = 0; i < N; i++)
    {
        mp_a[a[i]]++;
        mp_b[b[i]]++;
    }

    bool flag = true;
    for (auto itr = mp_a.begin(); itr != mp_a.end(); itr++)
    {
        int key = itr->first;
        int n = itr->second;

        if (mp_b[key] != n)
        {
            flag = false;
        }
    }
    for (auto itr = mp_b.begin(); itr != mp_b.end(); itr++)
    {
        int key = itr->first;
        int n = itr->second;

        if (mp_a[key] != n)
        {
            flag = false;
        }
    }

    if (!flag)
    {
        cout << -1 << endl;
        return 0;
    }

    vector<deque<int>> c(N);
    for (int i = 0; i < N; i++)
    {
        c[b[i]].push_back(i);
    }

    vector<int> d(N);
    for (int i = 0; i < N; i++)
    {
        d[i] = c[a[i]][0];
        c[a[i]].pop_front();
    }

    cout << inv_count(d) << endl;
}