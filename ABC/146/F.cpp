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

//セグ木・遅延セグ木
long long sgt_op(long long a, long long b)
{
    return min(a, b);
}
long long sgt_e()
{
    return INF_ll;
}
long long sgt_target;
bool sgt_f(long long v) { return v > sgt_target; }

int main()
{
    int N, M;
    cin >> N >> M;
    string S;
    cin >> S;
    reverse(S.begin(), S.end());

    segtree<long long, sgt_op, sgt_e> dp(N + 1);
    dp.set(0, 0);
    for (int i = 1; i <= N; i++)
    {
        if (S[i] == '1')
        {
            continue;
        }

        int l = i - M;
        int r = i;
        if (l < 0)
        {
            l = 0;
        }

        long long v = dp.prod(l, r);

        if (v != INF_ll)
        {
            dp.set(i, v + 1);
        }
    }

    /*
    for (int i = 0; i <= N; i++)
    {
        cout << dp.get(i) << " ";
    }
    cout << endl;
    */

    if (dp.get(N) == INF_ll)
    {
        cout << -1 << endl;
    }
    else
    {
        long long v = dp.get(N);
        v--;
        int j = N;
        for (int i = N - 1; i >= 0; i--)
        {
            if (v == dp.get(i))
            {
                cout << j - i << " ";
                j = i;
                v--;
            }
        }
        cout << endl;
    }
}