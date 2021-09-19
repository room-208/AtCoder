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

bool operator<(const Hara &a, const Hara &b)
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

    sort(h.begin(), h.end());

    UnionFind uf(N);
    set<int> st;
    vector<int> his;

    st.insert(0);

    for (int i = 1; i < N; i++)
    {
        for (auto itr = st.begin(); itr != st.end(); itr++)
        {
            int j = *itr;

            if (h[j].y < h[i].y)
            {
                uf.unite(h[i].num, h[j].num);
                his.push_back(j);
            }
        }

        int SIZE = his.size();

        if (SIZE == 0)
        {
            st.insert(i);
        }
        else
        {
            his.pop_back();

            while (!his.empty())
            {
                int j = his.back();
                st.erase(j);
                his.pop_back();
            }
        }
    }

    //初期化
    for (int i = 0; i < N; i++)
    {
        cout << uf.size(i) << endl;
    }

    return 0;
}
