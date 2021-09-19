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
*/

/*
std::unordered_set<int> hash; //(a,b)のxまでの履歴
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

using namespace std;

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

struct Hara
{
    int x, y, num;
};

bool cmp(const Hara &a, const Hara &b)
{
    return a.x < b.x;
}

int main()
{
    int N;
    cin >> N;
    vector<Hara> h(N);
    for (int i = 0; i < N; i++)
    {
        cin >> h[i].x >> h[i].y;
        h[i].x--;
        h[i].y--;
        h[i].num = i;
    }

    sort(h.begin(), h.end(), cmp);

    /*
    for (int i = 0; i < N; i++)
    {
        cout << h[i].x << "\t" << h[i].y << "\t" << h[i].num << endl;
    }
    */

    /*
    UnionFind uf(N);
    set<int> st;

    st.insert(0);
    for (int i = 1; i < N; i++)
    {
        bool flag = true;

        for (auto itr = st.begin(); itr != st.end(); itr++)
        {
            int j = *itr;

            if (h[j].y < h[i].y)
            {
                uf.unite(h[i].num, h[j].num);
                flag = false;
            }
        }

        if (flag)
        {
            st.insert(i);
        }
    }
    */

    UnionFind uf(N);
    vector<int> memo;

    memo.push_back(0);
    for (int i = 1; i < N; i++)
    {
        bool flag = true;

        for (auto itr = memo.begin(); itr != memo.end(); itr++)
        {
            int j = *itr;

            if (h[j].y < h[i].y)
            {
                uf.unite(h[i].num, h[j].num);
                flag = false;
            }
        }

        if (flag)
        {
            memo.push_back(i);
        }
    }

    //初期化
    for (int i = 0; i < N; i++)
    {
        cout << uf.size(i) << endl;
    }

    return 0;
}
