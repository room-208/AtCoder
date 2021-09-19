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

// 深さ優先探索
void DFS(int x, int y, int H, int W, int A, vector<vector<bool>> &seen, int &cnt)
{
    if (y == H)
    {
        if (A == 0)
        {
            cnt++;
        }

        return;
    }

    if (x == W)
    {
        DFS(0, y + 1, H, W, A, seen, cnt);
        return;
    }

    if (seen[y][x])
    {
        DFS(x + 1, y, H, W, A, seen, cnt);
        return;
    }

    //何もしない
    DFS(x + 1, y, H, W, A, seen, cnt);

    //下を埋める
    if (y < H - 1)
    {
        if (!seen[y + 1][x])
        {
            seen[y][x] = true;
            seen[y + 1][x] = true;
            DFS(x + 1, y, H, W, A - 1, seen, cnt);
            seen[y][x] = false;
            seen[y + 1][x] = false;
        }
    }

    //右を埋める
    if (x < W - 1)
    {
        if (!seen[y][x + 1])
        {
            seen[y][x] = true;
            seen[y][x + 1] = true;
            DFS(x + 1, y, H, W, A - 1, seen, cnt);
            seen[y][x] = false;
            seen[y][x + 1] = false;
        }
    }
}

int main()
{
    int H, W;
    cin >> H >> W;
    int A, B;
    cin >> A >> B;

    vector<vector<bool>> seen(H, vector<bool>(W, false));
    int cnt = 0;
    DFS(0, 0, H, W, A, seen, cnt);

    cout << cnt << endl;
}