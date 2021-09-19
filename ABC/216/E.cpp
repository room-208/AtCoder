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

//等差数列の和
long long tousa_sum(long long a, long long d, long long n)
{
    return (a * 2 + d * (n - 1)) * n / 2;
}

int main()
{
    int N;
    cin >> N;
    long long K;
    cin >> K;
    vector<long long> A(N + 1, 0);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    sort(A.begin(), A.end());
    reverse(A.begin(), A.end());

    long long ans = 0;
    long long r = 0;

    while (1)
    {
        if (K == 0)
        {
            break;
        }

        if (A[r] == 0)
        {
            break;
        }

        long long d_A = A[r] - A[r + 1];
        long long t = d_A * (r + 1);

        if (K >= t)
        {
            K -= t;
            long long sum = tousa_sum(A[r], -1LL, d_A) * (r + 1);
            ans += sum;
            r++;
        }
        else
        {
            long long p = K % (r + 1);
            long long n = (K - p) / (r + 1);
            long long sum = tousa_sum(A[r], -1LL, n) * (r + 1);
            ans += sum;
            A[r] -= n;
            for (int i = 0; i < p; i++)
            {
                ans += A[r];
            }
            K = 0;
        }
    }

    cout << ans << endl;
}