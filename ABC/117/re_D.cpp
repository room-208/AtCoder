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

using namespace std;
using namespace atcoder;

const int MOD = 1000000007;
const int INF_int = 1000000000;
const long long INF_ll = 1000000000000000000LL;
const int COM_MAX = 510000;

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

long long f(long long x, vector<long long> &A)
{
    long long f = 0;
    for (int i = 0; i < (int)A.size(); i++)
    {
        f += (x ^ A[i]);
    }
    return f;
}

int main()
{
    int N;
    long long K;
    cin >> N >> K;
    vector<long long> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    int M = 64;
    vector<vector<long long>> dp(2, vector<long long>(M + 1, -1));
    for (int j = 1; j <= M; j++)
    {
        long long d = M - j;
        long long msk = (1LL << d);

        long long zero = 0;
        long long one = 0;
        for (int i = 0; i < N; i++)
        {
            if (A[i] & msk)
            {
                one++;
            }
            else
            {
                zero++;
            }
        }

        if (K & msk)
        {
            if (dp[0][j - 1] == -1)
            {
                dp[0][j] = zero * msk;
                dp[1][j] = one * msk;
            }
            else
            {
                dp[0][j] = dp[0][j - 1] + zero * msk;
                chmax(dp[1][j], dp[0][j - 1] + one * msk);
                chmax(dp[1][j], dp[1][j - 1] + zero * msk);
                chmax(dp[1][j], dp[1][j - 1] + one * msk);
            }
        }
        else
        {
            if (dp[0][j - 1] == -1)
            {
                if (one > 0)
                {
                    dp[0][j] = one * msk;
                }
            }
            else
            {
                dp[0][j] = dp[0][j - 1] + one * msk;
                chmax(dp[1][j], dp[1][j - 1] + zero * msk);
                chmax(dp[1][j], dp[1][j - 1] + one * msk);
            }
        }
    }

    long long ans = -1;
    chmax(ans, f(0, A));
    chmax(ans, dp[0][M]);
    chmax(ans, dp[1][M]);

    cout << ans << endl;
}