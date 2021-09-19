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

using Graph_int = vector<vector<int>>;

// 深さ優先探索
void DFS(const Graph_int &G, int v, vector<bool> &seen, unordered_map<int, int> &mp, vector<int> &C, vector<int> &A)
{
    seen[v] = true;
    if (!mp.count(C[v]))
    {
        A.push_back(v);
    }
    else if (mp[C[v]] == 0)
    {
        A.push_back(v);
    }

    if (!mp.count(C[v]))
    {
        mp[C[v]] = 1;
    }
    else
    {
        mp[C[v]]++;
    }

    for (auto next_v : G[v])
    {
        if (seen[next_v])
        {
            continue;
        }

        DFS(G, next_v, seen, mp, C, A);
    }

    mp[C[v]]--;
}

int main()
{
    int N;
    cin >> N;
    vector<int> C(N);
    for (int i = 0; i < N; i++)
    {
        cin >> C[i];
        C[i]--;
    }
    Graph_int G(N);
    int M = N - 1;
    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    unordered_map<int, int> mp;
    vector<bool> seen(N, false);
    vector<int> A;
    DFS(G, 0, seen, mp, C, A);
    sort(A.begin(), A.end());

    for (auto a : A)
    {
        cout << a + 1 << endl;
    }
}