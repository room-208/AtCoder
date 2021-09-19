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

    deque<long long> q;
    priority_queue<long long, vector<long long>, greater<long long>> pq;
    for (int i = 0; i < Q; i++)
    {
        if (c[i] == 1)
        {
            q.push_back(x[i]);
        }
        else if (c[i] == 2)
        {
            if (pq.empty())
            {
                cout << q.front() << endl;
                q.pop_front();
            }
            else
            {
                cout << pq.top() << endl;
                pq.pop();
            }
        }
        else if (c[i] == 3)
        {
            for (int x = 0; x < (int)q.size(); x++)
            {
                pq.push(q[x]);
            }
            q.clear();
        }
    }
}