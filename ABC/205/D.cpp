#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <bits/stdc++.h>
#include <deque>
#include <queue>

using namespace std;

const long long INF = 1000000000000000000LL;

int main()
{
    int N, Q;
    cin >> N >> Q;
    vector<long long> A(N);
    vector<long long> K(Q);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    for (int i = 0; i < Q; i++)
    {
        cin >> K[i];
    }

    //A[i]より小さい整数の個数
    vector<long long> C(N);
    for (int i = 0; i < N; i++)
    {
        C[i] = A[i] - (i + 1);
        //cout << C[i] << endl;
    }

    //探索
    for (int q = 0; q < Q; q++)
    {
        if (K[q] > C[N - 1])
        {
            cout << K[q] + N << endl;
        }
        else if (K[q] <= C[0])
        {
            cout << K[q] << endl;
        }
        else
        {
            //k番目の区間
            auto itr = lower_bound(C.begin(), C.end(), K[q]);
            int k = itr - C.begin();

            cout << K[q] + k << endl;
        }
    }
    return 0;
}