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

struct Hara
{
    long long A, B;
};

bool cmp(const Hara &a, const Hara &b)
{
    return a.A < b.A;
}

int main()
{
    int N, M;
    cin >> N >> M;
    vector<Hara> h(N);
    for (int i = 0; i < N; i++)
    {
        cin >> h[i].A >> h[i].B;
    }

    sort(h.begin(), h.end(), cmp);

    /*
    for (int i = 0; i < N; i++)
    {
        cout << h[i].A << "\t" << h[i].B << endl;
    }
    */

    long long counter = M;
    long long price = 0;
    for (int i = 0; i < N; i++)
    {
        long long tmp = min(counter, h[i].B);
        counter -= tmp;
        price += h[i].A * tmp;

        if (counter == 0)
        {
            break;
        }
    }

    cout << price << endl;

    return 0;
}