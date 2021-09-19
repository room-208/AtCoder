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

//セグ木・遅延セグ木
long long sgt_op(long long a, long long b) { return max(a, b); }
long long sgt_e() { return -INF_ll; }
long long sgt_mapping(long long f, long long x)
{
    return x + f;
}
long long sgt_composition(long long f, long long g)
{
    return f + g;
}
long long sgt_id() { return 0; }
long long sgt_target;
bool sgt_f(long long v) { return v < sgt_target; }

int main()
{
    int N;
    long long D, A;
    cin >> N >> D >> A;
    vector<pair<long long, long long>> p(N);
    for (int i = 0; i < N; i++)
    {
        cin >> p[i].first >> p[i].second;
    }
    sort(p.begin(), p.end());

    vector<long long> X(N), H(N);
    for (int i = 0; i < N; i++)
    {
        X[i] = p[i].first;
        H[i] = p[i].second;
    }

    lazy_segtree<long long, sgt_op, sgt_e, long long, sgt_mapping, sgt_composition, sgt_id> sgt(H);
    long long cnt = 0;

    for (int i = 0; i < N; i++)
    {
        long long h = sgt.get(i);

        //負なら飛ばす
        if (h <= 0)
        {
            continue;
        }

        long long y = X[i] + D * 2;
        long long n = upper_bound(X.begin(), X.end(), y) - X.begin();
        long long c = (long long)ceil((long double)h / (long double)A);

        cnt += c;
        sgt.apply(i, n, -(A * c));
    }

    cout << cnt << endl;
}
