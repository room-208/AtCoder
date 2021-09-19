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

const int Mod = 1000000007;
const int INF = 1000000000;

int main()
{
    int H, W;
    cin >> H >> W;
    vector<vector<char>> s(H, vector<char>(W));
    vector<vector<int>> row(H), col(W);
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            cin >> s[i][j];
            if (s[i][j] == '#')
            {
                row[i].push_back(j);
                col[j].push_back(i);
            }
        }
    }
    
    /*
    for (int i = 0; i < H; i++)
    {
        for (auto itr = row[i].begin(); itr != row[i].end(); itr++)
        {
            cout << *itr << " ";
        }
        cout << endl;
    }

    cout << endl;
    for (int j = 0; j < W; j++)
    {
        for (auto itr = col[j].begin(); itr != col[j].end(); itr++)
        {
            cout << *itr << " ";
        }
        cout << endl;
    }
    */

    //全探索
    int counter = 0;
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (s[i][j] == '.')
            {
                int row_num;
                if (row[i].empty())
                {
                    row_num = W;
                }
                else
                {
                    auto itr_row = upper_bound(row[i].begin(), row[i].end(), j);

                    if (itr_row == row[i].begin())
                    {
                        row_num = *itr_row;
                    }
                    else if (itr_row == row[i].end())
                    {
                        row_num = (W - 1) - *(itr_row - 1);
                    }
                    else
                    {
                        row_num = *(itr_row) - *(itr_row - 1) - 1;
                    }
                }

                int col_num;
                if (col[j].empty())
                {
                    col_num = H;
                }
                else
                {
                    auto itr_col = upper_bound(col[j].begin(), col[j].end(), i);

                    if (itr_col == col[j].begin())
                    {
                        col_num = *itr_col;
                    }
                    else if (itr_col == col[j].end())
                    {
                        col_num = (H - 1) - *(itr_col - 1);
                    }
                    else
                    {
                        col_num = *(itr_col) - *(itr_col - 1) - 1;
                    }
                }

                //cout << i << " " << j << " " << row_num << " " << col_num << endl;
                int tmp = row_num + col_num - 1;
                if (tmp > counter)
                {
                    counter = tmp;
                }
            }
        }
    }

    cout << counter << endl;
}