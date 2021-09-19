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

const int MOD = 1000000007;
const int INF_int = 1000000000;
const long long INF_ll = 1000000000000000000LL;
const int COM_MAX = 510000;
const int COM_pskl_N = 60;

//セグ木・遅延セグ木
const long long sgt_ID = 0;
long long sgt_op(long long a, long long b)
{
    return min(a, b);
}
long long sgt_e()
{
    return INF_ll;
}
long long sgt_target;
bool sgt_f(long long v) { return v > sgt_target; }
//segtree<long long, sgt_op, sgt_e> sgt;

int main()
{
    int Q;
    cin >> Q;
    vector<int> c(Q);
    vector<long long> x(Q, -1);
    for (int i = 0; i < Q; i++)
    {
        cin >> c[i];

        if (c[i] == 1)
        {
            cin >> x[i];
        }
    }

    segtree<long long, sgt_op, sgt_e> sgt(1000000);
    int i = 0;
    int r = 0;
    for (int q = 0; q < Q; q++)
    {
        if (c[q] == 1)
        {
            sgt.set(i, x[q]);
            i++;
        }
        else if (c[q] == 2)
        {
            long long v = sgt.prod(0, r);

            if (v != INF_ll)
            {
                cout << v << endl;
                sgt_target = v;
                int r = sgt.max_right<sgt_f>(0);
                sgt.set(r, INF_ll);
            }
            else
            {
                cout << sgt.get(r) << endl;
                sgt.set(r, INF_ll);
                r++;
            }
        }
        else if (c[q] == 3)
        {
            r = i;
        }
    }
}