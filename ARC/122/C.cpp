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

using namespace std;

int main()
{
    long long N;
    cin >> N;
    long double a = (sqrt(5.) - 1.) / 2.;
    long long x, y;
    long long x_tmp, y_tmp;
    vector<int> op;

    x = N;
    y = (long long)(a * (long double)N);

    int counter = 0;

    while (x != 0LL && y != 0LL)
    {
        if (x >= y)
        {
            x_tmp = x - y;
            y_tmp = y;

            op.push_back(3);
        }
        else
        {
            x_tmp = x;
            y_tmp = y - x;

            op.push_back(4);
        }

        x = x_tmp;
        y = y_tmp;

        counter++;
    }

    if (x == 0)
    {
        while (y != 0)
        {
            y--;

            op.push_back(2);

            counter++;
        }
    }
    else if (y == 0)
    {
        while (x != 0)
        {
            x--;

            op.push_back(1);

            counter++;
        }
    }

    cout << counter << endl;
    for (int i = counter - 1; i >= 0; i--)
    {
        cout << op[i] << endl;
    }
}
