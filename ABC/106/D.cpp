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

int main()
{
    int N, M, Q;
    cin >> N >> M >> Q;
    vector<int> L(M), R(M);
    for (int i = 0; i < M; i++)
    {
        cin >> L[i] >> R[i];
        L[i]--;
        R[i]--;
    }
    vector<int> p(Q), q(Q);
    for (int i = 0; i < Q; i++)
    {
        cin >> p[i] >> q[i];
        p[i]--;
        q[i]--;
    }

    unordered_map<pair<int, int>, int, HashPair> mp_cnt;
    for (int i = 0; i < M; i++)
    {
        if (mp_cnt.count(make_pair(L[i], R[i])))
        {
            mp_cnt[make_pair(L[i], R[i])]++;
        }
        else
        {
            mp_cnt[make_pair(L[i], R[i])] = 1;
        }
    }

    unordered_map<pair<int, int>, int, HashPair> mp;
    for (int i = 0; i < N; i++)
    {
        int cnt = 0;
        for (int j = i; j < N; j++)
        {
            if (mp_cnt.count(make_pair(i, j)))
            {
                cnt += mp_cnt[make_pair(i, j)];
            }

            mp[make_pair(i, j)] = cnt;
        }
    }

    for (int i = 0; i < Q; i++)
    {
        int ans = 0;
        for (int k = p[i]; k <= q[i]; k++)
        {
            ans += mp[make_pair(k, q[i])];
        }

        cout << ans << endl;
    }
}