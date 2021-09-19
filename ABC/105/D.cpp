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

int main()
{
    int N, M;
    cin >> N >> M;
    vector<long long> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    vector<long long> S(N + 1);
    S[0] = 0;
    for (int i = 0; i < N; i++)
    {
        S[i + 1] = S[i] + A[i];
    }
    for (int i = 0; i <= N; i++)
    {
        S[i] %= M;
    }

    unordered_map<long long, int> mp;
    for (int i = 0; i <= N; i++)
    {
        if (mp.count(S[i]))
        {
            mp[S[i]]++;
        }
        else
        {
            mp[S[i]] = 1;
        }
    }

    long long ans = 0;
    for (auto itr = mp.begin(); itr != mp.end(); itr++)
    {
        long long n = itr->second;
        ans += (n * (n - 1)) / 2;
    }

    cout << ans << endl;
}