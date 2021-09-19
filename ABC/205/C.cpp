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

int main()
{
    int A, B, C;
    cin >> A >> B >> C;

    if (C % 2 == 0)
    {
        A = abs(A);
        B = abs(B);
        if (A < B)
        {
            cout << "<" << endl;
        }
        else if (A > B)
        {
            cout << ">" << endl;
        }
        else
        {
            cout << "=" << endl;
        }
    }
    else
    {
        if (A < B)
        {
            cout << "<" << endl;
        }
        else if (A > B)
        {
            cout << ">" << endl;
        }
        else
        {
            cout << "=" << endl;
        }
    }

    return 0;
}