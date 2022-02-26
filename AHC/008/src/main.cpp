//#define _GLIBCXX_DEBUG
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <time.h>

#include <algorithm>
#include <atcoder/fenwicktree>
#include <atcoder/lazysegtree>
#include <atcoder/modint>
#include <atcoder/scc>
#include <atcoder/segtree>
#include <cmath>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// Union-Find
struct UnionFind {
  std::vector<int> par, siz;

  // 初期化
  UnionFind(int n) : par(n, -1), siz(n, 1) {}

  // 根を求める
  int root(int x) {
    if (par[x] == -1)
      return x;  // x が根の場合は x を返す
    else
      return par[x] = root(par[x]);
  }

  // x と y が同じグループに属するかどうか (根が一致するかどうか)
  bool issame(int x, int y) { return root(x) == root(y); }

  // x を含むグループと y を含むグループとを併合する
  bool unite(int x, int y) {
    // x, y をそれぞれ根まで移動する
    x = root(x);
    y = root(y);

    // すでに同じグループのときは何もしない
    if (x == y) return false;

    // union by size (y 側のサイズが小さくなるようにする)
    if (siz[x] < siz[y]) std::swap(x, y);

    // y を x の子とする
    par[y] = x;
    siz[x] += siz[y];
    return true;
  }

  // x を含むグループのサイズ
  int size(int x) { return siz[root(x)]; }
};

enum class Animal {
  Cow = 1,
  Pig = 2,
  Rabbit = 3,
  Dog = 4,
  Cat = 5,
};

struct Pet {
 public:
  int16_t x;
  int16_t y;
  Animal t;
};

struct Human {
 public:
  int16_t x;
  int16_t y;
};

class Grid {
 private:
  std::vector<std::vector<char>> grid;

 public:
  Grid(/* args */);
};

namespace io {
std::pair<std::vector<Pet>, std::vector<Human>> ReadInput(std::istream &input) {
  // ペットの読み込み
  size_t N;
  input >> N;
  std::vector<Pet> p(N);
  for (size_t i = 0; i < N; i++) {
    int16_t tmp;
    input >> p[i].x >> p[i].y >> tmp;
    p[i].t = static_cast<Animal>(tmp);
  }

  // 人間の読み込み
  size_t M;
  input >> M;
  std::vector<Human> h(M);
  for (size_t i = 0; i < M; i++) {
    int16_t tmp;
    input >> h[i].x >> h[i].y;
  }

  return std::make_pair(p, h);
}

void WriteHumanAction() {}

void ReadAnimalAction(std::istream &input, std::vector<Pet> &p) {
  size_t N = p.size();
  std::vector<std::string> actions;
  for (size_t i = 0; i < N; i++) {
    input >> actions[i];
  }
  for (size_t i = 0; i < N; i++) {
    if (actions[i] == ".") {
      continue;
    }
    for (auto &&action : actions[i]) {
      if (action == 'U') {
        p[i].x--;
      } else if (action == 'D') {
        p[i].x++;
      } else if (action == 'L') {
        p[i].y--;
      } else if (action == 'R') {
        p[i].y++;
      }
    }
  }
}
}  // namespace io

namespace logic {}  // namespace logic

int main() {
  std::vector<Pet> p;
  std::vector<Human> h;
  std::tie(p, h) = io::ReadInput(std::cin);

  for (size_t loop = 0; loop < 300; loop++) {
    io::ReadAnimalAction(std::cin, p);
  }
}