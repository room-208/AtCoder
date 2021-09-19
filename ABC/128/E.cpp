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

//セグ木・遅延セグ木
const long long sgt_ID = -1;
long long sgt_op(long long a, long long b) { return min(a, b); }
long long sgt_e() { return INF_ll; }
long long sgt_mapping(long long f, long long x)
{
    if (f == sgt_ID)
    {
        return x;
    }
    else
    {
        return f;
    }
}
long long sgt_composition(long long f, long long g)
{
    if (f == sgt_ID)
    {
        return g;
    }
    else
    {
        return f;
    }
}
long long sgt_id() { return sgt_ID; }

struct my_struct
{
    long long s, t, x;
};

bool operator<(const my_struct &s_1, const my_struct &s_2)
{
    return s_1.x > s_2.x;
}

int main()
{
    int N, Q;
    cin >> N >> Q;
    vector<my_struct> m(N);
    for (int i = 0; i < N; i++)
    {
        cin >> m[i].s >> m[i].t >> m[i].x;
    }
    vector<long long> D(Q);
    for (int q = 0; q < Q; q++)
    {
        cin >> D[q];
    }

    vector<tuple<long long, int, long long>> event;
    for (int i = 0; i < N; i++)
    {
        auto t_out = make_tuple(m[i].t - m[i].x, 1, m[i].x);
        auto t_in = make_tuple(m[i].s - m[i].x, 2, m[i].x);

        event.push_back(t_in);
        event.push_back(t_out);
    }
    for (int q = 0; q < Q; q++)
    {
        auto t_d = make_tuple(D[q], 100, -1);
        event.push_back(t_d);
    }
    sort(event.begin(), event.end());

    set<long long> st;
    int SIZE = (int)event.size();
    int n = 0;
    while (1)
    {
        if (n == SIZE)
        {
            break;
        }

        int flag = get<1>(event[n]);
        int x = get<2>(event[n]);

        if (flag == 1)
        {
            st.erase(x);
        }
        else if (flag == 2)
        {
            st.insert(x);
        }
        else if (flag == 100)
        {
            if (st.empty())
            {
                cout << -1 << endl;
            }
            else
            {
                cout << *st.begin() << endl;
            }
        }

        n++;
    }
}