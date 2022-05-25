#define _USE_MATH_DEFINES

#include <algorithm>
#include <atcoder/fenwicktree>
#include <atcoder/lazysegtree>
#include <atcoder/modint>
#include <atcoder/scc>
#include <atcoder/segtree>
#include <bitset>
#include <cmath>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int main() {
  double A, B, H, M;
  cin >> A >> B >> H >> M;

  double h = (((H + (M / 60.)) / 12.)) * 2. * M_PI;
  double m = (M / 60.) * 2. * M_PI;

  double xa = A * cos(h);
  double ya = A * sin(h);
  double xb = B * cos(m);
  double yb = B * sin(m);

  double d = sqrt((xa - xb) * (xa - xb) + (ya - yb) * (ya - yb));
  printf("%.10f\n", d);
}