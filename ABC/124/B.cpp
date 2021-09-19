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

struct Hara
{
    int A, B;
};

bool cmp(const Hara &a, const Hara &b)
{
    return a.A < b.A;
}

sort(h.begin(), h.end(), cmp);
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

/*
struct Hara
{
    long long a, b;
};
bool operator<(const Hara &hara_1, const Hara &hara_2)
{
    return hara_1.b < hara_2.b;
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

long long GCD(long long m, long long n)
{
    if (m < n)
    {
        swap(m, n);
    }
    // ベースケース
    if (n == 0)
    {
        return m;
    }

    // 再帰呼び出し
    return GCD(n, m % n);
}

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
    vector<int> H(N);
    for (int i = 0; i < N; i++)
    {
        cin >> H[i];
    }

    int counter = 1;
    for (int i = 1; i < N; i++)
    {
        bool flag = true;
        for (int j = 0; j < i; j++)
        {
            if (H[j] > H[i])
            {
                flag = false;
                break;
            }
        }

        if (flag)
        {
            counter++;
        }
    }

    cout << counter << endl;
}
