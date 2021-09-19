#define _GLIBCXX_DEBUG
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

/*
// Union-Find
struct UnionFind
{
    vector<int> par, siz;

    UnionFind(int n) : par(n, -1), siz(n, 1) {}

    // 根を求める
    int root(int x)
    {
        if (par[x] == -1)
            return x;
        else
            return par[x] = root(par[x]);
    }

    // x と y が同じグループに属するかどうか (根が一致するかどうか)
    bool issame(int x, int y)
    {
        return root(x) == root(y);
    }

    // x を含むグループと y を含むグループとを併合する
    bool unite(int x, int y)
    {
        x = root(x), y = root(y);
        if (x == y)
            return false;
        if (siz[x] < siz[y])
            swap(x, y);
        par[y] = x;
        siz[x] += siz[y];
        return true;
    }

    // x を含むグループのサイズ
    int size(int x)
    {
        return siz[root(x)];
    }
};
*/

using namespace std;

struct Hara
{
    int A, num;
};

bool operator<(const Hara &hara_1, const Hara &hara_2)
{
    return hara_1.num > hara_2.num;
}

int main()
{
    int N, M;
    cin >> N >> M;
    vector<long long> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    vector<int> B(M);
    vector<long long> C(M);
    for (int i = 0; i < M; i++)
    {
        cin >> B[i] >> C[i];
    }

    map<long long, int> mp;
    for (int i = 0; i < N; i++)
    {
        if (mp.count(A[i]))
        {
            mp[A[i]]++;
        }
        else
        {
            mp[A[i]] = 1;
        }
    }

    for (int j = 0; j < M; j++)
    {
        //全てのAよりCが小さい時
        if (mp.begin()->first >= C[j])
        {
            continue;
        }

        int counter = 0;
        auto itr = mp.begin();
        while (itr != mp.end())
        {
            if (itr->first < C[j])
            {
                int delta = min(itr->second, B[j] - counter);

                if (mp.count(C[j]))
                {
                    mp[C[j]] += delta;
                }
                else
                {
                    mp[C[j]] = delta;
                }

                counter += delta;
                itr->second -= delta;
                itr++;
                //itr = mp.erase(itr);
            }
            else
            {
                break;
            }

            if (counter == B[j])
            {
                break;
            }
        }
    }

    long long score = 0;
    for (auto itr = mp.begin(); itr != mp.end(); itr++)
    {
        score += itr->first * itr->second;
    }

    cout << score << endl;
}