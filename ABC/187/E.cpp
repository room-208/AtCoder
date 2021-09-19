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

void DFS_par(const Graph_int &G, int p, int v, vector<int> &par)
{
    for (auto next_v : G[v])
    {
        if (p == next_v)
        {
            continue;
        }

        DFS_par(G, v, next_v, par);
    }

    par[v] = p;
}

void DFS_cal(const Graph_int &G, int p, int v, vector<long long> &c)
{
    for (auto next_v : G[v])
    {
        if (p == next_v)
        {
            continue;
        }

        c[next_v] += c[v];
        DFS_cal(G, v, next_v, c);
    }
}

int main()
{
    int N;
    cin >> N;
    int M = N - 1;
    Graph_int G(N);
    vector<int> A(M), B(M);
    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        A[i] = a;
        B[i] = b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    int Q;
    cin >> Q;
    vector<int> t(Q), e(Q), x(Q);
    for (int q = 0; q < Q; q++)
    {
        cin >> t[q] >> e[q] >> x[q];
        e[q]--;
    }

    //根つき木
    vector<int> par(N, -1);
    DFS_par(G, 0, 0, par);

    vector<long long> c(N, 0);
    for (int q = 0; q < Q; q++)
    {
        if (t[q] == 1)
        {
            int a = A[e[q]];
            int b = B[e[q]];

            if (par[a] == b)
            {
                c[a] += x[q];
            }
            else
            {
                c[0] += x[q];
                c[b] -= x[q];
            }
        }
        if (t[q] == 2)
        {
            int a = A[e[q]];
            int b = B[e[q]];

            if (par[b] == a)
            {
                c[b] += x[q];
            }
            else
            {
                c[0] += x[q];
                c[a] -= x[q];
            }
        }
    }

    DFS_cal(G, 0, 0, c);
    for (int i = 0; i < N; i++)
    {
        cout << c[i] << endl;
    }
}