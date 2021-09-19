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

using namespace std;

bool cmp(const std::pair<int, int> &a, const std::pair<int, int> &b)
{
    return a.first < b.first;
}

int main()
{
    int N;
    cin >> N;
    vector<int> a(N), b(N), c(N), d(N);
    for (int i = 0; i < N; i++)
    {
        cin >> a[i] >> b[i];
    }
    for (int i = 0; i < N; i++)
    {
        cin >> c[i] >> d[i];
    }

    //ソート
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
    for (int i = 0; i < N; i++)
    {
        p[i].first = c[i];
        p[i].second = d[i];
    }
    sort(p.begin(), p.end(), cmp);
    for (int i = 0; i < N; i++)
    {
        c[i] = p[i].first;
        d[i] = p[i].second;
    }

    std::unordered_set<int> hash; //(a,b)のxまでの履歴
    int a_index = 0;              //次に探索する(a,b)のペアの添字
    int c_index = 0;              //次に探索する(c,d)のペアの添字
    int tmp;                      //一時的な格納
    int b_max;                    //bの最大値
    int counter = 0;              //ペアの個数
    bool flag;

    for (int x = 0; x < 2 * N; x++)
    {
        if (a_index < N)
        {
            if (x == a[a_index])
            {
                //cout << a_index << "\t" << a[a_index] << "\t" << b[a_index] << endl;
                hash.insert(a_index);
                a_index++;
            }
        }
        if (c_index < N)
        {
            if (x == c[c_index])
            {

                //cout << c_index << "\t" << c[c_index] << "\t" << d[c_index] << endl;
                //cout << hash.size() << endl;
                flag = false;
                if (hash.size() != 0)
                {

                    b_max = -1;
                    for (int i = 0; i < a_index; i++)
                    {
                        if (hash.count(i))
                        {
                            if (b[i] < d[c_index] && b_max < b[i])
                            {
                                b_max = b[i];
                                tmp = i;
                                flag = true;
                            }
                        }
                    }

                    c_index++;
                    if (flag)
                    {
                        counter++;
                        hash.erase(tmp);
                    }
                }
                else
                {
                    c_index++;
                }
            }
        }
    }

    cout << counter << endl;
}