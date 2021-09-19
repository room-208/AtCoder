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

using namespace std;

const long long INF = 1000000000000000000LL;

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

struct Edge
{
    int to;
    long long w;
    Edge(int to, long long w) : to(to), w(w) {}
};

using Graph = vector<vector<Edge>>;

int main()
{
    int N, M;
    cin >> N >> M;
    Graph G(N);
    for (int i = 0; i < M; i++)
    {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        a--;
        b--;
        G[a].push_back(Edge(b, -c));
    }

    bool flag = true;
    vector<long long> dist(N, INF);
    dist[0] = 0;
    for (int i = 0; i < N; i++)
    {
        bool update = false;
        for (int v = 0; v < N; v++)
        {
            if (dist[v] == INF)
            {
                continue;
            }

            for (auto e : G[v])
            {
                if (chmin(dist[e.to], dist[v] + e.w))
                {
                    update = true;
                }
            }
        }

        if (!update)
        {
            break;
        }

        if (update && i == N - 1)
        {
            flag = false;
        }
    }

    if (flag)
    {
        cout << -dist[N - 1] << endl;
    }
    else
    {
        cout << "inf" << endl;
    }
}